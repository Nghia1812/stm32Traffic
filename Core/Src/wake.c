/*
 * wake.c
 *
 *  Created on: Mar 25, 2024
 *      Author: NGHIA
 */
#include "main.h"


void sleep_enter(){
	uint8_t str[] = "Sleep\n";

	HAL_UART_Transmit(&huart2,(uint8_t*) str, sizeof(str), HAL_MAX_DELAY);

	HAL_SuspendTick();

	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);



}


void exti_config_wake(){
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA; //EXTI on PA3
	EXTI->IMR |= EXTI_IMR_IM3; //interrupt request

	//falling edge
	EXTI->RTSR &= ~EXTI_RTSR_TR3_Msk;
	EXTI->FTSR |= EXTI_FTSR_TR3_Msk;

	//NVIC init
	NVIC_SetPriority(EXTI3_IRQn, 0);
	NVIC_EnableIRQ(EXTI3_IRQn);
}

void EXTI3_IRQHandler(void){
	if((EXTI->PR & EXTI_PR_PR3_Msk) != 0){

		//clear pending
		EXTI->PR = EXTI_PR_PR3;

		//Exit sleep mode
		HAL_ResumeTick();

//		uint8_t str[] = "Wake\n";
//
//		HAL_UART_Transmit(&huart2,(uint8_t*) str, sizeof(str), HAL_MAX_DELAY);
	}
}
