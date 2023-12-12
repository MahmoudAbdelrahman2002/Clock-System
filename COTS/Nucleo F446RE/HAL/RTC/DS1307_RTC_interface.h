/*
 * DS1307_RTC_interface.h
 *
 *  Created on: Dec 2, 2023
 *      Author: abdoa
 */

#ifndef DS1307_RTC_INTERFACE_H_
#define DS1307_RTC_INTERFACE_H_

/************** MAIN USER DEFINED VARIABLES ************/

typedef enum {
	_24_Hour_Mode =0,
	_12_Hour_Mode_PM,
	_12_Hour_Mode_AM

}time_format_t;

typedef struct {
	uint8_t SEC;
	uint8_t MIN;
	uint8_t HOUR;
	time_format_t time_format;
}DS1307_RTC_time_t;

typedef struct {
	uint8_t DAY;
	uint8_t DATE;
	uint8_t MONTH;
	uint8_t YEAR;
}DS1307_RTC_date_t;

typedef enum {
	SUNDAY = 1,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
}days;

/*
typedef struct {
	uint8_t SEC_REG;
	uint8_t MIN_REG;
	uint8_t HOUR_REG;
	uint8_t DAY_REG;
	uint8_t DATE_REG;
	uint8_t MONTH_REG;
	uint8_t YEAR_REG;
	uint8_t CONTROL_REG;
}DS1307_RTC_RegDef_t;

#define RTC_BASE_ADDRESS 0x00
#define DS1307_RTC ((DS1307_RTC_RegDef_t*) RTC_BASE_ADDRESS)*/


/****************** MAIN FUNCTIONS *********************/
/*
 * @function 		:	ds1307_RTC_init
 * @brief			:	Initialize RTC
 * @retval			:	Error State return CH bit. If it's is 1 so init failed
 */
uint8_t ds1307_RTC_init();

/*
 * @function 		:	ds1307_RTC_set_DateANDTime
 * @brief			:	Set date and time
 * @param			:	RTC_date structure, RTC_time structure
 */
void ds1307_RTC_set_DateANDTime(DS1307_RTC_date_t* u8_rtc_date,DS1307_RTC_time_t* u8_rtc_time);
/*
 * @function 		:	ds1307_RTC_get_DateANDTime
 * @brief			:	get date and time
 * @param			:	RTC_date structure, RTC_time structure
 */
void ds1307_RTC_get_DateANDTime(DS1307_RTC_date_t* u8_rtc_date,DS1307_RTC_time_t* u8_rtc_time);








#endif /* DS1307_RTC_INTERFACE_H_ */
