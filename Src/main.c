//EXTI - External Interrupts

#include "exti.h"

void main(){
//EXTI code starts here

	//8.3.7
	RCC->APB2ENR = (1<<2)//GPIOA clock enabled
				   |(1<<0); //Alternate Function Input/Output clock Enabled

	GPIOA->CRL &= ~(0xFF<<0);
	GPIOA->CRL |= (0x8<<0);//Configuring pin A0 as input mode pull up/down
	GPIOA->CRL |= (0x3<<4);//Configuring pin A1 as GPO Max 50 Hz


}
