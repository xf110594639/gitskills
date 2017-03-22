
/*
介绍：独立看门狗外设用于检测和解决由于软件错误产生的故障，用于当计数器达到给定的超时时间，
触发系统复位。
IWDG由LSI提供时钟源，IWDG的计数器是从大往小计数的。
注意：IWDG有两种模式：正常模式，窗口模式。
正常模式：当向下计数器值小于0时，产生复位。
窗口模式：如果向下计数器被重加载时不在窗口内产生复位，因此喂狗(reload operation)要保证计数
器值小于IWDG_WINR寄存器值，大于0。

*/

static IWDG_HandleTypeDef   IwdgHandle;

static void MX_IWDG_Init(void)
{
/*##-3- Configure & Start the IWDG peripheral #########################################*/
  /* Set counter reload value to obtain 1 sec. IWDG TimeOut.
     IWDG counter clock Frequency = uwLsiFreq
     Set Prescaler to 32 (IWDG_PRESCALER_32)
     Timeout Period = (Reload Counter Value * 32) / uwLsiFreq
     So Set Reload Counter Value = (1 * uwLsiFreq) / 32 */
  IwdgHandle.Instance = IWDG;
  /*
	配置分频寄存器，对时钟源LSI分频后作为计数器时钟
  */
  IwdgHandle.Init.Prescaler = IWDG_PRESCALER_32;
  /*配置重加载计数器，计数值为最大喂狗间隔时间*/
  IwdgHandle.Init.Reload = (uwLsiFreq / 32);
  /*使用默认值0xFFF，配置为正常模式*/
  IwdgHandle.Init.Window = IWDG_WINDOW_DISABLE;

  if(HAL_IWDG_Init(&IwdgHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
} 