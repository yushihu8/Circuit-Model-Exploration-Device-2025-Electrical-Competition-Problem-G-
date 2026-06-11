#include "fft.h"

//ADC数据缓冲数组
int16_t adc_buff[2 * FFT_LENGTH] = {0};

//fft输入数组
float64_t fft_in[2 * FFT_LENGTH];
float64_t fft_out[FFT_LENGTH];
void fft_calc_b(void)
{
  for(uint16_t i = 0;i < FFT_LENGTH;i++)
  {
    fft_in[2 * i] = (adc_buff[2 * i] - 8192) / 16383.0 * 5.0;
    fft_in[2 * i + 1] = 0;
  }
  arm_cfft_f64(&arm_cfft_sR_f64_len1024, fft_in, 0, 1);
}


void fft_calc_a(void)
{
  for(uint16_t i = 0;i < FFT_LENGTH;i++)
  {
    fft_in[2 * i] = -(8192 - adc_buff[2 * i + 1])  / 16383.0 * 5.0;
    fft_in[2 * i + 1] = 0;
  }
  arm_cfft_f64(&arm_cfft_sR_f64_len1024, fft_in, 0, 1);
}





