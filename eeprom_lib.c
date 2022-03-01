#include "stm32f2xx_hal.h"
#include "stm32f2xx_it.h"
#include <stdbool.h>
#include "string.h"
#include "main.h"
#include "math.h"

/*------------------------------DEFINES---------------------------------------*/


//#define EepromAddress     0x50
//#define MemAddress        0x00

/*---------------------------WRITE FUNCTION-----------------------------------*/

/*
* hi2c : Pointer to a I2C_HandleTypeDef structure that contains
*        the configuration information for the specified I2C.
* dataWrite : pointer to data write
* dataWrite_Size : Amount of data you want write (sizeof(dataWrite))
*/

int Eeprom_Write(I2C_HandleTypeDef *hi2c, uint16_t EepromAddress, uint16_t MemAddress, uint8_t *dataWrite, uint16_t dataWrite_Size)
{
       for(int i = 1; i <= (dataWrite_Size / 16) + 1; i++) // i - page
      {
          while((dataWrite_Size - 16) > 0)
          {
               while(HAL_I2C_Mem_Write(hi2c,(uint16_t)EepromAddress,(uint16_t)MemAddress,1, dataWrite,(uint16_t)16,1000)!= HAL_OK);
               dataWrite_Size -= 16;
               dataWrite += 16;
               MemAddress += 16;
          }
          while(HAL_I2C_Mem_Write(hi2c,(uint16_t)EepromAddress,(uint16_t)MemAddress, 1, dataWrite,(uint16_t)dataWrite_Size,1000)!= HAL_OK);
      }
   return 1;
}


/*----------------------------READ FUNCTION-----------------------------------*/

/*
* hi2c : Pointer to a I2C_HandleTypeDef structure that contains
*        the configuration information for the specified I2C.
* dataRead : pointer to data read 
* dataRead_Size : Amount of data you want to read (sizeof(dataRead))
*/

int Eeprom_Read(I2C_HandleTypeDef *hi2c, uint16_t EepromAddress, uint16_t MemAddress, uint8_t *dataRead, uint16_t dataRead_Size)
{
     int TimeOut;
     for(int i = 1; i <= (dataRead_Size / 16) + 1; i++) // i - page
     {          
          while((dataRead_Size - 16 * i) > 0)
          {
                TimeOut = 0;
                while(HAL_I2C_Mem_Read(hi2c, (uint16_t)EepromAddress, (uint16_t)MemAddress, 1, dataRead,(uint16_t)16, 1000)!= HAL_OK && TimeOut < 10)
                {
                    TimeOut++;
                }
        
                dataRead_Size -= 16;
                dataRead += 16;
                MemAddress += 16;
          }
          TimeOut = 0;
          while(HAL_I2C_Mem_Read(hi2c,(uint16_t)EepromAddress,(uint16_t)MemAddress,1,dataRead,(uint16_t)dataRead_Size,1000)!= HAL_OK && TimeOut < 10)
          {
		TimeOut++;
          }
     }
  return 1;
}
