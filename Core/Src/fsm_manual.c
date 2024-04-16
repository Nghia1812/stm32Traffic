/*
 * fsm_manual.c
 *
 *  Created on: Mar 20, 2024
 *      Author: NGHIA
 */


#include "main.h"

/*
 * Functions related to led blinking in manual state
 * fsm_led_manual: *led* blinks every 500ms
 * */

void fsm_red_manual() {
	switch(status) {
		case MODE2:
			led_config();
			setTimer1(500);
			status = AUTO_RED;
			break;
		case AUTO_RED:
			if (timer1_flag == 1) {
				toggle_red();
				setTimer1(500);
			}
			break;
		case ADJ_RED:
			if (timer1_flag == 1) {
				toggle_red();
				setTimer1(500);
			}
			break;
		default:
			break;
	}
}

void fsm_amber_manual() {
	switch(status) {
		case MODE3:
			led_config();
			setTimer1(500);
			status = AUTO_YELLOW;
			break;
		case AUTO_YELLOW:
			if (timer1_flag == 1) {
				toggle_yellow();
				setTimer1(500);
			}
			break;
		case ADJ_YELLOW:
			if (timer1_flag == 1) {
				toggle_yellow();
				setTimer1(500);
			}
			break;
		default:
			break;
	}
}

void fsm_green_manual() {
	switch(status) {
		case MODE4:
			led_config();
			setTimer1(500);
			status = AUTO_GREEN;
			break;
		case AUTO_GREEN:
			if (timer1_flag == 1) {
				toggle_green();
				setTimer1(500);
			}
			break;
		case ADJ_GREEN:
			if (timer1_flag == 1) {
				toggle_green();
				setTimer1(500);
			}
			break;
		default:
			break;
	}
}

