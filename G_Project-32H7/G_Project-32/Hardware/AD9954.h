/**
  ******************************************************************************
  * @file    AD9954.h
  * @brief   AD9954 DDS芯片驱动头文件
  * @details AD9954是Analog Devices公司的高性能直接数字合成器芯片
  *          主要特性：
  *          - 400MHz内部时钟
  *          - 14位DAC分辨率
  *          - 频率、相位、幅度可编程
  *          - 支持线性扫频模式
  *          - SPI串行接口
  *          
  *          本驱动实现：
  *          - 基本频率和幅度控制
  *          - 线性扫频功能
  *          - 寄存器读写操作
  *          - 硬件初始化配置
  ******************************************************************************
  */

#ifndef __AD9954__H__
#define __AD9954__H__

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"  // STM32 HAL库

/* Exported defines - GPIO引脚定义 ----------------------------------------*/
/**
 * @brief  AD9954 SDIO数据引脚
 * @details 双向数据线，用于串行数据传输
 *          连接到STM32的PH14引脚
 */
#define SDIO_Pin GPIO_PIN_14
#define SDIO_GPIO_Port GPIOH

/**
 * @brief  AD9954 PS0功能选择引脚
 * @details 功能选择引脚0，与PS1配合选择工作模式
 *          连接到STM32的PI0引脚
 */
#define PS0_Pin GPIO_PIN_0
#define PS0_GPIO_Port GPIOI

/**
 * @brief  AD9954 PS1功能选择引脚
 * @details 功能选择引脚1，与PS0配合选择工作模式
 *          连接到STM32的PI2引脚
 */
#define PS1_Pin GPIO_PIN_2
#define PS1_GPIO_Port GPIOI

/**
 * @brief  AD9954 IO_UPDATE更新引脚
 * @details 更新引脚，上升沿时将内部寄存器值更新到输出
 *          连接到STM32的PC10引脚
 */
#define IO_UD_Pin GPIO_PIN_10
#define IO_UD_GPIO_Port GPIOC

/**
 * @brief  AD9954 SCLK串行时钟引脚
 * @details 串行时钟输入，用于同步数据传输
 *          连接到STM32的PC11引脚
 */
#define DDSSCLK_Pin GPIO_PIN_11
#define DDSSCLK_GPIO_Port GPIOC

/**
 * @brief  AD9954 RESET复位引脚
 * @details 硬件复位引脚，低电平有效
 *          连接到STM32的PH15引脚
 */
#define DDSRS_Pin GPIO_PIN_15
#define DDSRS_GPIO_Port GPIOH

/**
 * @brief  AD9954 CS片选引脚
 * @details 片选引脚，低电平有效
 *          连接到STM32的PI3引脚
 */
#define DDSCS_Pin GPIO_PIN_3
#define DDSCS_GPIO_Port GPIOI

/**
 * @brief  AD9954 SDO串行数据输出引脚
 * @details 串行数据输出，用于读取寄存器值
 *          连接到STM32的PI1引脚
 */
#define DDSSDO_Pin GPIO_PIN_1
#define DDSSDO_GPIO_Port GPIOI

/* Exported defines - GPIO操作宏 ------------------------------------------*/
/**
 * @brief  PS1引脚控制宏
 * @details PS1_L: 设置PS1为低电平
 *          PS1_H: 设置PS1为高电平
 */
#define PS1_L  HAL_GPIO_WritePin(GPIOI, PS1_Pin, GPIO_PIN_RESET)
#define PS1_H  HAL_GPIO_WritePin(GPIOI, PS1_Pin, GPIO_PIN_SET)

/**
 * @brief  PS0引脚控制宏
 * @details PS0_L: 设置PS0为低电平
 *          PS0_H: 设置PS0为高电平
 */
#define PS0_L  HAL_GPIO_WritePin(GPIOI, PS0_Pin, GPIO_PIN_RESET)
#define PS0_H  HAL_GPIO_WritePin(GPIOI, PS0_Pin, GPIO_PIN_SET)

/**
 * @brief  SDIO数据引脚控制宏
 * @details SDIO_L: 设置SDIO为低电平
 *          SDIO_H: 设置SDIO为高电平
 */
