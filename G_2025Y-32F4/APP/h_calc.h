/**
  ******************************************************************************
  * @file    h_calc.h
  * @brief   频响拟合与滤波器系数计算模块头文件
  * @details 本模块负责将扫频得到的复数频率响应 H(jw) 拟合为
  *          二阶模拟滤波器模型，并进一步转换为 FPGA 可用的
  *          定点数字滤波器系数。
  *
  *          整体流程：
  *          H(jw) -> coef_calc() -> matrix_calc()
  *                -> bilinear_transform_quant() -> coef_lode()
  ******************************************************************************
  */

#ifndef __H_CAL_H__
#define __H_CAL_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "spi_reg.h"
#include "stdio.h"

/* Exported defines ----------------------------------------------------------*/
/* 扫频点数：200 Hz 到 50 kHz，步进 200 Hz，共 250 点。 */
#define SAMPLE_NUM 250u

/* 最小二乘方程矩阵维度。 */
#define MATRIX_SIZE 5

/* 线性方程向量维度。 */
#define VECTOR_SIZE 5

/* 数字滤波器目标采样率，需与外部 FPGA 滤波链路一致。 */
#define Fs 4096000

/* 48 位定点量化缩放系数。 */
#define Q48_SCALE 35184372088831LL

/* 滤波器类型判别阈值。 */
#define FILTER_MODE_THR 0.8

/* 浮点比较用的极小量。 */
#define EPS 1e-15

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    LOW_PASS_FILTER,
    HIGH_PASS_FILTER,
    BAND_PASS_FILTER,
    BAND_STOP_FILTER
} FILTER_TYPE;

/* 复数类型，用于保存频率响应和频域运算结果。 */
typedef struct
{
    float64_t r;
    float64_t i;
} complex;

/*
 * 模拟二阶滤波器系数，对应：
 * H(s) = (b2*s^2 + b1*s + b0) / (a2*s^2 + a1*s + 1)
 */
typedef struct
{
    float64_t b0;
    float64_t b1;
    float64_t b2;
    float64_t a1;
    float64_t a2;
} analog_coef;

/*
 * 数字二阶滤波器系数，量化为 48 位定点数后下发到 FPGA。
 * 对应：
 * H(z) = (b0 + b1*z^-1 + b2*z^-2) / (1 + a1*z^-1 + a2*z^-2)
 */
typedef struct
{
    int64_t b0;
    int64_t b1;
    int64_t b2;
    int64_t a1;
    int64_t a2;
} digital_coef;

/* Exported function prototypes ----------------------------------------------*/
/* 根据扫频得到的 H(jw) 计算最小二乘方程所需的累加项。 */
void coef_calc(const complex *sample_data);

/* 求解二阶模拟滤波器的系数。 */
analog_coef matrix_calc(void);

/* 执行双线性变换并量化为 48 位定点系数。 */
digital_coef bilinear_transform_quant(const analog_coef *analog_coef_data);

/* 根据低频和高频增益特征判断滤波器类型。 */
FILTER_TYPE get_filter_type(const analog_coef *coef);

/* 复数除法，主要用于 H(jw) = Hout / Hin。 */
complex complex_div(const complex *data0, const complex *data1);

/* 将量化后的数字滤波器系数写入 FPGA 寄存器。 */
void coef_lode(const digital_coef *coef);

#endif /* __H_CAL_H__ */
