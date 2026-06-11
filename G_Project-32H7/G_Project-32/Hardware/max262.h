#ifndef _MAX262_H_ 
#define _MAX262_H_  

#include "stm32f4xx.h"                  // Device header
#include "tim.h"
// 引脚定义
#define A0_PIN         GPIO_PIN_2
#define A1_PIN         GPIO_PIN_4
#define A2_PIN         GPIO_PIN_6
#define A3_PIN         GPIO_PIN_3
#define D0_PIN         GPIO_PIN_5
#define D1_PIN         GPIO_PIN_7
#define WR_PIN         GPIO_PIN_10
#define CLK_PIN        GPIO_PIN_1

#define A0_PORT        GPIOD
#define A1_PORT        GPIOD
#define A2_PORT        GPIOD
#define A3_PORT        GPIOD
#define D0_PORT        GPIOD
#define D1_PORT        GPIOD
#define WR_PORT        GPIOG
#define CLK_PORT       GPIOA

// 控制信号宏定义
#define setWr    HAL_GPIO_WritePin(WR_PORT, WR_PIN, GPIO_PIN_SET)
#define resetWr  HAL_GPIO_WritePin(WR_PORT, WR_PIN, GPIO_PIN_RESET)

#define PI 3.141592653 
 
extern enum {MODE_1=0,MODE_2,MODE_3,MODE_4} workMode;
extern enum {CH_A=0,CH_B} channel; 


void MAX262_Init(void);//IO口初始化
void MAX262_Write(uint8_t add,uint8_t dat2bit); //写两比特的数据到某地址 
void Set_Af(uint8_t datF); //设置A通道F值      
void Set_AQ(uint8_t datQ); //设置A通道Q值   
void Set_Bf(uint8_t datF);  // 设置B通道F值  
void Set_BQ(uint8_t datQ); // 设置B通道Q值 
  

float lhp_WorkFclk(float f0,float Q,uint8_t workMode,uint8_t channel);//设置低通和高通滤波器工作并取得时钟频率fclk ，切换模块上的跳线帽即可更改低通或高通
float bp_WorkFclk(float fh,float fl,uint8_t workMode,uint8_t channel); //设置带通滤波器工作并取得时钟频率fclk 
float bs_WorkFclk(float f0,float Q,uint8_t workMode,uint8_t channel);   //设置陷波滤波器工作并取得时钟频率fclk 
float ap_WorkFclk(float f0,float Q,uint8_t channel);//设置全通滤波器工作并取得时钟频率fclk 

void PWM_Set(uint32_t f0);

#endif



