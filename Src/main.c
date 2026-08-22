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
}
