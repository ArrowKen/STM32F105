/**
  ******************************************************************************
  * @file    IAP/inc/command.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22/07/2011
  * @brief   Header file for command.c 
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _COMMAND_H
#define _COMMAND_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "flash_layer.h"
#include "usbh_usr.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
   
#define CMD_UPLOAD                         ((uint8_t)0x01) /* Reads memory starting from an
                                                                  address specified by the application */
#define CMD_DOWNLOAD                       ((uint8_t)0x02) /* Writes RAM or Flash memory starting 
                                                            from an address specified by the application */
#define CMD_JUMP                           ((uint8_t)0x03) /* Jumps to user application code located
                                                                 in the internal Flash memory or in SRAM */
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void COMMAND_IAPExecuteApplication(void);
void COMMAND_UPLOAD(void);
void COMMAND_JUMP(void);
void COMMAND_DOWNLOAD(void);
void COMMAND_ProgramFlashMemory(void);

#ifdef __cplusplus
}
#endif

#endif  /* _COMMAND_H */

/*******************(C)COPYRIGHT 2011 STMicroelectronics *****END OF FILE******/
