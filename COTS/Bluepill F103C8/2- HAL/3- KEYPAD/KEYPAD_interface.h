
#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#include "KEYPAD_config.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
void KEYPAD_Init(void);
u8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_INTERFACE_H_ */
