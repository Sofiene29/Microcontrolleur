#include "U:\4 IR\Drivers\Include\GPIO.h"
#include "stm32f10x.h" 

		
void MyGPIO_Init_clck (void){
		RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
}
		
void MyGPIO_Init ( GPIO_TypeDef * GPIO , int GPIO_Pin, char GPIO_Conf) {
	MyGPIO_Init_clck();
	
	if ( GPIO_Pin<8) {  
		GPIO->CRL &= ~(0xF << (4*  GPIO_Pin));   
		GPIO->CRL |=   GPIO_Conf << (4*  GPIO_Pin) ;
				
	} else if ( GPIO_Pin<15) { 
		GPIO->CRH &= ~(0xF << (4* ( GPIO_Pin-8)));   
		GPIO->CRH |=   GPIO_Conf << (4* ( GPIO_Pin-8)) ;
	}  else { 
		
	}
		
	if (GPIO_Conf == In_PullDown) {
		GPIOC->ODR &=   ~(1 << GPIO_Pin);
	} else if (GPIO_Conf == In_PullUp) {
		GPIOC->ODR |=  0x1 << GPIO_Pin ;
	} 
}



int MyGPIO_Read ( GPIO_TypeDef * GPIO , int GPIO_Pin ) {
		return (GPIO->IDR & (0x1 << GPIO_Pin)) == (0x1<<GPIO_Pin);
}

void MyGPIO_Set ( GPIO_TypeDef * GPIO , int GPIO_Pin ) {
		GPIO->BSRR =  0x1 << GPIO_Pin;

}

void MyGPIO_Reset ( GPIO_TypeDef * GPIO , int GPIO_Pin ){
	GPIO->BRR =  1 << GPIO_Pin;
}

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , int GPIO_Pin ){
	if ((GPIO->ODR & (0x1 << GPIO_Pin)) == (0x1<<GPIO_Pin)) {
		MyGPIO_Reset(GPIO,GPIO_Pin); 
	}	else {MyGPIO_Set(GPIO,GPIO_Pin);}
}
