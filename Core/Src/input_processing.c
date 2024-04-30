/*
 * input_processing.c
 *
 *  Created on: Mar 20, 2024
 *      Author: NGHIA
 */
#include <stdio.h>

#include "main.h"
#include "global.h"
#include "input_processing.h"
#include "input_reading.h"
#include "timer.h"


enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};

enum ButtonState button_0_state = BUTTON_PRESSED; //Change mode
enum ButtonState button_1_state = BUTTON_PRESSED; //Increment time
enum ButtonState button_2_state = BUTTON_PRESSED; //Decrement time
enum ButtonState button_3_state = BUTTON_PRESSED; //Save time

void fsm_button_processing() {
	switch (button_0_state) {
		case BUTTON_RELEASED:
			if (is_button_pressed(0)) {
				button_0_state = BUTTON_PRESSED;
				if ((status == RED_GREEN) || (status == RED_YELLOW) || (status == GREEN_RED) || (status == YELLOW_RED))	status = MODE2;
				if (status == AUTO_RED) 	status = MODE3;
				if (status == AUTO_YELLOW) 	status = MODE4;
				if (status == AUTO_GREEN) 	status = MODE1;
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(0)) {
				button_0_state = BUTTON_RELEASED;
			} else {
				if (is_button_pressed_1s(0)) {
					button_0_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!is_button_pressed(0)) {
				button_0_state = BUTTON_RELEASED;
			}
			// do nothing, wait for the button to be released
			break;
	}

	switch (button_1_state) {
		case BUTTON_RELEASED:
			if (is_button_pressed(1)) {
				button_1_state = BUTTON_PRESSED;
				if (status == AUTO_RED || status == ADJ_RED) {
					status = ADJ_RED;
					T_RED++;
					if (T_RED >= 99) T_RED = 1;

				}
				if (status == AUTO_YELLOW || status == ADJ_YELLOW) {
					status = ADJ_YELLOW;
					T_YELLOW++;
					if (T_YELLOW >= 5) T_YELLOW = 1;

				}
				if (status == AUTO_GREEN || status == ADJ_GREEN) {
					status = ADJ_GREEN;
					T_GREEN++;
					if (T_GREEN >= 99) T_GREEN = 1;

				}
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(1)) {
				button_1_state = BUTTON_RELEASED;
			} else {
				if (is_button_pressed_1s(1)) {
					button_1_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!is_button_pressed(1)) {
				button_1_state = BUTTON_RELEASED;
			}
			// do nothing, wait for the button to be released
			break;
	}

	switch (button_2_state) {
		case BUTTON_RELEASED:
			if (is_button_pressed(2)) {
				button_2_state = BUTTON_PRESSED;
				if (status == AUTO_RED || status == ADJ_RED) {
					status = ADJ_RED;
					T_RED--;
					if (T_RED <= 0) T_RED = 1;

				}
				if (status == AUTO_YELLOW || status == ADJ_YELLOW) {
					status = ADJ_YELLOW;
					T_YELLOW--;
					if (T_YELLOW <= 0) T_YELLOW = 1;

				}
				if (status == AUTO_GREEN || status == ADJ_GREEN) {
					status = ADJ_GREEN;
					T_GREEN--;
					if (T_GREEN <= 0) T_GREEN = 1;

				}
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(2)) {
				button_2_state = BUTTON_RELEASED;
			} else {
				if (is_button_pressed_1s(2)) {
					button_2_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!is_button_pressed(2)) {
				button_2_state = BUTTON_RELEASED;
			}
			// do nothing, wait for the button to be released
			break;
	}

	switch (button_3_state) {
		case BUTTON_RELEASED:
			if (is_button_pressed(3)) {
				button_3_state = BUTTON_PRESSED;
				if (status == ADJ_RED) {
					status = AUTO_RED;
					if (T_RED <= T_YELLOW) T_RED = T_YELLOW + 1;
					T_GREEN = T_RED - T_YELLOW;
				}

				if (status == ADJ_YELLOW) {
					status = AUTO_YELLOW;
					if (T_RED <= T_YELLOW) T_RED = T_YELLOW + 1;
					T_GREEN = T_RED - T_YELLOW;
				}
				if (status == ADJ_GREEN) {
					status = AUTO_GREEN;
					if (T_YELLOW + T_GREEN >= 99) {
						T_YELLOW = 4;
						T_GREEN = 95;
					}
					T_RED = T_YELLOW + T_GREEN;
				}
				char str[18];
				sprintf(str, "G%d R%d Y%d\n", T_GREEN, T_RED, T_YELLOW);
				HAL_UART_Transmit(&huart2,(uint8_t*) str, sizeof(str), HAL_MAX_DELAY);
			}

			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(3)) {
				button_3_state = BUTTON_RELEASED;
			} else {
				if (is_button_pressed_1s(3)) {
					button_3_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!is_button_pressed(3)) {
				button_3_state = BUTTON_RELEASED;
			}
			// do nothing, wait for the button to be released
			break;
	}
}
