
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

void LCD_sendCommand(u8 command);

void LCD_init(void);

void LCD_displayCharacter(u8 data);

void LCD_displayString(char * string);

void LCD_clearScreen();

void LCD_moveCursor(u8 row,u8 column);

void LCD_displayStringRowColumn(u8 row , u8 column , char * string);

void LCD_intgerToString(long number);

#endif /* LCD_INTERFACE_H_ */
