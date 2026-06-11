#include "AD9954.h"
//系统频率fosc（外部晶振频率），系统频率=fosc*M
#define fosc  20                        //晶振频率
#define PLL_MULTIPLIER  19              //PLL倍频数（4--20）
#define fs  (fosc*PLL_MULTIPLIER)       //系统时钟频率

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

//double fH_Num=11.2204;
//double fH_Num=10.73741824;
//double fH_Num=11.3671588397205;//
double fH_Num = 11.3025455157895;

double CurFreq;	// 当前频率
double test;
uint8_t Mode_flag = 0;						// 当前模式：1->扫频模式；0->点频模式
static double StepFreq, StartFreq, EndFreq; // 步进频率(可固定)


/******************************************************************************
**函数原型：AD9954_GPIO_Init()
**函数功能：AD9954引脚初始化
**输入参数：无
**输出参数：无
**备    注：标准库
******************************************************************************/

void AD9954_GPIO_Init_HAL(void)
{
//	 GPIO_InitTypeDef GPIO_InitStruct = {0};
//	/* GPIO Ports Clock Enable */
////  __HAL_RCC_GPIOH_CLK_ENABLE();
//  //__HAL_RCC_GPIOI_CLK_ENABLE();
////  __HAL_RCC_GPIOA_CLK_ENABLE();

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOH, SDIO_Pin|DDSRS_Pin, GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(GPIOA, IO_UD_Pin|DDSSCLK_Pin, GPIO_PIN_RESET);
//  
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOI, PS0_Pin|PS1_Pin, GPIO_PIN_RESET);

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOI, DDSCS_Pin, GPIO_PIN_SET);

//  /*Configure GPIO pins : SDIO_Pin PS0_Pin PS1_Pin IO_UD_Pin
//                           DDSSCLK_Pin DDSRS_Pin */
//  GPIO_InitStruct.Pin = SDIO_Pin|DDSRS_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

//  GPIO_InitStruct.Pin = IO_UD_Pin|DDSSCLK_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//  GPIO_InitStruct.Pin = PS0_Pin|PS1_Pin|DDSCS_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
// 
//  /*Configure GPIO pin : DDSSDO_Pin */
//  GPIO_InitStruct.Pin = DDSSDO_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}

/******************************************************************************
**函数原型：AD9954_Reset()
**函数功能：AD9954复位
**输入参数：无
**输出参数：无
**备    注：也可以不复位
******************************************************************************/
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
/******************************************************************************
**函数原型：AD9954_WriteData()
**函数功能：向AD9954寄存器写入8位数据
**输入参数：无
**输出参数：无
**备    注：无
******************************************************************************/
void AD9954_WriteData(u8 Data)
{
	u8 i;
	for (i = 0; i < 8; i++)
	{
		DSCLK_L;
		HAL_Delay(1);
//		delay_us(100);
		if (Data & 0x80)
		{SDIO_H;}
		else
		{SDIO_L;}
		DSCLK_H;
//		delay_us(100);
		HAL_Delay(1);
		Data <<= 1;
	}
}
/******************************************************************************
**函数原型：AD9954_ReadData()
**函数功能：向AD9954寄存器读出8位数据
**输入参数：无
**输出参数：读出八位数据
**备    注：无
******************************************************************************/
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
/******************************************************************************
**函数原型：AD9954_Read_RegisterValue()
**函数功能：AD9954寄存器的32位数据
**输入参数：寄存器地址
**输出参数：32位寄存器数据
**备    注：无
******************************************************************************/
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
/******************************************************************************
**函数原型：AD9954_UpDate()
**函数功能：对AD9954寄存器进行更新
**输入参数：无
**输出参数：无
**备    注：无
******************************************************************************/
void AD9954_UpDate(void)
{
	IO_UD_L;
//	HAL_Delay(50);
	IO_UD_H;
	HAL_Delay(1);
	IO_UD_L;
}
/******************************************************************************
**函数原型：AD9954_Init()
**函数功能：AD9954初始化
**输入参数：无
**输出参数：无
**备    注：对CFR1和CFR2进行初始化（单音模式）
******************************************************************************/
void AD9954_Init(void)
{
	AD9954_GPIO_Init_HAL();
	AD9954_Reset();
	CS_L;

	AD9954_WriteData(CFR1);
	AD9954_WriteData(0x00); // 关闭OSK
	AD9954_WriteData(0x10);
	AD9954_WriteData(0x00);
	AD9954_WriteData(0x40); // 关闭比较器使能
//	AD9954_WriteData(0x00); // 关闭OSK
//	AD9954_WriteData(0x00);
//	AD9954_WriteData(0x00);
//	AD9954_WriteData(0x40); // 关闭比较器使能

	AD9954_WriteData(CFR2);
	AD9954_WriteData(0x00);
	AD9954_WriteData(0x08);
	AD9954_WriteData(0x54); // 10倍频 打开VCO  倍频后系统时钟400M

	#if fs>400
    #error "系统频率超过芯片最大值"
#endif
//#if fs>=250
//    AD9954_WriteData(PLL_MULTIPLIER<<3|0x04|0X03);
//#else
//    AD9954_WriteData(PLL_MULTIPLIER<<3);
//#endif
//	AD9954_WriteData(0x24);//4倍频，打开VCO控制高位，系统时钟倍频后为400M

	CS_H;
	AD9954_UpDate();
}
/******************************************************************************
**函数原型：AD9954_SetFre()
**函数功能：设置频率
**输入参数：Fre
**输出参数：无
**备    注：对FTW0寄存器进行相应的设置
******************************************************************************/
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

