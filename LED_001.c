#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include "LED.h"

int main() {
	/* Enable clock for the GPIOD */
	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	/* Set GPIOD-PIN1 to Output mode*/
	GPIOD->MODER &= ~(GPIO_MODER_MODER3 | GPIO_MODER_MODER2);
	GPIOD->MODER |= GPIO_MODER_MODER2_0;
	/* Set output regester type*/
	GPIOD->OTYPER &= ~(GPIO_OTYPER_OT_1);
	/*Setting the maximume speed for the pin*/
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_1;
	/*Ensure that all pull-UP/Pull-Down regesters are disabled*/
	GPIOD->PUPDR &= ~(GPIO_PUPDR_PUPDR2);
	while(1) {
		/* Set PC8 and PC9 */
        GPIOD->BSRR = GPIO_BSRR_BS_2;
	}
}

