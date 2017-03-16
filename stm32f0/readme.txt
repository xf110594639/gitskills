日期：2017.2.22
说明：使用官方代码工程，分析头文件包含路径
路径起始位置在main.c。

main.c文件中包含两个头文件
1. #include "main.h"
2. #include "stm32f0xx_hal.h"

由于‘1.’下一级无头文件，因此终止与main.c文件中。

在‘2.’stm32f0xx_hal.h文件中包含一个头文件
2.1. #include "stm32f0xx_hal_conf.h"

在‘2.1.’stm32f0xx_hal_conf.h文件中包含
2.1.1. #include "main.h"
2.1.2.#include "stm32f0xx_hal_rcc.h"
2.1.3. #include "stm32f0xx_hal_gpio.h"
2.1.4.  #include "stm32f0xx_hal_dma.h"
2.1.5. #include "stm32f0xx_hal_cortex.h"
2.1.6. #include "stm32f0xx_hal_adc.h"
2.1.7. #include "stm32f0xx_hal_can.h"
2.1.8. #include "stm32f0xx_hal_cec.h"
2.1.9. #include "stm32f0xx_hal_comp.h"
2.1.10. #include "stm32f0xx_hal_crc.h"
2.1.11. #include "stm32f0xx_hal_dac.h"
2.1.12. #include "stm32f0xx_hal_flash.h"
2.1.13. #include "stm32f0xx_hal_i2c.h"
2.1.14. #include "stm32f0xx_hal_i2s.h"
2.1.15. #include "stm32f0xx_hal_irda.h"
2.1.16. #include "stm32f0xx_hal_iwdg.h"
2.1.17. #include "stm32f0xx_hal_pcd.h"
2.1.18. #include "stm32f0xx_hal_pwr.h"
2.1.19. #include "stm32f0xx_hal_rtc.h"
2.1.20. #include "stm32f0xx_hal_smartcard.h"
2.1.21. #include "stm32f0xx_hal_smbus.h"
2.1.22. #include "stm32f0xx_hal_spi.h"
2.1.23. #include "stm32f0xx_hal_tim.h"
2.1.24. #include "stm32f0xx_hal_tsc.h"
2.1.25. #include "stm32f0xx_hal_uart.h"
2.1.26. #include "stm32f0xx_hal_usart.h"
2.1.27. #include "stm32f0xx_hal_wwdg.h"
#以上文件从2.1.2到2.1.27是外设头文件，因为关系等同
#选"stm32f0xx_hal_gpio.h"文件作为这个节点

在‘2.1.3.’stm32f0xx_hal_gpio.h文件包含
2.1.3.1. #include "stm32f0xx_hal_def.h"
2.1.3.2. #include "stm32f0xx_hal_gpio_ex.h"

#-------------------------------------
  在‘2.1.3.2.’stm32f0xx_hal_gpio_ex.h文件包含
      2.1.3.2.1. #include "stm32f0xx_hal_def.h"
#由于‘2.1.3.2.1.’与‘2.1.3.1.’相同所以此路径终止
#-------------------------------------

#-------------------------------------
#分支‘2.1.3.1.’开始

在‘2.1.3.1.’stm32f0xx_hal_def.h文件包含
2.1.3.1.1. #include "stm32f0xx.h"
2.1.3.1.2. #include "Legacy/stm32_hal_legacy.h"
#文件Legacy/stm32_hal_legacy.h是此路径一个分支终点
2.1.3.1.3. #include <stdio.h>
#文件stdio.h是此路径一个分支终点

#-------------------------------------
#分支‘2.1.3.1.1.’开始

在‘2.1.3.1.1.’stm32f0xx.h文件包含
2.1.3.1.1.1.  #include "stm32f030x6.h"
2.1.3.1.1.2.  #include "stm32f030x8.h"
2.1.3.1.1.3.  #include "stm32f031x6.h"
2.1.3.1.1.4.  #include "stm32f038xx.h"
2.1.3.1.1.5.  #include "stm32f042x6.h"
2.1.3.1.1.6.  #include "stm32f048xx.h"
2.1.3.1.1.7.  #include "stm32f051x8.h"
2.1.3.1.1.8.  #include "stm32f058xx.h"
2.1.3.1.1.9.  #include "stm32f070x6.h"
2.1.3.1.1.10. #include "stm32f070xb.h"
2.1.3.1.1.11. #include "stm32f071xb.h"
2.1.3.1.1.12. #include "stm32f072xb.h"
2.1.3.1.1.13. #include "stm32f078xx.h"
2.1.3.1.1.14. #include "stm32f091xc.h"
2.1.3.1.1.15. #include "stm32f098xx.h"
2.1.3.1.1.16. #include "stm32f030xc.h"    
#以上文件‘2.1.3.1.1.1.’到‘2.1.3.1.1.16.’是cpu都文件，因为关系等同
#选"stm32f042x6.h"文件作为这个节点

在‘2.1.3.1.1.5.’stm32f042x6.h文件包含
2.1.3.1.1.5.1. #include "core_cm0.h"            /* Cortex-M0 processor and core peripherals */
2.1.3.1.1.5.2. #include "system_stm32f0xx.h"    /* STM32F0xx System Header */
#文件system_stm32f0xx.h是此路径一个分支终点
2.1.3.1.1.5.3. #include <stdint.h>
#文件stdint.h是此路径一个分支终点

在‘2.1.3.1.1.5.1.’core_cm0.h文件包含
2.1.3.1.1.5.1.1. #include <stdint.h> 
#文件stdint.h是此路径一个分支终点
2.1.3.1.1.5.1.2. #include "core_cmInstr.h"                /* Core Instruction Access */
2.1.3.1.1.5.1.3. #include "core_cmFunc.h"                 /* Core Function Access */

在‘2.1.3.1.1.5.1.2.’core_cmInstr.h文件包含
2.1.3.1.1.5.1.2.1.  #include "cmsis_armcc.h"
#文件cmsis_armcc.h是此路径一个分支终点
2.1.3.1.1.5.1.2.2.  #include "cmsis_armcc_V6.h"
2.1.3.1.1.5.1.2.3.  #include "cmsis_gcc.h"
2.1.3.1.1.5.1.2.4.  #include <cmsis_iar.h>
2.1.3.1.1.5.1.2.5.  #include <cmsis_ccs.h>
2.1.3.1.1.5.1.2.6.  #include <cmsis_csm.h>

在‘2.1.3.1.1.5.1.3.’core_cmFunc.h文件包含
2.1.3.1.1.5.1.3.1.  #include "cmsis_armcc.h"
#文件cmsis_armcc.h是此路径一个分支终点
2.1.3.1.1.5.1.3.2.  #include "cmsis_armcc_V6.h"
2.1.3.1.1.5.1.3.3.  #include "cmsis_gcc.h"
2.1.3.1.1.5.1.3.4.  #include <cmsis_iar.h>
2.1.3.1.1.5.1.3.5.  #include <cmsis_ccs.h>
2.1.3.1.1.5.1.3.6.  #include <cmsis_csm.h>

#‘2.1.3.1.1.5.1.2.’core_cmInstr.h文件与‘2.1.3.1.1.5.1.3.’core_cmFunc.h文件
#包含头文件相同

#分支‘2.1.3.1.1.’结束
#-------------------------------------

#分支‘2.1.3.1.’结束
#-------------------------------------











