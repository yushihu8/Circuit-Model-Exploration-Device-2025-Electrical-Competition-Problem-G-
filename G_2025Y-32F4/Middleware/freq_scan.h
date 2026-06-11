/**
  ******************************************************************************
  * @file    freq_scan.h
  * @brief   频率扫描模块头文件
  * @details 定义扫频测量所需的常量和接口。
  *
  *          模块职责：
  *          1. 控制 AD9954 逐点输出扫频激励。
  *          2. 触发外部采样链路并读取双通道 ADC 数据。
  *          3. 配合 FFT 模块提取输入/输出基频分量。
  *          4. 计算各频率点的复数传递函数 H(jw)。
  ******************************************************************************
  */

#ifndef __FREQ_SCAN_H__
#define __FREQ_SCAN_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi_reg.h"
#include "h_calc.h"
#include "fft.h"
#include "AD9954.h"
#include "stdio.h"

/* Exported defines ----------------------------------------------------------*/
/* 扫频起始频率：200 Hz。 */
#define FREQ_START 200

/* 扫频步进：200 Hz。共 SAMPLE_NUM 个点，对应 200 Hz 到 50 kHz。 */
#define FREQ_STEP 200

/* Exported function prototypes ---------------------------------------------*/
/**
  * @brief  执行一次完整的频率扫描
  * @param  sample_buff 输出缓冲区，长度为 SAMPLE_NUM
  * @retval None
  * @details
  *          扫描流程如下：
  *          1. 设置 DDS 起始频率与幅度。
  *          2. 逐点触发采样并读取双通道 ADC 数据。
  *          3. 对输入/输出通道分别执行 FFT。
  *          4. 计算 H(jw) = Hout(jw) / Hin(jw)。
  *          5. 将结果写入 sample_buff，供后续拟合使用。
  */
void freq_scan(complex *sample_buff);

#endif /* __FREQ_SCAN_H__ */
