/**
  ******************************************************************************
  * @file    h_calc.h
  * @brief   滤波器计算模块头文件
  * @details 本模块实现自适应数字滤波器设计的核心算法，包括：
  *          1. 基于最小二乘法的模拟滤波器拟合
  *          2. 矩阵方程求解
  *          3. 双线性变换
  *          4. Q31量化处理
  *          5. 滤波器类型自动识别
  *          
  *          算法流程：
  *          频域响应数据 → 矩阵系数计算 → 线性方程组求解 → 双线性变换 → 量化输出
  *          
  *          数学基础：
  *          - 模拟滤波器：H(s) = (b₂s² + b₁s + b₀)/(a₂s² + a₁s + 1)
  *          - 数字滤波器：H(z) = (b₀ + b₁z⁻¹ + b₂z⁻²)/(1 + a₁z⁻¹ + a₂z⁻²)
  *          - 双线性变换：s = 2Fs(1-z⁻¹)/(1+z⁻¹)
  ******************************************************************************
  */

#ifndef __H_CAL_H__
#define __H_CAL_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"      // STM32 HAL库
#include "arm_math.h"            // ARM CMSIS-DSP数学库
#include "arm_const_structs.h"  // ARM DSP库常量结构体
#include "spi_reg.h"             // SPI寄存器读写接口
#include "stdio.h"               // 标准输入输出库

/* Exported defines ----------------------------------------------------------*/
/**
 * @brief  频率扫描采样点数
 * @details SAMPLE_NUM = 250
 *          对应200Hz-50kHz频率范围，步进200Hz
 *          用于构建最小二乘拟合的线性方程组
 */
#define SAMPLE_NUM 250u

/**
 * @brief  矩阵维度定义
 * @details MATRIX_SIZE = 5
 *          用于5×5系数矩阵和5×1向量运算
 *          对应二阶滤波器的5个未知系数：[b₀, b₁, b₂, a₁, a₂]ᵀ
 */
#define MATRIX_SIZE 5

/**
 * @brief  向量维度定义
 * @details VECTOR_SIZE = 5
 *          与矩阵维度一致，用于线性方程组求解
 */
#define VECTOR_SIZE 5

/**
 * @brief  系统采样频率
 * @details Fs = 4,096,000 Hz = 4.096 MHz
 *          用于双线性变换的频率参数
 *          选择原因：
 *          1. 足够高的采样率避免混叠
 *          2. 便于与ADC采样频率匹配
 *          3. 双线性变换系数计算方便
 */
#define Fs              4096000

/**
 * @brief  Q31量化缩放系数
 * @details Q48_SCALE = 2^48 - 1 = 281,474,976,710,655
 *          注意：虽然名为Q48，实际用于Q31格式的高精度计算
 *          用于浮点数到定点数的转换：
 *          int64_value = round(float_value * Q48_SCALE)
 */
#define Q48_SCALE       35184372088831LL

/**
 * @brief  滤波器类型判断阈值
 * @details FILTER_MODE_THR = 0.8
 *          用于根据|H(0)|和|H(∞)|判断滤波器类型：
 *          - |H(0)| > 0.8 且 |H(∞)| < 0.8 → 低通滤波器
 *          - |H(0)| < 0.8 且 |H(∞)| > 0.8 → 高通滤波器
 *          - |H(0)| < 0.8 且 |H(∞)| < 0.8 → 带通滤波器
 *          - |H(0)| > 0.8 且 |H(∞)| > 0.8 → 带阻滤波器
 */
#define FILTER_MODE_THR  0.8

/**
 * @brief  浮点数精度阈值
 * @details EPS = 1e-15
 *          用于数值比较和除零检查
 *          当数值绝对值小于EPS时视为零
 */
#define EPS       1e-15

/* Exported types ------------------------------------------------------------*/
/**
 * @brief  滤波器类型枚举
 * @details 定义四种基本滤波器类型
 *          用于自动识别和分类滤波器特性
 */
