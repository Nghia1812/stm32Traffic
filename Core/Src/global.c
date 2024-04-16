/*
 * global.c
 *
 *  Created on: Mar 20, 2024
 *      Author: NGHIA
 */

#include "main.h"


int T_RED = 10;
int T_YELLOW = 3;
int T_GREEN = 7;


int status = INIT;
int toggle_flag = 0;

void off_all_leds_road_1();
void off_all_leds_road_2();

void on_red_road_1();
void on_red_road_2();

void on_yellow_road_1();
void on_yellow_road_2();
void on_green_road_1();
void on_green_road_2();


void led_config() {
	switch (status) {
		case MODE1:
			off_all_leds_road_1();
			off_all_leds_road_2();
			break;
		case RED_GREEN:
			on_red_road_1();
			on_green_road_2();
			break;
		case RED_YELLOW:
			on_yellow_road_2();
			break;
		case GREEN_RED:
			on_green_road_1();
			on_red_road_2();
			break;
		case YELLOW_RED:
			on_yellow_road_1();
			break;
		case MODE2:
			on_red_road_1();
			on_red_road_2();
			toggle_flag = 0;
			break;
		case MODE3:
			on_yellow_road_1();
			on_yellow_road_2();
			toggle_flag = 0;
			break;
		case MODE4:
			on_green_road_1();
			on_green_road_2();
			toggle_flag = 0;
			break;
		default:
			break;
	}
}


void off_all_leds_road_1() {
	HAL_GPIO_WritePin (E4_Led1_G_GPIO_Port, E4_Led1_G_Pin, 0);
	HAL_GPIO_WritePin (E5_Led1_Y_GPIO_Port, E5_Led1_Y_Pin, 0);
	HAL_GPIO_WritePin (E6_Led1_R_GPIO_Port, E6_Led1_R_Pin, 0);

}

void off_all_leds_road_2() {
	HAL_GPIO_WritePin (E7_Led2_G_GPIO_Port, E7_Led2_G_Pin, 0);
	HAL_GPIO_WritePin (E8_Led2_Y_GPIO_Port, E8_Led2_Y_Pin, 0);
	HAL_GPIO_WritePin (E9_Led2_R_GPIO_Port, E9_Led2_R_Pin, 0);
}

void on_red_road_1() {
	HAL_GPIO_WritePin (E4_Led1_G_GPIO_Port, E4_Led1_G_Pin, 0);
	HAL_GPIO_WritePin (E5_Led1_Y_GPIO_Port, E5_Led1_Y_Pin, 0);
	HAL_GPIO_WritePin (E6_Led1_R_GPIO_Port, E6_Led1_R_Pin, 1);
}

void on_red_road_2() {
	HAL_GPIO_WritePin (E7_Led2_G_GPIO_Port, E7_Led2_G_Pin, 0);
	HAL_GPIO_WritePin (E8_Led2_Y_GPIO_Port, E8_Led2_Y_Pin, 0);
	HAL_GPIO_WritePin (E9_Led2_R_GPIO_Port, E9_Led2_R_Pin, 1);
}

void on_yellow_road_1() {
	HAL_GPIO_WritePin (E4_Led1_G_GPIO_Port, E4_Led1_G_Pin, 0);
	HAL_GPIO_WritePin (E5_Led1_Y_GPIO_Port, E5_Led1_Y_Pin, 1);
	HAL_GPIO_WritePin (E6_Led1_R_GPIO_Port, E6_Led1_R_Pin, 0);
}

void on_yellow_road_2() {
	HAL_GPIO_WritePin (E7_Led2_G_GPIO_Port, E7_Led2_G_Pin, 0);
	HAL_GPIO_WritePin (E8_Led2_Y_GPIO_Port, E8_Led2_Y_Pin, 1);
	HAL_GPIO_WritePin (E9_Led2_R_GPIO_Port, E9_Led2_R_Pin, 0);
}

void on_green_road_1() {
	HAL_GPIO_WritePin (E4_Led1_G_GPIO_Port, E4_Led1_G_Pin, 1);
	HAL_GPIO_WritePin (E5_Led1_Y_GPIO_Port, E5_Led1_Y_Pin, 0);
	HAL_GPIO_WritePin (E6_Led1_R_GPIO_Port, E6_Led1_R_Pin, 0);
}

void on_green_road_2() {
	HAL_GPIO_WritePin (E7_Led2_G_GPIO_Port, E7_Led2_G_Pin, 1);
	HAL_GPIO_WritePin (E8_Led2_Y_GPIO_Port, E8_Led2_Y_Pin, 0);
	HAL_GPIO_WritePin (E9_Led2_R_GPIO_Port, E9_Led2_R_Pin, 0);
}


void toggle_red() {
	if (toggle_flag == 0) {
		on_red_road_1();
		on_red_road_2();
		toggle_flag = 1;
	} else {
		off_all_leds_road_1();
		off_all_leds_road_2();
		toggle_flag = 0;
	}
}

void toggle_yellow() {
	if (toggle_flag == 0) {
		on_yellow_road_1();
		on_yellow_road_2();
		toggle_flag = 1;
	} else {
		off_all_leds_road_1();
		off_all_leds_road_2();
		toggle_flag = 0;
	}
}

void toggle_green() {
	if (toggle_flag == 0) {
		on_green_road_1();
		on_green_road_2();
		toggle_flag = 1;
	} else {
		off_all_leds_road_1();
		off_all_leds_road_2();
		toggle_flag = 0;
	}
}
