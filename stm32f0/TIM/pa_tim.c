#define TIM1_EN 0
#define TIM2_EN 0
#define TIM3_EN 0
#define TIM14_EN 0
#define TIM16_EN 1
#define TIM17_EN 1

#if defined(TIM1_EN)
TIM_HandleTypeDef htim16;
#endif

#if defined(TIM2_EN)
TIM_HandleTypeDef htim16;
#endif

#if defined(TIM3_EN)
TIM_HandleTypeDef htim16;
#endif

#if defined(TIM14_EN)
TIM_HandleTypeDef htim16;
#endif

#if defined(TIM16_EN)
TIM_HandleTypeDef htim16;
#endif

#if defined(TIM17_EN)
TIM_HandleTypeDef htim16;
#endif

/*
配置定时器为定时输出波形功能，使用MX_TIM16_Init()
配置定时器为输出PWM波形功能，使用MX_TIM17_Init()
配置定时器2的pwm输入捕获功能，使用MX_TIM2_Init()
配置定时器2的单通道输入捕获功能，使用MX_TIM2_Init()

*/

/*
定时器多种输出配置集合函数
-------------------------------------------------------------------------
                      定时输出配置
-------------------------------------------------------------------------
*/

/* TIM16 init function
使用定时器16的输出比较模式输出波形

*/
static void MX_TIM16_Init(void)
{

  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim16.Instance = TIM16;//选择定时器
  htim16.Init.Prescaler = 47;//设置预分频值
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;//选择计数器计数方向
  htim16.Init.Period = 600;//设置自动冲加载值，也是计数器溢出值
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//选择时钟分频，一般不使用选择0分频
  htim16.Init.RepetitionCounter = 0;//设置重复计数值，一般不使用设置0
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;//设置ARR寄存器任意时刻更新，还是更新事件时才能更新
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }


  sConfigOC.OCMode = TIM_OCMODE_FORCED_INACTIVE;//选择输出比较模式
  sConfigOC.Pulse = 100;//设置比较值，当计数器值与其相等时可产生比较事件
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;//选择输出引脚电平极性，也就是输出是否通过非门
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;//选择互补输出引脚电平极性，也就是输出是否通过非门
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;//未使用
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;//未使用
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//未使用
  if (HAL_TIM_OC_ConfigChannel(&htim16, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;//未使用
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;//未使用
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;//未使用
  sBreakDeadTimeConfig.DeadTime = 0;//未使用
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;//未使用
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;//未使用
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;//使能自动输出
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim16, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
	SET_BIT(htim16.Instance->DIER,TIM_DIER_UIE);//使能更新中断

  HAL_TIM_MspPostInit(&htim16);

}



void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM16)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM16_CLK_ENABLE();

		/*使能中断，设置优先级*/
		HAL_NVIC_SetPriority(TIM16_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM16_IRQn);

  }
  else if(htim_base->Instance==TIM17)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM17_CLK_ENABLE();
  }
}


/*配置tim17输出38khz方波
系统时钟=48Mhz是定时器时钟源
将tim17计数器时钟设为16MHZ prescaler=systemcoreclock/16M-1=2
tim17输出时钟38khz，所以自动重装载寄存器值为 ARR=tim1 counter clock/tim1 output clock-1=420
*/
/* TIM17 init function 
tim17用于载波生成
*/
static void MX_TIM17_Init(void)
{

 
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim17.Instance = TIM17;//选择输出比较模式
  htim17.Init.Prescaler = 2;//设置预分频值
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;//选择计数器计数方向
  htim17.Init.Period = 420;//设置自动冲加载值，也是计数器溢出值
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//选择时钟分频，一般不使用选择0分频
  htim17.Init.RepetitionCounter = 0;//设置重复计数值，一般不使用设置0
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;//设置ARR寄存器任意时刻更新，还是更新事件时才能更新
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_OC_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }

	/*pwm1模式cnt<ccr1,通道1为有效'1'，否则为无效'0'*/
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 105;//设置比较值，在PWM模式下设置占空比
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;//高电平有效
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;//高电平有效
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;//未使用
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;//未使用
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//未使用

	/*PWM模式配置函数*/
	HAL_TIM_PWM_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1);
	
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;//使能自动输出
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim17, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim17);

}

/*
定时器多种输入捕获配置集合函数
-------------------------------------------------------------------------
                      定时输入捕获配置
-------------------------------------------------------------------------
*/

/* 
使用定时器2的pwm输入捕获功能，此模式需要通道1与通道2联合使用，
并且其中一个通道捕获事件同时作为触发事件使计数器重加载
定时器的通道2用于测量波形周期，通道1用于测量占空比
 */
static void MX_TIM2_Init(void)
{

  TIM_SlaveConfigTypeDef sSlaveConfig;
  TIM_IC_InitTypeDef sConfigIC;
  //TIM_MasterConfigTypeDef sMasterConfig;
	
	htim2.Instance = TIM2;
	/* Initialize TIM2 peripheral as follows:
       + Period = 0xFFFF
       + Prescaler = 0
       + ClockDivision = 0
       + Counter direction = Up
  */	
	htim2.Init.Period = 65535;
  htim2.Init.Prescaler = 0;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

	/*##-2- Configure the Input Capture channels ###############################*/
  /* 通道1对下降沿敏感，接收TI2FP1信号*/
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
	
	sConfigIC.ICPolarity = TIM_ICPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
	if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
	/*通道2对上升沿敏感，接收TI2FP2信号*/
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
	
	/*##-3- Configure the slave mode ###########################################*/
  /* 选择从模式，采用复位模式，上升沿触发，触发信号TI2FP2  */
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_TI2FP2;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_NONINVERTED;
  sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchronization(&htim2, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }

	/*##-4- Start the Input Capture in interrupt mode ##########################*/
  if (HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }

  /*##-5- Start the Input Capture in interrupt mode ##########################*/
  if (HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
}


/* TIM2 init function 
定时器的通道2，通道3用于输入捕获模式
*/
static void MX_TIM2_Init(void)
{

  TIM_IC_InitTypeDef sConfigIC;
  //TIM_MasterConfigTypeDef sMasterConfig;
	
	htim2.Instance = TIM2;
	/* Initialize TIM2 peripheral as follows:
       + Period = 0xFFFF
       + Prescaler = 0
       + ClockDivision = 0
       + Counter direction = Up
  */	
	htim2.Init.Period = 3999;//计数器溢出周期4000us
  htim2.Init.Prescaler = 47;//分频后计数器频率1MHZ
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

	/*##-2- Configure the Input Capture channels ###############################*/
		/*通道2对下降沿敏感，接收TI2FP2信号*/
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0xf;//8次采样电平一致认为是一个正确的边沿
	sConfigIC.ICPolarity = TIM_ICPOLARITY_FALLING;//TIM_ICPOLARITY_RISING
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
	
	/*##-3- Configure the Input Capture channels ###############################*/
		/*通道3对下降沿敏感，接收TI3FP3信号*/
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0xf;//8次采样电平一致认为是一个正确的边沿
	sConfigIC.ICPolarity = TIM_ICPOLARITY_FALLING;//TIM_ICPOLARITY_RISING
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
	
	/*##-4- Start the Input Capture in interrupt mode ##########################*/
  if (HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
	
	 if (HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }

}

