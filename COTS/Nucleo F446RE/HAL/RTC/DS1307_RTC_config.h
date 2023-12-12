/*
 * DS1307_RTC_config.h
 *
 *  Created on: Dec 2, 2023
 *      Author: abdoa
 */

#ifndef DS1307_RTC_CONFIG_H_
#define DS1307_RTC_CONFIG_H_
#include "../../LIB/Stm32F466xx.h"
#include "../../MCAL/GPIO/GPIO_interface.h"


#define DS1307_I2C 				I2C1
#define DS1307_I2C_SDA_PORT		PORTB
#define DS1307_I2C_SDA_PIN		PIN9
#define DS1307_I2C_SCL_PIN		PIN8
#define I2C_Num					I2C_NUMBER_1





#endif /* DS1307_RTC_CONFIG_H_ */
