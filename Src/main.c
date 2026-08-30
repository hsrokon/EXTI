//EXTI - External Interrupts

#include "exti.h"

void main(){
//EXTI code starts here

	//8.3.7
	RCC->APB2ENR |= (1<<2)//GPIOA clock enabled
				   |(1<<0); //Alternate Function Input/Output clock Enabled

	GPIOA->CRL &= ~(0xFF<<0);
	GPIOA->CRL |= (0x8<<0);//Configuring PA0 as input mode pull up/down
	GPIOA->ODR |= (1<<0);//Setting PA0(as it is input) to pull up resistor.

	GPIOA->CRL |= (0x3<<4);//Configuring PA1 as GPO Max 50 Hz output


	AFIO->EXTICR[0] &= ~(0xF<<0);//Clearing EXTI0
	AFIO->EXTICR[0] |= (0x0<<0);//Connecting EXTI0 for PA0

	//FTSR(Falling Trigger Selection Register) Falling Edge- 3.3v to 0v)
	EXTI->FTSR |= (1<<0);//When the button falls 3.3-0v it will trigger

	//IMR(Interrupt Mask Register)
	EXTI->IMR |= (1<<0);//Interrupt trigger signal is allowed to go to CPU by unmasking

	//NVIC(Nested Vectored Interrupt Controller)
	//IRQ=Interrupt Request
	//ISR=Interrupt Service Routine
	/*
	 * Interrupt request signal comes to CPU
	 * It saves Current Register State
	 * Runs ISR
	 * Clears Pending flag, interrupt marked solved
	 * Restore saved register, and resume while(1)
	 */

	//CMSIS(Cortex Microcontroller Software Interface Standard)
	NVIC_EnableIRQ(EXTI0_IRQn);//core_cm3.h CMSIS function that enables and points to EXTI0_IRQHandler

	//Keeping CPU alive while waiting for hardware interrupts
	while(1){
		//It uses minimal energy, while keeping the CPU awake
	}
}

//Setting the interrupt with Interrupt Request Handler Function
void EXTI0_IRQHandler(void){
	//Setting/Resetting/Checking the pending bit

}

//rc_w1 = Read Clear by Writing 1
