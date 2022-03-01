#ifndef EEPROM_LIB_H
#define EEPROM_LIB_H

#include "main.h"

int Eeprom_Write(I2C_HandleTypeDef *hi2c, uint16_t EepromAddress, uint16_t MemAddress, uint8_t *dataWrite, uint16_t dataWrite_Size);
int Eeprom_Read(I2C_HandleTypeDef *hi2c, uint16_t EepromAddress, uint16_t MemAddress, uint8_t *dataRead, uint16_t dataRead_Size);
//void Eeprom_Erase (I2C_HandleTypeDef *hi2c, uint8_t *dataWrite);

#endif /*EEPROM_LIB_H*/