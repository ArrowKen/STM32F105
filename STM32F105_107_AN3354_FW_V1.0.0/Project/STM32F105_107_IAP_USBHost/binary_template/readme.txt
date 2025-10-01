/**
  @page binary_template AN3354 Binary Template Readme file
  
  @verbatim
  ******************** (C) COPYRIGHT 2011 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-July-2011
  * @brief   Description of the binary_template directory.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

@par Description

This directory contains a set of sources files that build the application to be
loaded into Flash memory using In-Application Programming (IAP, through USB HOST).

To build such application, some special configuration has to be peformed:
1. Set the program load address at 0x08008000, using your toolchain linker file.
2. Relocate the vector table at address 0x08008000, using 
   the "NVIC_SetVectorTable" function.
 
The SysTick example provided within the STM32F10x Standard Peripherals library 
examples is used as illustration.
This example configures the SysTick to generate a time base equal to 1 ms.
The system clock is set to the maximum system frequency, the SysTick is clocked by 
the AHB clock (HCLK). A "Delay" function is implemented based on the SysTick 
end-of-count event.
Four LEDs are toggled with a timing defined by the Delay function.


@par Directory contents 

 - "STM32F105_107_IAP_USBHost\binary_template\EWARM": This folder contains a pre-configured project file 
													  that produces a binary image of SysTick example to 
													  be loaded with IAP.

 - "STM32F105_107_IAP_USBHost\binary_template\RIDE": This folder contains a pre-configured project file 
													 that produces a binary image of SysTick example to be 
													 loaded with IAP.

 - "STM32F105_107_IAP_USBHost\binary_template\MDK-ARM": This folder contains a pre-configured project file 
														that produces a binary image of SysTick example to be 
														loaded with IAP.

 - "STM32F105_107_IAP_USBHost\binary_template\TrueSTUDIO": This folder contains a pre-configured project file 
														   that produces a binary image of SysTick example to be 
														   loaded with IAP.
                           
 - "STM32F105_107_IAP_USBHost\binary_template\inc": contains the binary_template firmware header files 
     - STM32F105_107_IAP_USBHost/binary_template/inc/stm32f10x_conf.h    Library Configuration file
     - STM32F105_107_IAP_USBHost/binary_template/inc/stm32f10x_it.h      Header for stm32f10x_it.c
     - STM32F105_107_IAP_USBHost/binary_template/inc/main.h              Header for main.c
     
 - "STM32F105_107_IAP_USBHost\binary_template\src": contains the binary_template firmware source files 
     - STM32F105_107_IAP_USBHost/binary_template/src/main.c              Main program
     - STM32F105_107_IAP_USBHost/binary_template/src/stm32f10x_it.c      Interrupt handlers
     - STM32F105_107_IAP_USBHost/binary_template/src/system_stm32f10x.c  STM32F10x system source file

@par Hardware and Software environment 

  - This example runs on STM32F10x Connectivity line Devices.
  
  - This example has been tested with STMicroelectronics  STM3210C-EVAL (Connectivity line), 
    evaluation board and can be easily tailored to any other supported device and development board.    
     
  - STM3210C-EVAL Set-up 
    - Use LED1, LED2, LED3 and LED4 connected respectively to PD.07, PD.13, PF.03
      and PD.04 pins
      
@par How to use it ?  

In order to load the SysTick example with the IAP, you must do the following:

 - EWARM (v5.50 and later):
    - Open the SysTick.eww workspace
    - In the workspace toolbar select the project config:
        - STM3210C-EVAL: to configure the project for STM32 Connectivity line devices
    - Rebuild all files: Project->Rebuild all
    - A binary file "SysTick.bin" will be generated under "STM3210C-EVAL\Exe" folder depending 
	  on the selected configuration.  
    - Finally load this image with IAP application

 - RIDE:
    - Open the SysTick.rprj project
    - In the configuration toolbar(Project->properties) select the project config:
        - STM3210C-EVAL: to configure the project for STM32 Connectivity line devices
    - Rebuild all files: Project->build project
    - Go to "Utilities\Binary" directory and run "hextobin.bat"
    - A binary file "SysTick.bin" will be generated under "\STM3210C-EVAL",  
      folder depending on the selected configuration. 
    - Finally load this image with IAP application

 - MDK-ARM:
    - Open the SysTick.uvproj project
    - In the build toolbar select the project config:
        - STM3210C-EVAL: to configure the project for STM32 Connectivity line devices
    - Rebuild all files: Project->Rebuild all target files
    - Go to "Utilities\Binary" directory and run "axftobin.bat"
    - A binary file "STM3210C-EVAL_SysTick.bin", will be generated under "\STM3210C-EVAL". 
      folder depending on the selected configuration. 
    - Finally load this image with IAP application
 
 - TrueSTUDIO:
    - Open the TrueSTUDIO toolchain.
    - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace directory.
    - Click on File->Import, select General->'Existing Projects into Workspace' and then click "Next". 
    - Browse to the TrueSTUDIO workspace directory, select the project:
        - STM3210C-EVAL: to load the project for STM32 Connectivity line devices
    - Under Windows->Preferences->General->Workspace->Linked Resources, add 
      a variable path named "CurPath" which points to the folder containing
      "Libraries", "Project" and "Utilities" folders.
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Go to "Utilities\Binary" directory and run "TrueSTUDIO_elf2bin.bat"
    - A binary file "STM3210C-EVAL_SysTick.bin", will be generated under "\Debug" folder
    - Finally load this image with IAP application

@note
 - Connectivity line devices are STM32F105xx and STM32F107xx microcontrollers.

 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 */
