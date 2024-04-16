/*
 * fsm_automatic.c
 *
 *  Created on: Mar 20, 2024
 *      Author: NGHIA
 */


#include "main.h"



int t_road_1 = 0, t_road_2 = 0;

void fsm_automatic() {
	switch (status) {
		case INIT:
			//TODO: wake MCU up by PC
			status = MODE1;
			break;
		case MODE1:
			led_config();
			t_road_1 = T_RED;
			t_road_2 = T_GREEN;
			setTimer4(1000);
			status = RED_GREEN;
			break;
		case RED_GREEN:
			led_config();
			if (timer4_flag == 1) {
				t_road_1--;
				t_road_2--;
				if (t_road_2 <= 0) { // next state pre-setup
					t_road_2 = T_YELLOW;
					status = RED_YELLOW; // Change state
				}
				setTimer4(1000);
			}
			break;
		case RED_YELLOW:
			led_config();
			if (timer4_flag == 1) {
				t_road_1--;
				t_road_2--;
				if (t_road_1 <= 0) { // next state pre-setup
					t_road_1 = T_GREEN;
					t_road_2 = T_RED;
					status = GREEN_RED; // Change state
				}
				setTimer4(1000);
			}
			break;
		case GREEN_RED:
			led_config();
			if (timer4_flag == 1) {
				t_road_1--;
				t_road_2--;
				if (t_road_1 <= 0) { // next state pre-setup
					t_road_1 = T_YELLOW;
					status = YELLOW_RED; // Change state
				}
				setTimer4(1000);
			}
			break;
		case YELLOW_RED:
			led_config();
			if (timer4_flag == 1) {
				t_road_1--;
				t_road_2--;
				if (t_road_1 <= 0) { // next state pre-setup
					t_road_1 = T_RED;
					t_road_2 = T_GREEN;
					status = RED_GREEN; // Change state
				}
				setTimer4(1000);
			}
			break;
		default:
			break;
	}
}
