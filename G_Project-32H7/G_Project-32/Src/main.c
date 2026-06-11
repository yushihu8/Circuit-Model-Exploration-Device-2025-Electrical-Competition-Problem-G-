/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : 主程序文件 - 自适应数字滤波器设计系统
  * @details        : 本程序实现了一个完整的自适应滤波器设计系统，包括：
  *                   1. 频率扫描获取系统频率响应
  *                   2. 基于最小二乘法拟合模拟滤波器系数
  *                   3. 双线性变换转换为数字滤波器
  *                   4. 滤波器类型自动识别
  *                   5. 系数加载到外部滤波器芯片
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_system.h"    // 板级支持包，包含所有硬件驱动头文件
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// 用户自定义类型定义区域
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// 用户自定义宏定义区域
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// 用户自定义宏函数区域
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */
// 用户私有函数原型声明区域
complex sample_array[SAMPLE_NUM];  // 频率扫描结果存储数组
                                     // 存储各频率点的传递函数H(jω)值
                                     // SAMPLE_NUM = 250，对应200Hz-50kHz扫频点
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// 用户私有代码区域（函数定义等）
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  // 用户代码区域1：在初始化之前的代码
  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  // 用户代码区域2：HAL初始化后的自定义初始化
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  // 用户代码区域3：系统时钟配置后的初始化
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  // 用户代码区域4：外设初始化后的主要应用代码
  
  AD9954_Init();  // 初始化AD9954 DDS芯片，用于生成扫频信号

  // 定义滤波器系数结构体变量
  analog_coef ac;  // 模拟滤波器系数结构体
  digital_coef dc; // 数字滤波器系数结构体
  uint16_t cmd = 0x00; // 临时命令变量（用于调试）

  // ========== 调试代码段（已注释）==========
  // 以下代码用于单步调试和硬件测试，正常使用时保持注释状态
  
//	printf("start");
//  AD9954_SetFre(200);                    // 设置DDS输出频率为200Hz
//  AD9954_Voltage_Control(16383);          // 设置DDS输出幅度（最大值）

  
  printf("START\n");  // 打印开始标志，表示滤波器设计流程开始

  // ========== 自适应滤波器设计主流程 ==========
  
  // 步骤1：频率扫描 - 获取系统在200Hz-50kHz范围内的频率响应
  // 扫描结果存储在sample_array数组中，每个元素为复数形式的传递函数值
  freq_scan(sample_array);
  
  // 步骤2：计算矩阵系数 - 基于频率响应数据构建最小二乘拟合的系数矩阵
  // 这些系数将用于后续的线性方程组求解
  coef_calc(sample_array);
  
  // 步骤3：求解矩阵方程 - 通过5×5线性方程组求解模拟滤波器系数
  // 返回的ac结构体包含模拟滤波器的分子(b0,b1,b2)和分母(a1,a2)系数
  ac = matrix_calc();
  
  // 步骤4：双线性变换 - 将模拟滤波器转换为数字滤波器
  // 同时进行Q31格式量化，便于硬件实现
  dc = bilinear_transform_quant(&ac);
  
  // 步骤5：滤波器类型识别 - 根据频率响应特性判断滤波器类型
  // 可识别：低通、高通、带通、带阻滤波器
  get_filter_type(&ac);
  
  // 步骤6：系数加载 - 将计算得到的数字滤波器系数通过SPI加载到外部滤波器芯片
  coef_lode(&dc);
//  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // 主循环：滤波器设计完成后，系统进入空闲状态
    // 可以在此处添加其他功能，如实时监控、参数调整等
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// 用户代码区域4：用户自定义函数
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  // 用户代码区域：错误处理调试信息
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();  // 禁用所有中断，防止中断干扰错误处理
  
  // 无限循环：系统进入安全停止状态
  while (1)
  {
    // 可以在此处添加错误指示功能：
    // - 点亮LED指示灯
    // - 通过串口输出错误信息
    // - 记录错误日志到Flash
    // - 触发看门狗复位等
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
