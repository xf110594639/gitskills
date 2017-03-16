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