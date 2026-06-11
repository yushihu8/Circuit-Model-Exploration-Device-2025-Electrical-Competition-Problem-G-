/**
  ******************************************************************************
  * @file    freq_scan.h
  * @brief   频率扫描模块头文件
  * @details 定义频率扫描功能的相关常量、类型声明和函数接口
  *          
  *          模块功能：
  *          - 自动频率扫描（200Hz-50kHz）
  *          - 传递函数测量
  *          - 频率响应特性分析
  *          
  *          硬件依赖：
  *          - AD9954 DDS芯片（信号生成）
  *          - 外部ADC（数据采集）
  *          - SPI接口（通信）
  ******************************************************************************
  */

#ifndef __FREQ_SCAN_H__
#define __FREQ_SCAN_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"  // STM32 HAL库
#include "spi_reg.h"        // SPI寄存器读写接口
#include "h_calc.h"         // 滤波器计算相关定义（complex结构体等）
#include "fft.h"            // FFT处理接口
#include "ad9954.h"         // AD9954 DDS控制接口
#include "stdio.h"          // 标准输入输出库

/* Exported defines ----------------------------------------------------------*/
/**
  * @brief  扫频起始频率定义
  * @details FREQ_START = 200Hz
  *          选择200Hz作为起始频率的原因：
  *          1. 避开直流分量和工频干扰（50/60Hz）
  *          2. 大多数模拟系统的有效工作频段起点
  *          3. 便于后续滤波器设计的频率归一化
  */
#define FREQ_START 200

/**
  * @brief  扫频步进频率定义
  * @details FREQ_STEP = 200Hz
  *          选择200Hz步进的原因：
  *          1. 在200Hz-50kHz范围内提供250个测量点
  *          2. 足够的频率分辨率用于滤波器设计
  *          3. 合理的测量时间与精度平衡
  *          
  *          频率点计算：
  *          - 总点数：SAMPLE_NUM = 250
  *          - 频率范围：200Hz ~ 50kHz
  *          - 频率点：200Hz, 400Hz, 600Hz, ..., 50kHz
  */
#define FREQ_STEP 200

/* Exported function prototypes ---------------------------------------------*/
/**
  * @brief  频率扫描主函数
  * @param  sample_buff: 输出参数，指向复数数组的指针
  *                      数组大小为SAMPLE_NUM，用于存储各频率点的传递函数
  *                      sample_buff[i] = H(jω_i) = H_out(jω_i) / H_in(jω_i)
  * @retval None
  * @details 执行完整的频率扫描流程：
  *          1. 初始化AD9954 DDS输出
  *          2. 循环扫描所有频率点
  *          3. 对每个频率点进行FFT分析
  *          4. 计算传递函数并存储结果
  *          5. 输出调试信息
  *          6. 清理并关闭硬件
  *          
  *          调用示例：
  *          @code
  *          complex freq_response[SAMPLE_NUM];
  *          freq_scan(freq_response);  // 执行频率扫描
  *          // freq_response现在包含250个复数传递函数值
  *          @endcode
  *          
  *          注意事项：
  *          - 调用前需确保AD9954和SPI已正确初始化
  *          - 函数执行时间较长（约250 × 40ms = 10秒）
  *          - 结果可用于后续的滤波器系数计算
  */
void freq_scan(complex *sample_buff);

#endif /* __FREQ_SCAN_H__ */
