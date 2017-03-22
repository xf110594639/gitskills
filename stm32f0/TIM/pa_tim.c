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
���ö�ʱ��Ϊ��ʱ������ι��ܣ�ʹ��MX_TIM16_Init()
���ö�ʱ��Ϊ���PWM���ι��ܣ�ʹ��MX_TIM17_Init()
���ö�ʱ��2��pwm���벶���ܣ�ʹ��MX_TIM2_Init()
���ö�ʱ��2�ĵ�ͨ�����벶���ܣ�ʹ��MX_TIM2_Init()

*/

/*
��ʱ������������ü��Ϻ���
-------------------------------------------------------------------------
                      ��ʱ�������
-------------------------------------------------------------------------
*/

/* TIM16 init function
ʹ�ö�ʱ��16������Ƚ�ģʽ�������

*/
static void MX_TIM16_Init(void)
{

  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim16.Instance = TIM16;//ѡ��ʱ��
  htim16.Init.Prescaler = 47;//����Ԥ��Ƶֵ
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;//ѡ���������������
  htim16.Init.Period = 600;//�����Զ������ֵ��Ҳ�Ǽ��������ֵ
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//ѡ��ʱ�ӷ�Ƶ��һ�㲻ʹ��ѡ��0��Ƶ
  htim16.Init.RepetitionCounter = 0;//�����ظ�����ֵ��һ�㲻ʹ������0
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;//����ARR�Ĵ�������ʱ�̸��£����Ǹ����¼�ʱ���ܸ���
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }


  sConfigOC.OCMode = TIM_OCMODE_FORCED_INACTIVE;//ѡ������Ƚ�ģʽ
  sConfigOC.Pulse = 100;//���ñȽ�ֵ����������ֵ�������ʱ�ɲ����Ƚ��¼�
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;//ѡ��������ŵ�ƽ���ԣ�Ҳ��������Ƿ�ͨ������
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;//ѡ�񻥲�������ŵ�ƽ���ԣ�Ҳ��������Ƿ�ͨ������
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;//δʹ��
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;//δʹ��
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//δʹ��
  if (HAL_TIM_OC_ConfigChannel(&htim16, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;//δʹ��
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;//δʹ��
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;//δʹ��
  sBreakDeadTimeConfig.DeadTime = 0;//δʹ��
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;//δʹ��
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;//δʹ��
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;//ʹ���Զ����
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim16, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
	SET_BIT(htim16.Instance->DIER,TIM_DIER_UIE);//ʹ�ܸ����ж�

  HAL_TIM_MspPostInit(&htim16);

}



void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM16)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM16_CLK_ENABLE();

		/*ʹ���жϣ��������ȼ�*/
		HAL_NVIC_SetPriority(TIM16_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM16_IRQn);

  }
  else if(htim_base->Instance==TIM17)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM17_CLK_ENABLE();
  }
}


/*����tim17���38khz����
ϵͳʱ��=48Mhz�Ƕ�ʱ��ʱ��Դ
��tim17������ʱ����Ϊ16MHZ prescaler=systemcoreclock/16M-1=2
tim17���ʱ��38khz�������Զ���װ�ؼĴ���ֵΪ ARR=tim1 counter clock/tim1 output clock-1=420
*/
/* TIM17 init function 
tim17�����ز�����
*/
static void MX_TIM17_Init(void)
{

 
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim17.Instance = TIM17;//ѡ������Ƚ�ģʽ
  htim17.Init.Prescaler = 2;//����Ԥ��Ƶֵ
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;//ѡ���������������
  htim17.Init.Period = 420;//�����Զ������ֵ��Ҳ�Ǽ��������ֵ
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//ѡ��ʱ�ӷ�Ƶ��һ�㲻ʹ��ѡ��0��Ƶ
  htim17.Init.RepetitionCounter = 0;//�����ظ�����ֵ��һ�㲻ʹ������0
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;//����ARR�Ĵ�������ʱ�̸��£����Ǹ����¼�ʱ���ܸ���
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_OC_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }

	/*pwm1ģʽcnt<ccr1,ͨ��1Ϊ��Ч'1'������Ϊ��Ч'0'*/
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 105;//���ñȽ�ֵ����PWMģʽ������ռ�ձ�
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;//�ߵ�ƽ��Ч
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;//�ߵ�ƽ��Ч
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;//δʹ��
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;//δʹ��
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//δʹ��

	/*PWMģʽ���ú���*/
	HAL_TIM_PWM_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1);
	
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;//ʹ���Զ����
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim17, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim17);

}

/*
��ʱ���������벶�����ü��Ϻ���
-------------------------------------------------------------------------
                      ��ʱ���벶������
-------------------------------------------------------------------------
*/

/* 
ʹ�ö�ʱ��2��pwm���벶���ܣ���ģʽ��Ҫͨ��1��ͨ��2����ʹ�ã�
��������һ��ͨ�������¼�ͬʱ��Ϊ�����¼�ʹ�������ؼ���
��ʱ����ͨ��2���ڲ����������ڣ�ͨ��1���ڲ���ռ�ձ�
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
  /* ͨ��1���½������У�����TI2FP1�ź�*/
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
	
	sConfigIC.ICPolarity = TIM_ICPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
	if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
	/*ͨ��2�����������У�����TI2FP2�ź�*/
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
	
	/*##-3- Configure the slave mode ###########################################*/
  /* ѡ���ģʽ�����ø�λģʽ�������ش����������ź�TI2FP2  */
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
��ʱ����ͨ��2��ͨ��3�������벶��ģʽ
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
	htim2.Init.Period = 3999;//�������������4000us
  htim2.Init.Prescaler = 47;//��Ƶ�������Ƶ��1MHZ
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

	/*##-2- Configure the Input Capture channels ###############################*/
		/*ͨ��2���½������У�����TI2FP2�ź�*/
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0xf;//8�β�����ƽһ����Ϊ��һ����ȷ�ı���
	sConfigIC.ICPolarity = TIM_ICPOLARITY_FALLING;//TIM_ICPOLARITY_RISING
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
	
	/*##-3- Configure the Input Capture channels ###############################*/
		/*ͨ��3���½������У�����TI3FP3�ź�*/
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0xf;//8�β�����ƽһ����Ϊ��һ����ȷ�ı���
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

