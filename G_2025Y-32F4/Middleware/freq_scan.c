/**
  ******************************************************************************
  * @file    freq_scan.c
  * @brief   频率扫描模块实现
  * @details 本模块完成自动扫频测量，用于获取被测系统在
  *          200 Hz 到 50 kHz 范围内的复数频率响应。
  *
  *          每个频点的流程为：
  *          DDS 输出激励 -> 触发采样 -> 读取 ADC 数据 ->
  *          输入通道 FFT -> 输出通道 FFT -> 计算传递函数
  ******************************************************************************
  */

#include "freq_scan.h"

/* 保存每个扫频点的幅度平方，便于串口调试观察。 */
float32_t gain[SAMPLE_NUM];

/**
  * @brief  频率扫描主函数
  * @param  sample_buff 输出的复数频率响应数组
  * @retval None
  */
void freq_scan(complex *sample_buff)
{
  complex h_in;
  complex h_out;

  /* 初始化 DDS 到起始频点，并打开最大幅度输出。 */
  AD9954_SetFre(FREQ_START);
  AD9954_Voltage_Control(16383);

  HAL_Delay(100);

  for (uint16_t i = 0; i < SAMPLE_NUM; i++)
  {
    uint16_t cmd = 1;

    /* 等待激励稳定后触发一次采样。 */
    spi_reg_write(&cmd, 0xbb01, 1);
    HAL_Delay(20);

    /* 读取 1024 点双通道交织采样数据。 */
    spi_reg_read((uint16_t *)adc_buff, 0, 2 * FFT_LENGTH);

    /* 提取输入通道当前频点的基频复数分量。 */
    fft_calc_a();
    h_in.r = fft_in[2 * (i + 1)];
    h_in.i = fft_in[2 * (i + 1) + 1];

    /* 提取输出通道当前频点的基频复数分量。 */
    fft_calc_b();
    h_out.r = fft_in[2 * (i + 1)];
    h_out.i = fft_in[2 * (i + 1) + 1];

    /* 计算传递函数 H(jw) = Hout(jw) / Hin(jw)。 */
    sample_buff[i] = complex_div(&h_out, &h_in);

    /* 切换到下一个扫频点。 */
    AD9954_SetFre(FREQ_STEP * (i + 2));
		
    /* 保存幅度平方供调试输出使用。 */
    gain[i] = sample_buff[i].r * sample_buff[i].r +
              sample_buff[i].i * sample_buff[i].i;
  }

  /* 输出所有频点的幅度平方，并以 END 作为结束标记。 */
  for (uint16_t k = 0; k < SAMPLE_NUM; k++)
  {
    printf("%f\n", gain[k]);
  }
  printf("END\n");

  /* 关闭 DDS 输出，避免扫频结束后继续激励被测系统。 */
  AD9954_SetFre(0);
  AD9954_Voltage_Control(0);
}