#define SDIO_L  HAL_GPIO_WritePin(GPIOH, SDIO_Pin, GPIO_PIN_RESET)
#define SDIO_H  HAL_GPIO_WritePin(GPIOH, SDIO_Pin, GPIO_PIN_SET)

/**
 * @brief  SCLK时钟引脚控制宏
 * @details DSCLK_L: 设置SCLK为低电平
 *          DSCLK_H: 设置SCLK为高电平
 */
#define DSCLK_L  HAL_GPIO_WritePin(GPIOC, DDSSCLK_Pin, GPIO_PIN_RESET)
#define DSCLK_H  HAL_GPIO_WritePin(GPIOC, DDSSCLK_Pin, GPIO_PIN_SET)

/**
 * @brief  CS片选引脚控制宏
 * @details CS_L: 设置CS为低电平（选中芯片）
 *          CS_H: 设置CS为高电平（取消选中）
 */
#define CS_L  HAL_GPIO_WritePin(GPIOI, DDSCS_Pin, GPIO_PIN_RESET)
#define CS_H  HAL_GPIO_WritePin(GPIOI, DDSCS_Pin, GPIO_PIN_SET)

/**
 * @brief  RESET复位引脚控制宏
 * @details RESET_L: 设置RESET为低电平（复位有效）
 *          RESET_H: 设置RESET为高电平（复位无效）
 */
#define RESET_L  HAL_GPIO_WritePin(GPIOH, DDSRS_Pin, GPIO_PIN_RESET)
#define RESET_H  HAL_GPIO_WritePin(GPIOH, DDSRS_Pin, GPIO_PIN_SET)

/**
 * @brief  IO_UPDATE更新引脚控制宏
 * @details IO_UD_L: 设置IO_UPDATE为低电平
 *          IO_UD_H: 设置IO_UPDATE为高电平（触发更新）
 */
#define IO_UD_L  HAL_GPIO_WritePin(GPIOC, IO_UD_Pin, GPIO_PIN_RESET)
#define IO_UD_H  HAL_GPIO_WritePin(GPIOC, IO_UD_Pin, GPIO_PIN_SET)

/**
 * @brief  SDO数据读取宏
 * @details 读取SDO引脚的电平状态
 */
#define SDO HAL_GPIO_ReadPin(DDSSDO_GPIO_Port,DDSSDO_Pin)

/* Exported defines - AD9954寄存器地址 -----------------------------------*/
#define CFR1 0X00    ///< 控制功能寄存器1
#define CFR2 0X01    ///< 控制功能寄存器2
#define ASF  0X02    ///< 幅度比例因子寄存器
#define ARR  0X03    ///< 幅度斜率寄存器
#define FTW0 0X04    ///< 频率调谐字0（通道0）
#define POW0 0X05    ///< 相位偏移字0（通道0）
#define FTW1 0X06    ///< 频率调谐字1（通道1）
#define NLSCW 0X07   ///< 无停留控制字
#define PLSCW 0X08   ///< 正线性扫频控制字
#define RSCW0 0X07   ///< 斜坡控制字0
#define RSCW1 0X08   ///< 斜坡控制字1
#define RSCW2 0X09   ///< 斜坡控制字2
#define RSCW3 0X0A   ///< 斜坡控制字3
#define RAM  0X0B    ///< RAM控制寄存器

/* Exported defines - 常量定义 --------------------------------------------*/
/**
 * @brief  无停留模式标志
 * @details 用于线性扫频模式，表示在频率点不停留
 */
#define No_Dwell 0X80

/**
 * @brief  频率转换系数
 * @details Fre_Ave = 2^32 / 400MHz = 10.73741824
 *          用于将频率值转换为32位频率调谐字
 *          计算公式：FTW = Frequency × Fre_Ave
 */
#define Fre_Ave 10.73741824f

/**
 * @brief  DAC幅度转换系数
 * @details DAC_Ave = 40MHz / 2^16 = 0.00088225
 *          用于将幅度值转换为14位DAC值
 *          注意：这里使用40MHz作为参考时钟
 */
#define DAC_Ave 0.00008825f

