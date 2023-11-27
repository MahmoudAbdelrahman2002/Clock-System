
#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/*******************************************************************************
*                        		Configurations                                 *
*******************************************************************************/

//#define STANDARD_KEYPAD

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                GPIO_u8_GPIOA
#define KEYPAD_FIRST_ROW_PIN_ID           GPIO_u8_PIN4

#define KEYPAD_COL_PORT_ID                GPIO_u8_GPIOA
#define KEYPAD_FIRST_COL_PIN_ID           GPIO_u8_PIN0

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            GPIO_u8_LOW
#define KEYPAD_BUTTON_RELEASED           GPIO_u8_HIGH


#endif /* KEYPAD_CONFIG_H_ */
