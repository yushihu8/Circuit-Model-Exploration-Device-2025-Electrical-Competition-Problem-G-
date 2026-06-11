/**
  ******************************************************************************
  * @file    fft.h
  * @brief   FFT 频域分析模块头文件
  * @details 本模块负责将 FPGA 读回的 ADC 原始采样数据转换为
  *          频域复数结果，供扫频模块提取基频响应。
  *
  *          当前实现约定：
  *          - 每次读取 1024 点双通道交织采样数据
  *          - 采用 CMSIS-DSP 双精度复数 FFT
  *          - FFT 结果保存在 fft_in 中，格式为 [Re0, Im0, Re1, Im1, ...]
  ******************************************************************************
  */

#ifndef __FFT_H__
#define __FFT_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "arm_math.h"
#include "arm_const_structs.h"

/* Exported defines ----------------------------------------------------------*/
/* 固定使用 1024 点 FFT，与外部采样长度保持一致。 */
#define FFT_LENGTH 1024u

/* Exported variables --------------------------------------------------------*/
/**
  * @brief  ADC 原始采样缓冲区
  * @details 长度为 2 * FFT_LENGTH，数据按双通道交织排列：
  *          ch0[0], ch1[0], ch0[1], ch1[1], ...
  */
extern int16_t adc_buff[2 * FFT_LENGTH];

/**
  * @brief  FFT 输入/输出缓冲区
  * @details 调用 FFT 前保存时域数据，调用后原地变为频域结果。
  */
extern float64_t fft_in[2 * FFT_LENGTH];

/* Exported function prototypes ----------------------------------------------*/
/**
  * @brief  计算输入通道的 FFT
  * @retval None
  * @details 本函数从交织缓冲区中提取输入通道数据，完成归一化与
  *          极性处理后执行 1024 点复数 FFT。
  */
void fft_calc_a(void);

/**
  * @brief  计算输出通道的 FFT
  * @retval None
  * @details 本函数从交织缓冲区中提取输出通道数据，完成归一化后
  *          执行 1024 点复数 FFT。
  */
void fft_calc_b(void);

#endif /* __FFT_H__ */
