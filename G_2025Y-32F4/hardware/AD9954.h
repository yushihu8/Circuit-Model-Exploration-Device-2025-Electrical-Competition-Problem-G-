/**
  ******************************************************************************
  * @file    AD9954.h
  * @brief   AD9954 DDS chip driver header
  ******************************************************************************
  */

#ifndef __AD9954__H__
#define __AD9954__H__

#include "main.h"

#define SDIO_Pin GPIO_PIN_3
#define SDIO_GPIO_Port GPIOC

#define PS0_Pin GPIO_PIN_2
#define PS0_GPIO_Port GPIOC

#define PS1_Pin GPIO_PIN_1
#define PS1_GPIO_Port GPIOC

#define IO_UD_Pin GPIO_PIN_0
#define IO_UD_GPIO_Port GPIOC    

#define DDSSCLK_Pin GPIO_PIN_4
#define DDSSCLK_GPIO_Port GPIOC

#define DDSRS_Pin GPIO_PIN_1
#define DDSRS_GPIO_Port GPIOB

#define DDSCS_Pin GPIO_PIN_5
#define DDSCS_GPIO_Port GPIOC

#define DDSSDO_Pin GPIO_PIN_0
#define DDSSDO_GPIO_Port GPIOB

#define PS1_L  HAL_GPIO_WritePin(PS1_GPIO_Port, PS1_Pin, GPIO_PIN_RESET)
#define PS1_H  HAL_GPIO_WritePin(PS1_GPIO_Port, PS1_Pin, GPIO_PIN_SET)

#define PS0_L  HAL_GPIO_WritePin(PS0_GPIO_Port, PS0_Pin, GPIO_PIN_RESET)
#define PS0_H  HAL_GPIO_WritePin(PS0_GPIO_Port, PS0_Pin, GPIO_PIN_SET)

#define SDIO_L  HAL_GPIO_WritePin(SDIO_GPIO_Port, SDIO_Pin, GPIO_PIN_RESET)
#define SDIO_H  HAL_GPIO_WritePin(SDIO_GPIO_Port, SDIO_Pin, GPIO_PIN_SET)

#define DSCLK_L  HAL_GPIO_WritePin(DDSSCLK_GPIO_Port, DDSSCLK_Pin, GPIO_PIN_RESET)
#define DSCLK_H  HAL_GPIO_WritePin(DDSSCLK_GPIO_Port, DDSSCLK_Pin, GPIO_PIN_SET)

#define CS_L  HAL_GPIO_WritePin(DDSCS_GPIO_Port, DDSCS_Pin, GPIO_PIN_RESET)
#define CS_H  HAL_GPIO_WritePin(DDSCS_GPIO_Port, DDSCS_Pin, GPIO_PIN_SET)

#define RESET_L  HAL_GPIO_WritePin(DDSRS_GPIO_Port, DDSRS_Pin, GPIO_PIN_RESET)
#define RESET_H  HAL_GPIO_WritePin(DDSRS_GPIO_Port, DDSRS_Pin, GPIO_PIN_SET)

#define IO_UD_L  HAL_GPIO_WritePin(IO_UD_GPIO_Port, IO_UD_Pin, GPIO_PIN_RESET)
#define IO_UD_H  HAL_GPIO_WritePin(IO_UD_GPIO_Port, IO_UD_Pin, GPIO_PIN_SET)

#define SDO HAL_GPIO_ReadPin(DDSSDO_GPIO_Port,DDSSDO_Pin)

#define CFR1 0X00
#define CFR2 0X01
#define ASF  0X02
#define ARR  0X03
#define FTW0 0X04
#define POW0 0X05
#define FTW1 0X06
#define NLSCW 0X07
#define PLSCW 0X08
#define RSCW0 0X07
#define RSCW1 0X08
#define RSCW2 0X09
#define RSCW3 0X0A
#define RAM  0X0B

#define No_Dwell 0X80
#define Fre_Ave 10.73741824f
#define DAC_Ave 0.00008825f

void AD9954_GPIO_Init_HAL(void);
void AD9954_Reset(void);
void AD9954_WriteData(uint8_t Data);
void AD9954_UpDate(void);
void AD9954_Init(void);
void AD9954_SetFre(double Fre);
uint8_t AD9954_ReadData(void);
uint32_t AD9954_Read_RegisterValue(uint8_t Register);
void AD9954_LinearSweepMode(double FreMin, double FreMax, double Frestep, uint8_t UpStepTime);
void ScanMode(double StartFrequency, double EndFrequency, double StepFrequency);
void AD9954_Voltage_Control(uint16_t Vol);
void SignalMode(double Freq);
void AD9954_Fre_Vol(uint32_t Fre, double Vol_REF);

#endif /* __AD9954__H__ */
