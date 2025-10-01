/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22/07/2011
  * @brief   IAP thru USB host main file
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_msc_core.h"
#include "flash_layer.h"

/** @addtogroup USBH_USER
  * @{
  */

/** @defgroup IAP_OVER_USB_MAIN
  * @brief
  * @{
  */

/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction Jump_To_Application;
uint32_t JumpAddress;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  main
  *         Main routine for IAP application
  * @param  None
  * @retval int
  */
int main(void)
{
  /* At this point System clock is already set to 72MHz
  using CMSIS SystemInit() function */

  /* STM32 evalboard user initializations*/
  BSP_Init();

  /* Display LCD message */
  USBH_USR_IAPInit();

  /* Flash unlock */
  FLASH_LAYER_FlashUnlock();

  /* Test if Key push-button on STM3210C-EVAL Board is pressed */
  if (STM_EVAL_PBGetState(BUTTON_KEY)  == RESET)
  {
    /* Init Host Library */
    USBH_Init(&USB_OTG_FS_dev, &MSC_cb , &USR_Callbacks);

    while (1)
    {
      /* Host Task handler */
      USBH_Process();
    }
  }
  /* Keep the user application running */
  else
  {
    /* Test if user code is programmed starting from address "ApplicationAddress" */
    if (((*(__IO uint32_t*)APPLICATIONADDRESS) & 0x2FFE0000 ) == 0x20000000)
    {
      /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (APPLICATIONADDRESS + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) APPLICATIONADDRESS);
      Jump_To_Application();
    }
  }
  while (1)
  {}
}


#ifdef USE_FULL_ASSERT
/**
  * @brief  assert_failed
  *         Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  File: pointer to the source file name
  * @param  Line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
