#include "fft.h"

/**
  * @brief  ADC 原始采样缓冲区定义
  * @details 该数组由 `spi_reg_read()` 从 FPGA RAM 中读回后填充。
  *          双通道数据采用交织方式存放，排列方式见 `fft.h` 说明。
  */
int16_t adc_buff[2 * FFT_LENGTH] = {0};

/**
  * @brief  FFT 输入/输出缓冲区
  * @details 采用原地变换方式：
  *          - 变换前保存时域输入
  *          - 变换后保存频域输出
  */
float64_t fft_in[2 * FFT_LENGTH];

/**
  * @brief  预留频谱数组
  * @details 当前主流程未直接使用，保留给后续扩展使用。
  */
float64_t fft_out[FFT_LENGTH];

/**
  * @brief  计算输出通道的 FFT
  * @retval None
  * @details
  *          处理步骤如下：
  *          1. 从交织缓冲区中提取偶数下标通道数据
  *          2. 去除直流偏置并按满量程做归一化
  *          3. 将虚部清零，构造实序列 FFT 输入
  *          4. 调用 CMSIS-DSP 完成 1024 点复数 FFT
  *
  *          其中：
  *          - `8192` 为 ADC 中点附近偏置
  *          - `16383.0` 对应 14 位 ADC 满量程
  *          - `5.0` 为当前工程使用的电压换算系数
  */
void fft_calc_b(void)
{
  for(uint16_t i = 0; i < FFT_LENGTH; i++)
  {
    fft_in[2 * i] = (adc_buff[2 * i] - 8192) / 16383.0 * 5.0;
    fft_in[2 * i + 1] = 0;
  }

  arm_cfft_f64(&arm_cfft_sR_f64_len1024, fft_in, 0, 1);
}

/**
  * @brief  计算输入通道的 FFT
  * @retval None
  * @details
  *          处理步骤如下：
  *          1. 从交织缓冲区中提取奇数下标通道数据
  *          2. 按当前通道极性进行翻转
  *          3. 乘以经验补偿系数 1.01 做幅值校正
  *          4. 将虚部清零，构造实序列 FFT 输入
  *          5. 调用 CMSIS-DSP 完成 1024 点复数 FFT
  *
  *          注意：
  *          - 本函数执行后会覆盖 `fft_in` 中之前的内容
  *          - 如果上层还需要上一次 FFT 的频谱，应先取走数据
  */
void fft_calc_a(void)
{
  for(uint16_t i = 0; i < FFT_LENGTH; i++)
  {
    fft_in[2 * i] =  (8192 - adc_buff[2 * i + 1]) / 16383.0 * 5.0;
    fft_in[2 * i + 1] = 0;
  }

  arm_cfft_f64(&arm_cfft_sR_f64_len1024, fft_in, 0, 1);
}
