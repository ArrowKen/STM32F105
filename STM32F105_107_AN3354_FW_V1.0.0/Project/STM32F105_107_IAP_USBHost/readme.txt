/**
  @page STM32F105_107_IAP_USBHost STM32F105_107 in-application programming using a USB host Readme file
 
  @verbatim
  ******************** (C) COPYRIGHT 2011 STMicroelectronics *******************
  * @file    readme.txt
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-July-2011
  * @brief   This is the readme file of the in-application programming using 
  *          USB host project.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
  * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
  * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
  * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
  * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  @endverbatim
 
 @par Description

This directory contains a set of sources files and pre-configured projects that 
build the In-Application Programming (IAP, through USB HOST) porgram.

@par Directory contents 

    - "STM32F105_107_IAP_USBHost\inc":            	   Contains the IAP firmware header files 
    - STM32F105_107_IAP_USBHost/inc/command.h     	   This file provides all the headers of the command functions.
    - STM32F105_107_IAP_USBHost/inc/flash_layer.h      This file provides all the the headers of the flash_layer functions.
    - STM32F105_107_IAP_USBHost/inc/usbh_usr.h         This file provides all the headers of usbh_usr functions.
    - STM32F105_107_IAP_USBHost/inc/stm32f10x_conf.h   Library Configuration file
    - STM32F105_107_IAP_USBHost/inc/stm32f10x_it.h     Header for stm32F1xx_it.c
	
    - "STM32F105_107_IAP_USBHost\src": 				         Contains the IAP firmware source files
    - STM32F105_107_IAP_USBHost/src/main.c             Main program
    - STM32F105_107_IAP_USBHost/src/stm32f10x_it.c     Interrupt handlers
    - STM32F105_107_IAP_USBHost/src/flash_layer.c      This file provides all the flash_layer functions: lock, unlock, erase, program.
    - STM32F105_107_IAP_USBHost/src/usbh_usr.c         This file contains the usb_user configuration, it control the usb status.
    - STM32F105_107_IAP_USBHost/src/command.c          This file provides functions related to IAP menu: upload, download, jump
    - STM32F105_107_IAP_USBHost/src/usb_bsp.c		       This file implements the board support package for the USB host library
	
 - "STM32F105_107_IAP_USBHost\binary_template": contains the binary template firmware source files
 - "STM32F105_107_IAP_USBHost\EWARM": 			    contains preconfigured project for EWARM toolchain
 - "STM32F105_107_IAP_USBHost\MDK-ARM": 		    contains preconfigured project for MDK-ARM toolchain
 - "STM32F105_107_IAP_USBHost\RIDE": 			      contains preconfigured project for RIDE toolchain
 - "STM32F105_107_IAP_USBHost\TrueSTUDIO":	   	contains preconfigured project for TrueSTUDIO toolchain
 

@par Hardware and Software environment

  - This example runs on STM32F105/107 Devices.
  
  - This example has been tested with STM3210C-EVAL RevB and can be easily 
    tailored to any other development board.
    
  - STM3210C-EVAL Set-up
    - Use the Key push-button.

@par How to use it ? 

In order to make the program work, you must do the following:

  1. Generate a binary image using the preconfigured project provided in the directory
      "Project\STM32F105_107_IAP_USBHost\binary_template" . 
  2. Program the internal Flash with the IAP. 
  3. Connect the USB flash pen drive to the board.
  4. To run the IAP application, keep the Key push-button pressed at Reset. 

  In order to load the IAP code, you have do the following:
   - EWARM
      - Open the Project.eww workspace
      - Rebuild all files: Project->Rebuild all
      - Load project image: Project->Debug
      - Run program: Debug->Go(F5)

   - RIDE
      - Open the Project.rprj project
      - Rebuild all files: Project->build project
      - Load project image: Debug->start(ctrl+D)
      - Run program: Debug->Run(ctrl+F9)

   - MDK-ARM
      - Open the Project.uvproj project
      - Rebuild all files: Project->Rebuild all target files
      - Load project image: Debug->Start/Stop Debug Session
      - Run program: Debug->Run (F5)

   - TrueSTUDO
      - Open the TrueSTUDIO toolchain.
      - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace directory.
      - Click on File->Import, select General->'Existing Projects into Workspace' and then click "Next". 
      - Browse to the TrueSTUDIO workspace directory, select the project:
          - STM3210C-EVAL: to configure the project for STM32F105/107 devices
      - Under Windows->Preferences->General->Workspace->Linked Resources, add 
        a variable path named "CurPath" which points to the folder containing
        "Libraries", "Project" and "Utilities" folders.
      - Rebuild all project files: Select the project in the "Project explorer" 
        window then click on Project->build project menu.
      - Run program: Run->Debug (F11)

 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 */