/* Exported function prototypes ---------------------------------------------*/
/**
 * @brief  AD9954 GPIO初始化函数（HAL版本）
 * @retval None
 * @details 初始化AD9954相关的GPIO引脚
 *          包括数据、时钟、控制等所有引脚的配置
 */
extern void AD9954_GPIO_Init_HAL(void);

/**
 * @brief  AD9954硬件复位函数
 * @retval None
 * @details 通过RESET引脚对AD9954进行硬件复位
 *          复位后芯片恢复到默认状态
 */
extern void AD9954_Reset(void);

/**
 * @brief  AD9954写入单字节数据
 * @param  Data: 要写入的8位数据
 * @retval None
 * @details 通过SPI接口向AD9954写入一个字节的数据
 *          使用软件SPI实现，不依赖硬件SPI外设
 */
extern void AD9954_WriteData(uint8_t Data);

/**
 * @brief  AD9954更新输出函数
 * @retval None
 * @details 通过IO_UPDATE引脚触发内部寄存器更新
 *          使新设置的频率、相位、幅度参数生效
 */
extern void AD9954_UpDate(void);

/**
 * @brief  AD9954初始化函数
 * @retval None
 * @details 完整的AD9954初始化流程
 *          包括GPIO初始化、硬件复位、基本配置等
 */
extern void AD9954_Init(void);

/**
 * @brief  AD9954设置输出频率
 * @param  Fre: 目标频率值（Hz）
 * @retval None
 * @details 设置AD9954的输出频率
 *          频率范围：0Hz - 400MHz
 *          使用32位频率调谐字实现高精度控制
 */
extern void AD9954_SetFre(double Fre);

/**
 * @brief  AD9954读取单字节数据
 * @retval uint8_t: 读取到的8位数据
 * @details 通过SPI接口从AD9954读取一个字节的数据
 *          用于读取寄存器值或状态信息
 */
extern uint8_t AD9954_ReadData(void);

/**
 * @brief  读取AD9954寄存器值
 * @param  Register: 寄存器地址
 * @retval uint32_t: 读取到的32位寄存器值
 * @details 读取指定地址的32位寄存器内容
 *          用于调试和状态监控
 */
extern uint32_t AD9954_Read_RegisterValue(uint8_t Register);

/**
 * @brief  AD9954线性扫频模式设置
 * @param  FreMin: 起始频率（Hz）
 * @param  FreMax: 结束频率（Hz）
 * @param  Frestep: 频率步进（Hz）
 * @param  UpStepTime: 步进时间（ms）
 * @retval None
 * @details 配置AD9954为线性扫频模式
 *          从起始频率线性扫描到结束频率
 */
extern void AD9954_LinearSweepMode(double FreMin, double FreMax, double Frestep, uint8_t UpStepTime);

/**
 * @brief  扫描模式函数
 * @param  StartFrequency: 起始频率
 * @param  EndFrequency: 结束频率
 * @param  StepFrequency: 步进频率
 * @retval None
 * @details 实现频率扫描功能
 *          用于系统频率响应测试
 */
extern void ScanMode(double StartFrequency, double EndFrequency, double StepFrequency);

/**
 * @brief  AD9954幅度控制函数
 * @param  Vol: 幅度控制值（0-16383）
 * @retval None
 * @details 设置AD9954的输出幅度
 *          幅度范围：0 - 16383（14位DAC满量程）
 *          16383对应最大输出幅度
 */
extern void AD9954_Voltage_Control(uint16_t Vol);

/**
 * @brief  信号模式函数
 * @param  Freq: 信号频率
 * @retval None
 * @details 设置AD9954输出指定频率的连续信号
 *          用于生成测试信号
 */
extern void SignalMode(double Freq);

/**
 * @brief  频率和幅度同时设置函数
 * @param  Fre: 频率值
 * @param  Vol_REF: 参考幅度值
 * @retval None
 * @details 同时设置AD9954的输出频率和幅度
 *          原子操作，避免频率和幅度更新不同步
 */
void AD9954_Fre_Vol(uint32_t Fre, double Vol_REF);

#endif /* __AD9954__H__ */
