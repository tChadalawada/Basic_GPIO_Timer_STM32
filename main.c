#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>
#include "hal_hal.h"
#include "util.h"

void TimingDelay_Decrement(void);
void Delay_ms(uint32_t tim);
void SysTick_Handler(void);
void Delay_s(unsigned char s);


/* Use this variable for SysTick Timer */
static __IO uint32_t TimingDelay;



int main()
{
	
	   /*Set Systick Timer for 1ms*/ 
if (SysTick_Config(SystemCoreClock / 1000))//1ms interrupt
  { 
      /* Capture error */
      while (1);
  }
	/*set clock for the GPIOD*/
	RCC->AHB1ENR = RCC_AHB1ENR_GPIODEN;
	/*set port pins as Output mode*/
	GPIOD->MODER = GPIO_MODER_MODER1_0;
	 // Ensure push pull mode selected--default
	GPIOD->OTYPER &= ~(GPIO_OTYPER_OT_1);
  //Ensure maximum speed setting (even though it is unnecessary)
  GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1;
  //Ensure all pull up pull down resistors are disabled
  GPIOD->PUPDR &= ~(GPIO_PUPDR_PUPDR1);
	
	/*Enable the clock for TIMER6 Basic-16bit counter*/
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	
	

	/*Set prescalor for TIMER6/41999*/
	TIM6->PSC = (SystemCoreClock/TIMCLK)-1;

	/*set auto reload to 5999*/
	TIM6->ARR = 19999;
	/*One pulse mode*/
	TIM6->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
	/*Force Update*/
	TIM6->EGR |= TIM_EGR_UG;
	/*clear update flag*/

	TIM6->SR &= ~(TIM_SR_UIF);
			/*Enable interrupt on the update event*/
	TIM6->DIER |= TIM_DIER_UIE;
		/*Enable TIM6 IRQ*/
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	/*Enable TIM6 counter*/
	TIM6->CR1 |= TIM_CR1_CEN;
//	GPIOD->BSRR |= (1UL << 2*17);

	    
	while(1) {
		
		//GPIOD->BSRR = GPIO_BSRR_BS_1;
		//GPIOD->BSRR = GPIO_BSRR_BR_1;
		
	//	GPIOD->BSRR = GPIO_BSRR_BS_1;
	//	Delay_ms(1000);
	//	GPIOD->BSRR = GPIO_BSRR_BR_1;
	//	Delay_ms(1000);
		
	//	delay
	}
	
}

	void TIM6_DAC_IRQHandler(){
		if(TIM6->SR & TIM_SR_UIF) {
			//GPIOD->BSRR = GPIO_BSRR_BS_1;
			//GPIOD->BSRR = GPIO_BSRR_BR_1;
			GPIOD->ODR ^= (1 << 1);
		TIM6->SR &= ~TIM_SR_UIF;
			//TIM2->SR = 0x0;
		}
	}
/******************************************************
  * @brief  This function decrease value of TimingDelay
  * @param  None
  * @retval None
  *****************************************************/
 
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
     
  }
}
/******************************************************
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  *****************************************************/
void SysTick_Handler(void)
{
	uint8_t s;
	s++;
     TimingDelay_Decrement();
}
 
 
/******************************************************
  * @brief  This function generate time x ms
  * @param  None
  * @retval None
  *****************************************************/
void Delay_ms(uint32_t time)
{
    TimingDelay = time;
 
  while(TimingDelay != 0);
  
   
}
 
/******************************************************
  * @brief  This function generate time x s
  * @param  None
  * @retval None
  *****************************************************/
void Delay_s(unsigned char s)
{
    
  uint32_t ms;
  ms=s*1000;
  Delay_ms(ms);
}
 
