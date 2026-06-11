//#include "pwm.h"

//// 全局定时器句柄，需在头文件中声明
//TIM_HandleTypeDef htim3;

////PWM输出初始化
////arr：自动重装值
////psc：时钟预分频数
//void PWM_Init(uint16_t arr, uint16_t psc)
//{  
//    GPIO_InitTypeDef GPIO_InitStructure = {0};
//    TIM_OC_InitTypeDef sConfigOC = {0};

//    // 使能TIM3和GPIOA时钟
//    __HAL_RCC_TIM3_CLK_ENABLE();
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//  
//    // 配置PA7为复用推挽输出（TIM3_CH2）
//    GPIO_InitStructure.Pin = GPIO_PIN_7;
//    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStructure.Pull = GPIO_NOPULL;
//    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_50MHz;
//    GPIO_InitStructure.Alternate = GPIO_AF2_TIM3;  // 根据具体芯片确认复用映射
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//    // 初始化TIM3句柄
//    htim3.Instance = TIM3;
//    htim3.Init.Prescaler = psc;
//    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
//    htim3.Init.Period = arr;
//    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
//    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
//    {
//        Error_Handler();
//    }

//    // 配置PWM输出通道
//    sConfigOC.OCMode = TIM_OCMODE_PWM2;
//    sConfigOC.Pulse = 0;  // 初始占空比为0
//    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
//    {
//        Error_Handler();
//    }

//    // 启动PWM输出
//    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
//}

//// 设置PWM输出频率（系统时钟84MHz）
//void PWM_Set(uint32_t f0)
//{
//    uint32_t arr_t;
//    
//    // TIM3挂载在APB1总线上，84MHz系统时钟下APB1时钟为42MHz
//    // 定时器时钟为APB1时钟的2倍，即84MHz
//    if(f0 < 10000)
//    {
//        // 低频时使用预分频
//        htim3.Instance->PSC = 840 - 1;  // 840分频，84MHz/840=100kHz
//        arr_t = 100000 / f0;            // 基于100kHz计数时钟计算周期
//        arr_t--;
//        htim3.Instance->ARR = arr_t;
//        htim3.Instance->CCR2 = arr_t / 2;  // 50%占空比
//    }
//    else
//    {
//        // 高频时不使用预分频
//        htim3.Instance->PSC = 0;         // 不分频，84MHz计数时钟
//        arr_t = 84000000 / f0;           // 基于84MHz计数时钟计算周期
//        arr_t--;
//        htim3.Instance->ARR = arr_t;
//        htim3.Instance->CCR2 = arr_t / 2;  // 50%占空比
//    }
//}

//// 错误处理函数
//void Error_Handler(void)
//{
//    while(1)
//    {
//        // 错误状态，可以添加LED闪烁等提示
//    }
//}
//    