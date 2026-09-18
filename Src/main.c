//EXTI - External Interrupts

#include "exti.h"

int main(){
//EXTI code starts here

	//8.3.7
	RCC->APB2ENR |= (1<<2)//GPIOA clock enabled
				   |(1<<0); //Alternate Function Input/Output clock Enabled

	GPIOA->CRL &= ~(0xFF<<0);
	GPIOA->CRL |= (0x8<<0);//Configuring PA0 as input mode pull up/down
	GPIOA->ODR |= (1<<0);//Setting PA0(as it is input) to pull up resistor.

	GPIOA->CRL &= ~(0xF<<4);
	GPIOA->CRL |= (0x3<<4);//Configuring PA1 as GPO Max 50 Hz output

	/*
	 * EXTICR[0]: Governs lines EXTI0(for Px0, x=A,B,C,D), EXTI1, EXTI2, EXTI3
	 * EXTICR[1]: Governs lines EXTI4, EXTI5, EXTI6, EXTI7
	 * EXTICR[2]: Governs lines EXTI8, EXTI9, EXTI10, EXTI11
	 * EXTICR[3]: Governs lines EXTI12, EXTI13, EXTI14, EXTI15
	*/
	AFIO->EXTICR[0] &= ~(0xF<<0);//Clearing EXTI0
	AFIO->EXTICR[0] |= (0x0<<0);//Connecting EXTI0 for PA0(0x0 is for PA0, 0x1 = PB0)

	//FTSR(Falling Trigger Selection Register) Falling Edge- 3.3v to 0v) - Enabled
	EXTI->FTSR |= (1<<0);//When the button falls 3.3-0v it will trigger
	EXTI->RTSR &= ~(1<<0);//Rising Trigger disabled

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

	//CMSIS(Cortex Micro-controller Software Interface Standard)
	NVIC_EnableIRQ(EXTI0_IRQn);
	//core_cm3.h, CMSIS function, that *enables* and points to EXTI0_IRQHandler

	//Keeping CPU alive while waiting for hardware interrupts
	while(1){
		//It uses minimal energy, while keeping the CPU awake
	}
}

//Setting the interrupt with Interrupt Request Handler Function
void EXTI0_IRQHandler(void){
	//Setting/Resetting/Checking the Pending Register(PR) - 10.3.6
	//Check > Execute > Clear

	//Check if EXTI Line 0 pending flag is set
	if(EXTI->PR & (1<<0)){
		/*Checking if EXTI Line 0(mapped to PA0)triggered this interrupt using
		 bitwise and(&).
		 *Line 0 active: 0000...0001 & 0000...0001 = 0000...0001 (Non-zero, execute ISR body)
		 *Line 1 active: 0000...0010 & 0000...0001 = 0000...0000 (Zero, triggered by PA1, ignore)
		 */

		EXTI->PR|=(1<<0);//first clear the PR so no pending bits
		//rc_w1 = Read Clear by Writing 1

		for(volatile int i=0; i< 40000; i++);//wait first for the switch to settle(~20ms at 72MHz)

		//IDR=Input Data Register
		if((GPIOA->IDR & (1<<0))==0){//Check if bit 0 evaluated to 0(logic low)

			GPIOA->ODR^=(1<<1);//9.2.4
			//XOR-Toogles: input 1, target mask bit 1 output 0, input 1 tar. mask bit 0 output 1

			/*This way we only toggle after waiting 15ms and checking
			 if we are still keeping button low buy holding the physical press*/
		}
		EXTI->PR |= (1<<0);/*Clearing it again so any new trigger happen during
		the initial 20ms delay and that does not trigger the CPU to re jump to do ISR */
	}
}
