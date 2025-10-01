/**
  ******************************************************************************
  * @file    command.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22/07/2011
  * @brief   This file provides all the IAP command functions.
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
#include "command.h"

/** @addtogroup USBH_USER
  * @{
  */

/** @defgroup IAP_OVER_USB_COMMAND
  * @brief
  * @{
  */


/* External variables --------------------------------------------------------*/
extern uint8_t CMD_index;
extern uint8_t joystick_use;
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Download_FileTypeDef Download_File [9];
static uint8_t RAM_Buf[BUFFER_SIZE] =
  {
    0x00
  };
static uint32_t tmp_program_counter = 0x00, tmp_read_size = 0x00 , ram_address = 0x00;
static uint32_t Last_PGAddress = APPLICATIONADDRESS;
const uint8_t MSG_UPLOAD_GOING[]        = "> UPLOAD ON GOING                        ";
const uint8_t MSG_UPLOAD_DONE[]         = "> UPLOAD DONE                            ";
const uint8_t MSG_ROP1[]                = ">      Can not access flash memory       ";
const uint8_t MSG_ROP2[]                = "> Please disable the Read Out Protection ";
const uint8_t MSG_DIR_ERROR[]           = "> Can not open directory                 ";
const uint8_t MSG_DOWNLOAD_GOING[]      = "> DOWNLOAD ON GOING                      ";
const uint8_t MSG_DOWNLOAD_DONE[]       = "> DOWNLOAD DONE                          ";
const uint8_t MSG_FLASH_PG_ERROR[]      = "> Flash programming error                ";
const uint8_t MSG_FLASH_ER_ERROR[]      = "> Flash erase error                      ";
const uint8_t MSG_FILE_SIZE_ERROR[]     = "> File size exceed 224Kbyte              ";
const uint8_t MSG_SELECT_MENU[]         = "> Please select a menu                   ";
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  COMMAND_IAPExecuteApplication
  * @param  None
  * @retval None
  */
void COMMAND_IAPExecuteApplication(void)
{
  /* Execute the command switch the command index */
  switch (CMD_index)
  {
      /* Reads all flash memory */
    case CMD_UPLOAD:
      COMMAND_UPLOAD();
      break;

      /* Writes Flash memory */
    case CMD_DOWNLOAD:
      COMMAND_DOWNLOAD();
      break;

      /* Jumps to user application code located in the internal Flash memory */
    case CMD_JUMP:
      COMMAND_JUMP();
      break;
  }
}

/**
  * @brief IAP Read all flash memory
  * @param  None
  * @retval None
  */
void COMMAND_UPLOAD(void)
{
  __IO uint32_t address = FLASH_STARTADDRESS;
  __IO uint32_t counter_read = 0x00;
  uint32_t tmp_counter = 0x00, index_offset = 0x00;
  FlagStatus readoutstatus = SET;

  /* Get the read out protection status */
  readoutstatus = FLASH_LAYER_ReadOutProtectionStatus();

  if (readoutstatus == RESET)
  {
    /* Remove UPLOAD file if exist on flash disk */
    rmfile(&efs.myFs, "UPLOAD.BIN");

    /* Init written byte counter */
    index_offset = 0x00;

    /* Open binary file to write on it */
    if ((HCD_IsDeviceConnected(&USB_OTG_FS_dev) == 1) && (file_fopen(&file, &efs.myFs, "UPLOAD.BIN", 'w') == 0))
    {
      /* Clear LCD msg */
      USBH_USR_LCDClearPart(90, 90);

      /* Display LCD message */
      LCD_DisplayStringLine(80, (uint8_t *)MSG_UPLOAD_GOING);

      /* Read flash memory */
      while ((index_offset != FLASH_SIZE) && (HCD_IsDeviceConnected(&USB_OTG_FS_dev) == 1))
      {
        for (counter_read = 0; counter_read < BUFFER_SIZE; counter_read++)
        {
          /* Check the read bytes versus the end of flash */
          if (index_offset + counter_read != FLASH_SIZE)
          {
            tmp_counter = counter_read;
            RAM_Buf[tmp_counter] = (*(uint8_t*)(address++));
          }
          /* In this case all flash was read */
          else
          {
            break;
          }
        }

        /* Write buffer to file */
        file_write(&file, counter_read, RAM_Buf);

        /* Number of byte written  */
        index_offset = index_offset + counter_read;
      }

      /* Display LCD message */
      LCD_DisplayStringLine(80, (uint8_t *)MSG_UPLOAD_DONE);

      /* Close file and filesystem */
      file_fclose(&file);
      fs_umount(&efs.myFs);
    }
  }
  else
  {
    /* Display LCD message ROP active */
    LCD_DisplayStringLine(80, (uint8_t *)MSG_ROP1);
    LCD_DisplayStringLine(90, (uint8_t *)MSG_ROP2);
  }
}

/**
  * @brief  IAP write memory
  * @param  None
  * @retval None
  */
