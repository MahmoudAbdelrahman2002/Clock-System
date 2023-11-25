/********************************************************************************************/
/********************************************************************************************/
/**************************		Date:    13 September 2023	            		*************/
/**************************		Layer:   HAL								   	*************/
/**************************		SWC:	 RTC									*************/
/**************************		Version: 1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

/********************************************************************************************/
/* Guard of file will call one time in .c  			                                        */
/********************************************************************************************/
#ifndef RTC_PRIVATE_H
#define RTC_PRIVATE_H

#define DS1307_SEC_ADD 		(0x00)  	  /* Address of seconds register */
#define DS1307_MIN_ADD 		(0x01)   	  /* Address of minutes register */
#define DS1307_HR_ADD 		(0x02)   	  /* Address of hours register	 */
#define DS1307_DAY_ADD 		(0x03)  	  /* Address of day register 	 */
#define DS1307_DATE_ADD 	(0x04) 		  /* Address of date register	 */
#define DS1307_MONTH_ADD 	(0x05) 		  /* Address of month register	 */
#define DS1307_YEAR_ADD 	(0x06) 		  /* Address of year register 	 */

#define DS1307_FIRST_LOC 			0x00
#define DS1307_WRITE_ARR_SIZE 		0x08
#define DS1307_RECEIVE_ARR_SIZE 	0x07

#define DS1307_SLAVE_ADDRESS_WRITE  0b11010000
#define DS1307_SLAVE_ADDRESS_READ   0b11010001

/*  control bits    */
#define CH (1<<7)
#define HR (1<<6)

uint8_t device_data[2];

/*  private function prototypes     */
uint8_t Ds1307_read_register(uint8_t reg);
void  Ds1307_write_register(uint8_t reg,uint8_t data);

#endif
/********************************************************************************************/
/* END OF FILE: RTC_private.h                                                               */
/********************************************************************************************/
