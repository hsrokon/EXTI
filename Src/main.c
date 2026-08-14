//EXTI - External Interrupts

#include "exti.h"

void main(){
//EXTI code starts here

	//7.3.7
	RCC->APB2ENR = (1<<2);//GPIOA clock enabled
	RCC->APB2ENR = (1<<0); //Alternate Function Input/Output clock Enabled

	GPIOA->CRL = ();//unfinished


}
