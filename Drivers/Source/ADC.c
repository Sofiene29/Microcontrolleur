#include "stm32f10x.h" 


void 	ADC_Init(ADC_TypeDef * ADC) {  
	 
	
	RCC->CFGR |=10<<14 ; //diviser freq par 6
	RCC->APB2ENR |= (1<<9) | (1<<10); //Active clock ADC1 et ADC 2
	
	ADC->CR2|=1<<0; //Power ON ADC  
	ADC->SQR1 &= ~(0xF<<20); //Set 1 conversion  

	
}   


void Set_Channel(ADC_TypeDef * ADC , char channel) { 
	ADC->SQR3= channel<<0;
} 


void Start_conv(ADC_TypeDef * ADC) { 
	ADC->CR2|=1<<0; //Power ON ADC  
} 


int Handler_ADC (ADC_TypeDef * ADC) {
	Start_conv(ADC);
	while(ADC->SR && 0x1<<1 != 0x1<<1) { }
		
	return ADC->DR ; 
}