typedef enum
{
    LOW_PASS_FILTER,   ///< 低通滤波器：允许低频通过，衰减高频
    HIGH_PASS_FILTER,  ///< 高通滤波器：允许高频通过，衰减低频
    BAND_PASS_FILTER,  ///< 带通滤波器：允许特定频段通过
    BAND_STOP_FILTER   ///< 带阻滤波器：衰减特定频段
} FILTER_TYPE;

/**
 * @brief  复数结构体
 * @details 使用64位双精度浮点数表示复数
 *          用于存储频率响应的幅度和相位信息
 */
typedef struct
{
    float64_t r;  ///< 实部 Real part
    float64_t i;  ///< 虚部 Imaginary part
} complex;

/**
 * @brief  模拟滤波器系数结构体
 * @details 存储二阶模拟滤波器的传递函数系数
 *          传递函数形式：H(s) = (b₂s² + b₁s + b₀)/(a₂s² + a₁s + 1)
 *          注意：分母常数项固定为1，便于归一化处理
 */
typedef struct
{
    float64_t b0;  ///< 分子常数项系数
    float64_t b1;  ///< 分子一次项系数
    float64_t b2;  ///< 分子二次项系数
    float64_t a1;  ///< 分母一次项系数
    float64_t a2;  ///< 分母二次项系数
} analog_coef;

/**
 * @brief  数字滤波器系数结构体
 * @details 存储二阶数字滤波器的传递函数系数（Q31格式）
 *          传递函数形式：H(z) = (b₀ + b₁z⁻¹ + b₂z⁻²)/(1 + a₁z⁻¹ + a₂z⁻²)
 *          使用64位整数存储，便于硬件实现
 */
typedef struct
{
    int64_t b0;  ///< 分子常数项系数（Q31格式）
    int64_t b1;  ///< 分子一次项系数（Q31格式）
    int64_t b2;  ///< 分子二次项系数（Q31格式）
    int64_t a1;  ///< 分母一次项系数（Q31格式）
    int64_t a2;  ///< 分母二次项系数（Q31格式）
} digital_coef;

/* Exported function prototypes -----------------------------------------------*/
/**
 * @brief  计算矩阵方程系数
 * @param  sample_data: 输入参数，频率响应数据数组指针
 * @retval None
 * @details 基于频率响应数据计算最小二乘拟合的系数矩阵
 *          计算结果存储在全局变量中，供matrix_calc()使用
 */
void coef_calc(const complex * sample_data);

/**
 * @brief  求解矩阵方程得到模拟滤波器系数
 * @retval analog_coef: 模拟滤波器系数结构体
 * @details 求解5×5线性方程组 M*N = C
 *          返回二阶模拟滤波器的分子和分母系数
 */
analog_coef matrix_calc(void);

/**
 * @brief  双线性变换和量化
 * @param  analog_coef_data: 输入参数，模拟滤波器系数指针
 * @retval digital_coef: 数字滤波器系数结构体（Q31格式）
 * @details 将模拟滤波器转换为数字滤波器并进行Q31量化
 *          使用双线性变换：s = 2Fs(1-z⁻¹)/(1+z⁻¹)
 */
digital_coef bilinear_transform_quant(const analog_coef * analog_coef_data);

/**
 * @brief  滤波器类型识别
 * @param  coef: 输入参数，模拟滤波器系数指针
 * @retval FILTER_TYPE: 滤波器类型枚举值
 * @details 根据|H(0)|和|H(∞)|判断滤波器类型
 *          自动识别低通、高通、带通、带阻滤波器
 */
FILTER_TYPE get_filter_type(const analog_coef * coef);

/**
 * @brief  复数除法运算
 * @param  data0: 被除数（分子）复数指针
 * @param  data1: 除数（分母）复数指针
 * @retval complex: 商的复数结果
 * @details 实现复数除法：(a+jb)/(c+jd) = [(ac+bd)+j(bc-ad)]/(c²+d²)
 */
complex complex_div(const complex * data0, const complex * data1);

/**
 * @brief  系数加载函数
 * @param  coef: 输入参数，数字滤波器系数指针
 * @retval None
 * @details 将计算得到的数字滤波器系数通过SPI加载到外部滤波器芯片
 *          将64位系数拆分为3个16位数据传输
 */
void coef_lode(const digital_coef * coef);

#endif /* __H_CAL_H__ */
