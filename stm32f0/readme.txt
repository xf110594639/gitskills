���ڣ�2017.2.22
˵����ʹ�ùٷ����빤�̣�����ͷ�ļ�����·��
·����ʼλ����main.c��

main.c�ļ��а�������ͷ�ļ�
1. #include "main.h"
2. #include "stm32f0xx_hal.h"

���ڡ�1.����һ����ͷ�ļ��������ֹ��main.c�ļ��С�

�ڡ�2.��stm32f0xx_hal.h�ļ��а���һ��ͷ�ļ�
2.1. #include "stm32f0xx_hal_conf.h"

�ڡ�2.1.��stm32f0xx_hal_conf.h�ļ��а���
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
#�����ļ���2.1.2��2.1.27������ͷ�ļ�����Ϊ��ϵ��ͬ
#ѡ"stm32f0xx_hal_gpio.h"�ļ���Ϊ����ڵ�

�ڡ�2.1.3.��stm32f0xx_hal_gpio.h�ļ�����
2.1.3.1. #include "stm32f0xx_hal_def.h"
2.1.3.2. #include "stm32f0xx_hal_gpio_ex.h"

#-------------------------------------
  �ڡ�2.1.3.2.��stm32f0xx_hal_gpio_ex.h�ļ�����
      2.1.3.2.1. #include "stm32f0xx_hal_def.h"
#���ڡ�2.1.3.2.1.���롮2.1.3.1.����ͬ���Դ�·����ֹ
#-------------------------------------

#-------------------------------------
#��֧��2.1.3.1.����ʼ

�ڡ�2.1.3.1.��stm32f0xx_hal_def.h�ļ�����
2.1.3.1.1. #include "stm32f0xx.h"
2.1.3.1.2. #include "Legacy/stm32_hal_legacy.h"
#�ļ�Legacy/stm32_hal_legacy.h�Ǵ�·��һ����֧�յ�
2.1.3.1.3. #include <stdio.h>
#�ļ�stdio.h�Ǵ�·��һ����֧�յ�

#-------------------------------------
#��֧��2.1.3.1.1.����ʼ

�ڡ�2.1.3.1.1.��stm32f0xx.h�ļ�����
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
#�����ļ���2.1.3.1.1.1.������2.1.3.1.1.16.����cpu���ļ�����Ϊ��ϵ��ͬ
#ѡ"stm32f042x6.h"�ļ���Ϊ����ڵ�

�ڡ�2.1.3.1.1.5.��stm32f042x6.h�ļ�����
2.1.3.1.1.5.1. #include "core_cm0.h"            /* Cortex-M0 processor and core peripherals */
2.1.3.1.1.5.2. #include "system_stm32f0xx.h"    /* STM32F0xx System Header */
#�ļ�system_stm32f0xx.h�Ǵ�·��һ����֧�յ�
2.1.3.1.1.5.3. #include <stdint.h>
#�ļ�stdint.h�Ǵ�·��һ����֧�յ�

�ڡ�2.1.3.1.1.5.1.��core_cm0.h�ļ�����
2.1.3.1.1.5.1.1. #include <stdint.h> 
#�ļ�stdint.h�Ǵ�·��һ����֧�յ�
2.1.3.1.1.5.1.2. #include "core_cmInstr.h"                /* Core Instruction Access */
2.1.3.1.1.5.1.3. #include "core_cmFunc.h"                 /* Core Function Access */

�ڡ�2.1.3.1.1.5.1.2.��core_cmInstr.h�ļ�����
2.1.3.1.1.5.1.2.1.  #include "cmsis_armcc.h"
#�ļ�cmsis_armcc.h�Ǵ�·��һ����֧�յ�
2.1.3.1.1.5.1.2.2.  #include "cmsis_armcc_V6.h"
2.1.3.1.1.5.1.2.3.  #include "cmsis_gcc.h"
2.1.3.1.1.5.1.2.4.  #include <cmsis_iar.h>
2.1.3.1.1.5.1.2.5.  #include <cmsis_ccs.h>
2.1.3.1.1.5.1.2.6.  #include <cmsis_csm.h>

�ڡ�2.1.3.1.1.5.1.3.��core_cmFunc.h�ļ�����
2.1.3.1.1.5.1.3.1.  #include "cmsis_armcc.h"
#�ļ�cmsis_armcc.h�Ǵ�·��һ����֧�յ�
2.1.3.1.1.5.1.3.2.  #include "cmsis_armcc_V6.h"
2.1.3.1.1.5.1.3.3.  #include "cmsis_gcc.h"
2.1.3.1.1.5.1.3.4.  #include <cmsis_iar.h>
2.1.3.1.1.5.1.3.5.  #include <cmsis_ccs.h>
2.1.3.1.1.5.1.3.6.  #include <cmsis_csm.h>

#��2.1.3.1.1.5.1.2.��core_cmInstr.h�ļ��롮2.1.3.1.1.5.1.3.��core_cmFunc.h�ļ�
#����ͷ�ļ���ͬ

#��֧��2.1.3.1.1.������
#-------------------------------------

#��֧��2.1.3.1.������
#-------------------------------------











