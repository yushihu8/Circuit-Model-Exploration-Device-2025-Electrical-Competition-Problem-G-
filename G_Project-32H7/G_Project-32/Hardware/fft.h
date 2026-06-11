/**
  ******************************************************************************
  * @file    fft.h
  * @brief   FFT快速傅里叶变换模块头文件
  * @details 本模块实现频域分析的核心功能，包括：
  *          1. 1024点FFT/IFFT变换
  *          2. 复数数组处理
  *          3. 频谱分析
  *          4. 基频分量提取
  *          
  *          应用场景：
  *          - 频率扫描中的信号分析
  *          - 传递函数计算
  *          - 频域特性分析
  *          - 信号处理算法
  *          
  *          技术特点：
  *          - 使用ARM CMSIS-DSP库优化
  *          - 支持64位双精度浮点运算
  *          - 高效的内存管理
  *          - 实时处理能力
  ******************************************************************************
  */

#ifndef __FFT_H__
#define __FFT_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"      // STM32 HAL库
#include "arm_math.h"            // ARM CMSIS-DSP数学库
#include "arm_const_structs.h"  // ARM DSP库常量结构体

/* Exported defines ----------------------------------------------------------*/
/**
 * @brief  FFT变换长度定义
 * @details FFT_LENGTH = 1024
 *          选择1024点FFT的原因：
 *          1. 足够的频率分辨率（Fs/1024 ≈ 4kHz）
 *          2. 合理的计算复杂度（O(N log N)）
 *          3. 适合实时处理要求
 *          4. ARM DSP库优化支持
 *          
 *          频率分辨率计算：
 *          - 采样频率：Fs = 4.096MHz
 *          - 频率分辨率：Δf = Fs/1024 = 4kHz
 *          - 最大分析频率：Fs/2 = 2.048MHz
 */
#define FFT_LENGTH 1024u

/* Exported variables -------------------------------------------------------*/
/**
 * @brief  ADC数据缓冲区
 * @details adc_buff[2 * FFT_LENGTH] = adc_buff[2048]
 *          存储从外部ADC读取的原始采样数据
 *          数组格式：
 *          - adc_buff[0]     : 通道1第1个采样点
 *          - adc_buff[1]     : 通道2第1个采样点
 *          - adc_buff[2]     : 通道1第2个采样点
 *          - adc_buff[3]     : 通道2第2个采样点
 *          - ...
 *          - adc_buff[2046]  : 通道1第1024个采样点
 *          - adc_buff[2047]  : 通道2第1024个采样点
 *          
 *          数据格式：16位有符号整数（-32768 ~ +32767）
 *          对应ADC的满量程输入范围
 */
extern int16_t adc_buff[2 * FFT_LENGTH];

/**
 * @brief  FFT输入输出缓冲区
 * @details fft_in[2 * FFT_LENGTH] = fft_in[2048]
 *          用于FFT变换的输入和输出数据存储
 *          数组格式（复数交错存储）：
 *          - fft_in[0]      : 实部0（直流分量）
 *          - fft_in[1]      : 虚部0（直流分量，通常为0）
 *          - fft_in[2]      : 实部1（基频分量）
 *          - fft_in[3]      : 虚部1（基频分量）
 *          - fft_in[4]      : 实部2（2次谐波）
 *          - fft_in[5]      : 虚部2（2次谐波）
 *          - ...
 *          - fft_in[2046]   : 实部1023（最高频率分量）
 *          - fft_in[2047]   : 虚部1023（最高频率分量）
 *          
 *          数据格式：64位双精度浮点数
 *          提供高精度的频域分析能力
 *          
 *          频率索引对应关系：
 *          - 索引0: 直流分量（0Hz）
 *          - 索引1: 基频分量（Δf = 4kHz）
 *          - 索引2: 2次谐波（8kHz）
 *          - ...
 *          - 索引511: 511次谐波（2.044MHz）
 *          - 索引512-1023: 负频率分量（共轭对称）
 */
extern float64_t fft_in[2 * FFT_LENGTH];

/* Exported function prototypes ---------------------------------------------*/
/**
 * @brief  通道A FFT计算函数
 * @retval None
 * @details 对ADC通道1的数据进行FFT变换
 *          处理流程：
 *          1. 从adc_buff提取通道1数据
 *          2. 转换为浮点格式并存储到fft_in
 *          3. 应用窗函数（可选）
 *          4. 执行1024点FFT变换
 *          5. 结果存储在fft_in数组中
 *          
 *          应用场景：
 *          - 输入信号频谱分析
 *          - 传递函数计算的分子部分
 *          - 系统输入特性分析
 */
void fft_calc_a(void);

/**
 * @brief  通道B FFT计算函数
 * @retval None
 * @details 对ADC通道2的数据进行FFT变换
 *          处理流程：
 *          1. 从adc_buff提取通道2数据
 *          2. 转换为浮点格式并存储到fft_in
 *          3. 应用窗函数（可选）
 *          4. 执行1024点FFT变换
 *          5. 结果存储在fft_in数组中
 *          
 *          应用场景：
 *          - 输出信号频谱分析
 *          - 传递函数计算的分母部分
 *          - 系统输出特性分析
 *          
 *          注意：
 *          - 覆盖fft_in中的前次结果
 *          - 与fft_calc_a()使用相同的缓冲区
 *          - 调用顺序影响最终结果
 */
void fft_calc_b(void);

/* ============================================================================
 * 使用说明和注意事项
 * ============================================================================
 * 
 * @brief  基本使用流程
 * @details 
 * @code
 * // 1. 读取ADC数据
 * spi_reg_read((uint16_t*)adc_buff, 0, 2 * FFT_LENGTH);
 * 
 * // 2. 分析输入信号
 * fft_calc_a();
 * complex input_spectrum = {fft_in[2], fft_in[3]}; // 基频分量
 * 
 * // 3. 分析输出信号
 * fft_calc_b();
 * complex output_spectrum = {fft_in[2], fft_in[3]}; // 基频分量
 * 
 * // 4. 计算传递函数
 * complex transfer_function = complex_div(&output_spectrum, &input_spectrum);
 * @endcode
 * 
 * @brief  频率分辨率说明
 * @details 
 * - 采样频率：Fs = 4.096MHz
 * - FFT长度：N = 1024
 * - 频率分辨率：Δf = Fs/N = 4kHz
 * - 最大分析频率：Fs/2 = 2.048MHz
 * - 有效频率点数：N/2 + 1 = 513
 * 
 * @brief  内存使用说明
 * @details 
 * - adc_buff：2048 × 2字节 = 4KB
 * - fft_in：2048 × 8字节 = 16KB
 * - 总内存使用：20KB
 * - 建议使用DTCM-RAM以提高访问速度
 * 
 * @brief  性能优化建议
 * @details 
 * 1. 使用ARM CMSIS-DSP库的优化函数
 * 2. 将数据缓冲区放置在DTCM内存区域
 * 3. 启用CPU的FPU和DSP指令集
 * 4. 考虑使用DMA进行ADC数据传输
 * 5. 适当使用编译器优化选项
 */

#endif /* __FFT_H__ */
