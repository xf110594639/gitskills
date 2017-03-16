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