void COMMAND_DOWNLOAD(void)
{
  __IO uint8_t index_struct = 0x00, status = NEXT_MENU;
  __IO uint32_t erase_address = 0x00;
  uint8_t tmp = 0x00;

  /* Get the read out protection status */
  if (ls_openDir(&list, &(efs.myFs), "/") != 0)
  {
    /* Clear LCD msg */
    USBH_USR_LCDClearPart(80, 80);
    /* Could not open the selected directory */
    LCD_DisplayStringLine(90, (uint8_t *)MSG_DIR_ERROR);
  }
  else
  {
    /* Joystick is used now to select the image to be downloaded */
    joystick_use = IAP_DOWNLOAD_SELECT;

    /* Check the flash disk binary image */
    status = USBH_USR_DisplayBinaryFlashContents(Download_File);

    switch (status)
    {
        /* Binary image selected */
      case  NEXT_DOWNLOAD:

        tmp = Seclect_FileCounter;
        /* Search the selected image */
        while (Download_File[index_struct].file_index != tmp)
        {
          index_struct++;
        }

        /* Open the binary file to be downloaded */
        if (file_fopen(&fileR, &efs.myFs, (char *)&Download_File[index_struct].filenameString[0], 'r') == 0)
        {

          if (fileR.FileSize > FLASH_SIZE - IAP_SIZE)
          {
            /* Clear LCD message*/
            USBH_USR_LCDClearPart(80, 230);
            /* Display LCD message flash erase error */
            LCD_DisplayStringLine(80, (uint8_t *)MSG_FILE_SIZE_ERROR);
            /* Display LCD message flash erase error */
            LCD_DisplayStringLine(90, (uint8_t *)MSG_SELECT_MENU);

            /* Joystick is used now to select the image to be downloaded */
            joystick_use = IAP_DOWNLOAD_SELECT;
          }
          else
          {
            /* Clear LCD msg */
            USBH_USR_LCDClearPart(80, 80);

            /* Display LCD message */
            LCD_DisplayStringLine(90, (uint8_t *)MSG_DOWNLOAD_GOING);

            /* Erase necessary page to download image */
            for (erase_address = APPLICATIONADDRESS; (erase_address < (APPLICATIONADDRESS + fileR.FileSize)) && (erase_address < FLASH_ENDADDRESS); \
                 erase_address = erase_address + PAGE_SIZE)
            {
              if (FLASH_LAYER_ErasePage (erase_address) != FLASH_COMPLETE)
              {
                /* Clear LCD message*/
                USBH_USR_LCDClearPart(80, 230);

                /* Display LCD message flash erase error */
                LCD_DisplayStringLine(100, (uint8_t *)MSG_FLASH_ER_ERROR);
                while (1);
              }
            }

            /* Program flash memory */
            COMMAND_ProgramFlashMemory();

            /* Display LCD message */
            LCD_DisplayStringLine(90, (uint8_t *)MSG_DOWNLOAD_DONE);

            /* Close file and filesystem */
            file_fclose(&fileR);
          }
          /* Clear LCD flash disk binary image */
          USBH_USR_LCDClearPart(120, 230);

          /* Joystick is used now to select IAP command */
          joystick_use = IAP_COMMAND_SELECT;
        }
        break;

      default:
        break;
    }
  }
}

/**
  * @brief  IAP jump to user program
  * @param  None
  * @retval None
  */
void COMMAND_JUMP(void)
{
  /* Software reset */
  NVIC_SystemReset();
}

/**
  * @brief  COMMAND_ProgramFlashMemory
  * @param  None
  * @retval None
  */
void COMMAND_ProgramFlashMemory(void)
{
  __IO uint32_t program_counter = 0x00, read_size = 0x00;
  uint8_t read_flag = TRUE;

  /* RAM Address Initialization */
  ram_address = (uint32_t) & RAM_Buf;

  /* Erase address init */
  Last_PGAddress = APPLICATIONADDRESS;

  /* While file still contain data */
  while (read_flag == TRUE)
  {
    /* Read maximum "BUFFER_SIZE" Kbyte from the selected file  */
    read_size = file_read(&fileR, BUFFER_SIZE, RAM_Buf);

    /* Temp variable */
    tmp_read_size = read_size;

    /* The read data < "BUFFER_SIZE" Kbyte */
    if (tmp_read_size < BUFFER_SIZE)
    {
      read_flag = FALSE;
    }

    /* Program flash memory */
    for (program_counter = tmp_read_size; program_counter != 0; program_counter -= 4)
    {
      tmp_program_counter = program_counter;
      /* Write word into flash memory */
      if (FLASH_LAYER_ProgramWord((Last_PGAddress - tmp_program_counter + tmp_read_size), \
                                  *(__IO uint32_t *)(ram_address - program_counter + tmp_read_size)) != FLASH_COMPLETE)
      {
        /* Clear LCD message*/
        USBH_USR_LCDClearPart(80, 230);

        /* Display LCD message flash programing error */
        LCD_DisplayStringLine(100, (uint8_t *)MSG_FLASH_PG_ERROR);
        while (1);
      }
    }

    /* Update last programmed address value */
    Last_PGAddress = Last_PGAddress + tmp_read_size;
  }
}
/**
  * @}
  */

/**
  * @}
  */

/*******************(C)COPYRIGHT 2011 STMicroelectronics *****END OF FILE******/
