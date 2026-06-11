#include "AD9954.h"

#define fosc  20
#define PLL_MULTIPLIER  19
#define fs  (fosc * PLL_MULTIPLIER)

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

double fH_Num = 11.3025455157895;

double CurFreq;
double test;
uint8_t Mode_flag = 0;
static double StepFreq, StartFreq, EndFreq;

void AD9954_GPIO_Init_HAL(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  HAL_GPIO_WritePin(SDIO_GPIO_Port, SDIO_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PS0_GPIO_Port, PS0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PS1_GPIO_Port, PS1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(IO_UD_GPIO_Port, IO_UD_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DDSSCLK_GPIO_Port, DDSSCLK_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DDSRS_GPIO_Port, DDSRS_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DDSCS_GPIO_Port, DDSCS_Pin, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = SDIO_Pin | PS0_Pin | PS1_Pin | DDSSCLK_Pin | DDSRS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = IO_UD_Pin;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = DDSCS_Pin;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = DDSSDO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DDSSDO_GPIO_Port, &GPIO_InitStruct);
}

void AD9954_Reset(void)
{
  RESET_L;
  RESET_H;
  HAL_Delay(100);
  RESET_L;
  CS_L;
  DSCLK_L;
  PS0_L;
  PS1_L;
  IO_UD_L;
  CS_H;
}

void AD9954_WriteData(u8 Data)
{
  u8 i;
  for (i = 0; i < 8; i++)
  {
    DSCLK_L;
    HAL_Delay(1);
    if (Data & 0x80)
    {
      SDIO_H;
    }
    else
    {
      SDIO_L;
    }
    DSCLK_H;
    HAL_Delay(1);
    Data <<= 1;
  }
}

u8 AD9954_ReadData(void)
{
  u8 i, data = 0;
  for (i = 0; i < 8; i++)
  {
    DSCLK_L;
    data |= SDO;
    DSCLK_H;
    data <<= 1;
  }
  return data;
}

u32 AD9954_Read_RegisterValue(u8 Register)
{
  u32 Resgiter_Data;

  CS_H;
  AD9954_WriteData(Register | 0x80);
  Resgiter_Data = AD9954_ReadData();
  Resgiter_Data <<= 8;
  Resgiter_Data += AD9954_ReadData();
  Resgiter_Data <<= 8;
  Resgiter_Data += AD9954_ReadData();
  Resgiter_Data <<= 8;
  Resgiter_Data += AD9954_ReadData();
  CS_L;
  AD9954_UpDate();
  return Resgiter_Data;
}

void AD9954_UpDate(void)
{
  IO_UD_L;
	
  IO_UD_H;
//  HAL_Delay(1);
  IO_UD_L;
}

void AD9954_Init(void)
{
  AD9954_GPIO_Init_HAL();
  AD9954_Reset();
  CS_L;

  AD9954_WriteData(CFR1);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x10);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x40);

  AD9954_WriteData(CFR2);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x08);
  AD9954_WriteData(0x54);

#if fs > 400
#error "System frequency exceeds AD9954 limit"
#endif

  CS_H;
  AD9954_UpDate();
}

void AD9954_SetFre(double Fre)
{
  u32 FTW = 0;
  FTW = (u32)(Fre * Fre_Ave);
  CS_L;

  AD9954_WriteData(FTW0);
  AD9954_WriteData((u8)(FTW >> 24));
  AD9954_WriteData((u8)(FTW >> 16));
  AD9954_WriteData((u8)(FTW >> 8));
  AD9954_WriteData((u8)FTW);

  CS_H;
  AD9954_UpDate();
}

void AD9954_LinearSweepMode(double FreMin, double FreMax, double Frestep, u8 UpStepTime)
{
  u32 FTW_MIN, FTW_MAX;
  u32 FTW_Step;

  PS0_L;
  PS1_L;

  CS_L;

  AD9954_WriteData(CFR1);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x20);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x00);

  FTW_MIN = FreMin * Fre_Ave;
  AD9954_WriteData(FTW0);
  AD9954_WriteData((u8)(FTW_MIN >> 24));
  AD9954_WriteData((u8)(FTW_MIN >> 16));
  AD9954_WriteData((u8)(FTW_MIN >> 8));
  AD9954_WriteData((u8)(FTW_MIN));

  FTW_MAX = FreMax * Fre_Ave;
  AD9954_WriteData(FTW1);
  AD9954_WriteData((u8)(FTW_MAX >> 24));
  AD9954_WriteData((u8)(FTW_MAX >> 16));
  AD9954_WriteData((u8)(FTW_MAX >> 8));
  AD9954_WriteData((u8)(FTW_MAX));

  FTW_Step = Frestep * Fre_Ave;
  AD9954_WriteData(PLSCW);
  AD9954_WriteData((u8)UpStepTime);
  AD9954_WriteData((u8)(FTW_Step >> 24));
  AD9954_WriteData((u8)(FTW_Step >> 16));
  AD9954_WriteData((u8)(FTW_Step >> 8));
  AD9954_WriteData((u8)(FTW_Step));

  PS0_H;

  CS_H;
  AD9954_UpDate();
}

void AD9954_Voltage_Control(u16 Vol)
{
  Vol &= 0x3FFF;

  CS_L;

  /* 使能ASF幅度缩放路径（AD9954手动OSK模式） */
  AD9954_WriteData(CFR1);
  AD9954_WriteData(0x02);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x40);

  AD9954_WriteData(ASF);
  AD9954_WriteData(Vol >> 8);
  AD9954_WriteData(Vol);

  CS_H;
  AD9954_UpDate();
}

void AD9954_CompMode(void)
{
  CS_L;

  AD9954_WriteData(CFR1);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x00);
  AD9954_WriteData(0x00);

  CS_H;
  AD9954_UpDate();
}

void SignalMode(double Freq)
{
  Mode_flag = 0;
  CurFreq = Freq;
  AD9954_SetFre(CurFreq);
}

void AD9954_Fre_Vol(u32 Fre, double Vol_REF)
{
  AD9954_SetFre(Fre);
  AD9954_Voltage_Control(Vol_REF / 1.32 * 16383);
}
