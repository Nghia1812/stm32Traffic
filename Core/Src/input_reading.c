/*
 * input_reading.c
 *
 *  Created on: Mar 20, 2024
 *      Author: NGHIA
 */

#include "main.h"

#define N0_OF_BUTTONS 				       4

// timer interrupt duration is 10ms,
// 100 times in ISR
#define DURATION_FOR_AUTO_INCREASING	   100
#define BUTTON_IS_PRESSED                  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED                 GPIO_PIN_SET


// the buffer that the final result is stored after debouncing
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];

//  two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];

// flag for a button pressed more than 1 second.
static uint8_t flagForButtonPress1s[N0_OF_BUTTONS];

// define counter for automatically increasing the value
// after the button is pressed more than 1 second.
static uint16_t counterForButtonPress1s[N0_OF_BUTTONS];

static GPIO_TypeDef* button_ports[N0_OF_BUTTONS] = {B4_Btn1_GPIO_Port, B5_Btn2_GPIO_Port, B6_Btn3_GPIO_Port, B7_Btn4_GPIO_Port};
static uint16_t button_pins[N0_OF_BUTTONS] = {B4_Btn1_Pin, B5_Btn2_Pin, B6_Btn3_Pin, B7_Btn4_Pin};

void button_reading(void) {
	for (int i = 0; i < N0_OF_BUTTONS; i++) {
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(button_ports[i], button_pins[i]);

		if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer1[i];

		if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
			//if a button is pressed, start counting
			if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
				counterForButtonPress1s[i]++;
			} else {
				//the flag is turned on when 1 second has passed
				//since the button is pressed.
				flagForButtonPress1s[i] = 1;
			}
		} else {
			counterForButtonPress1s[i] = 0;
			flagForButtonPress1s[i] = 0;
		}
	}
}

unsigned char is_button_pressed(uint8_t index){
	if (index >= N0_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(unsigned char index){
	if (index >= N0_OF_BUTTONS) return 0;
	return (flagForButtonPress1s[index] == 1);
}