/******************************************************************************
**函数原型：AD9954_LinearSweepMode()
**函数功能：设置扫频模式
**输入参数：Fre
**输出参数：无
**备    注：存在问题（勿使用）
******************************************************************************/
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
	AD9954_WriteData(0x00); // 扫描模式使能
	AD9954_WriteData(0x00); // 扫描无驻留 NO-DELL和比较器失能
	

	
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
	AD9954_WriteData((u8)UpStepTime);		// Rising Sweep Ramp Rate Wor
	AD9954_WriteData((u8)(FTW_Step >> 24)); // 频率步进
	AD9954_WriteData((u8)(FTW_Step >> 16));
	AD9954_WriteData((u8)(FTW_Step >> 8));
	AD9954_WriteData((u8)(FTW_Step));

	PS0_H;

	CS_H;
	AD9954_UpDate();
}



/******************************************************************************
**函数原型：AD9954_Voltage_Control()
**函数功能：设置幅度
**输入参数：Vol
**输出参数：无
**备    注：1.ASF寄存器设置在手动OSK模式下
						2.Vol最高设置为0x3fff(代表DDS直接输出的幅值)
						3.无需配置ASF高2位
******************************************************************************/
void AD9954_Voltage_Control(u16 Vol)
{
	
	CS_L;

	AD9954_WriteData(CFR1);
	AD9954_WriteData(0x02); // OSK Enable
	AD9954_WriteData(0x00);
	AD9954_WriteData(0x00);
	AD9954_WriteData(0x40);

	AD9954_WriteData(ASF);
	AD9954_WriteData(Vol >> 8);
	AD9954_WriteData(Vol);

	
	CS_H;
	AD9954_UpDate();
}

/******************************************************************************
**函数原型：AD9954_CompMode()
**函数功能：比较器模式使能
**输入参数：无
**输出参数：无
**备    注：CFR1<6>置0 Comp Power Down
******************************************************************************/
void AD9954_CompMode(void)
{
	CS_L;

	AD9954_WriteData(CFR1);
	AD9954_WriteData(0x00); // 关闭OSK
	AD9954_WriteData(0x00);
	AD9954_WriteData(0x00);
	AD9954_WriteData(0x00); // 比较器使能

	CS_H;
	AD9954_UpDate();
}
//扫频模式还没配置成功 暂且忽略//
//void ScanMode(double StartFrequency, double EndFrequency, double StepFrequency)
//{
//	Mode_flag = 1;
//	StartFreq = StartFrequency;
//	EndFreq = EndFrequency;
//	StepFreq = StepFrequency;
//	CurFreq = StartFreq;
//	HAL_TIM_Base_Start_IT(&htim2);
//}

void SignalMode(double Freq)
{
	Mode_flag = 0; // 禁止定时
	CurFreq = Freq;
	AD9954_SetFre(CurFreq);
	//AD9954_SetFre(CurFreq - 100);
	// Dac1_Set_Vol(CurFreq * DAC_Ave);

//	TIM_Cmd(TIM13, DISABLE);
//	TIM_PrescalerConfig(TIM13, (uint16_t)(42 * 1e9 / CurFreq), TIM_PSCReloadMode_Immediate);
//	TIM_Cmd(TIM13, ENABLE);
}


/******************************************************************************
**函数原型：AD9954_Fre_Vol()
**函数功能：设置参考幅度，频率
**输入参数：Fre Vol_REF
**输出参数：无
**备    注：由于硬件设计未能满足各个频点幅度保持一样，因此软件修正
						输出电压始终保持在Vol_REF
******************************************************************************/
void AD9954_Fre_Vol(u32 Fre,double Vol_REF)
{
	double Vol;
	double Vol_Y=1.5;
	double Fre_X=0;
	
	AD9954_SetFre(Fre);
	AD9954_Voltage_Control(Vol_REF / 1.32 * 16383);
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
////	test = test + 1;
//  /* Prevent unused argument(s) compilation warning */
//  if(htim == (&htim2))
//  {
//	  test = test + 1;
//		if (!Mode_flag)
//		{
//			HAL_TIM_Base_Stop_IT(&htim2);
//		}
//		else
//		{
//			AD9954_SetFre(CurFreq);
////			HAL_TIM_Base_Stop_IT(&htim2);
////			TIM_PrescalerConfig(TIM13, (uint16_t)(42 * 1e9 / CurFreq), TIM_PSCReloadMode_Immediate);
////			HAL_TIM_Base_Start_IT(&htim2);
//			CurFreq += 1000;
//			if (CurFreq >= EndFreq)
//				CurFreq = StartFreq;
//		}
//		
//		if(test == 100)
//		{
//			test = 0;
//		
//		
//		}
//  }
//}

//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // 检查指定的TIM中断发生与否:TIM 中断源
//	{
//		if (!Mode_flag)
//			TIM_Cmd(TIM3, DISABLE);
//		else
//		{
//			AD9954_SetFre(CurFreq);
//			TIM_Cmd(TIM13, DISABLE);
//			TIM_PrescalerConfig(TIM13, (uint16_t)(42 * 1e9 / CurFreq), TIM_PSCReloadMode_Immediate);
//			TIM_Cmd(TIM13, ENABLE);
//			CurFreq += 1000;
//			if (CurFreq >= EndFreq)
//				CurFreq = StartFreq;
//		}
//	}
//	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除中断标志位
//}

