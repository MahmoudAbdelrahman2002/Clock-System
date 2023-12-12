/*
 * DS1307_RTC_private.h
 *
 *  Created on: Dec 2, 2023
 *      Author: abdoa
 */

#ifndef DS1307_RTC_PRIVATE_H_
#define DS1307_RTC_PRIVATE_H_


#define DS1307_I2C_SALVE_ADDRESS_W (0x68<<1)
#define DS1307_I2C_SALVE_ADDRESS_R ((0x68<<1)|1)
#define TIME_FORMAT_MASK 			6
#define _12_HOUR_MASK        		5
#define MCU_ADDRESS 0b00000010

//addresses of the RTC regs
#define DS1307_SEC_ADD 		(0x00)  	  /* Address of seconds register */
#define DS1307_MIN_ADD 		(0x01)   	  /* Address of minutes register */
#define DS1307_HR_ADD 		(0x02)   	  /* Address of hours register	 */
#define DS1307_DAY_ADD 		(0x03)  	  /* Address of day register 	 */
#define DS1307_DATE_ADD 	(0x04) 		  /* Address of date register	 */
#define DS1307_MONTH_ADD 	(0x05) 		  /* Address of month register	 */
#define DS1307_YEAR_ADD 	(0x06) 		  /* Address of year register 	 */

#endif /* DS1307_RTC_PRIVATE_H_ */
