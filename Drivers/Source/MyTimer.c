#include "U:\4 IR\Drivers\Include\MyTimer.h" 
#include "U:\4 IR\Drivers\Include\GPIO.h"
#include "stm32f10x.h"  

/* Fichier de la couche pilote */
void (* pFnc) (void) ; /* déclaration d’un pointeur de fonction */

void MyTimer_Base_Init ( TIM_TypeDef * Timer , unsigned short ARR ,unsigned short PSC) {  

	
	if (Timer  == TIM1 ) {
		RCC->APB2ENR |= 1<<11; 
	} else if (Timer == TIM2) {
		RCC->APB1ENR |= 1<<0; 
	} else if (Timer  == TIM3) {
		RCC->APB1ENR |= 1<<1; 
	}else if (Timer == TIM4) {
		RCC->APB1ENR |= 1<<2; 
	}else {
	}
		
	Timer->PSC = PSC;	  
	Timer->ARR = ARR;	   
	
	
} 
void MyTimer_Base_Start ( TIM_TypeDef * Timer ) {  
	
	Timer->CR1|=1<<0;
} 

void MyTimer_Base_Stop ( TIM_TypeDef * Timer  ) { 
	
	Timer->CR1&=~(1<<0);
	
}  

void MyTimer_ActiveIT(TIM_TypeDef * Timer , char Prio, void (*Fnc) (void)) { 
	
	Timer->DIER |= 1<<0; 
	if (Timer == TIM2) {
		NVIC->ISER[0] |=1<<28; 
		NVIC->IP[TIM2_IRQn]=Prio<<4; //=> IP[28]
		pFnc=Fnc;
	} else if (Timer  == TIM3) {
		NVIC->ISER[0] |=1<<29; 
		NVIC->IP[29]=Prio<<4; 
		pFnc=Fnc;
	}else if (Timer == TIM4) {
		NVIC->ISER[0] |=1<<30;  
		NVIC->IP[30]=Prio<<4; 
		pFnc=Fnc;
	}else {
	} 
	 
} 
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel){   
	
	if (Channel==1) {  
		Timer -> CCMR1  = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; //set pwm
		Timer -> CCER |= 1<< 0 ; //enable clock register
	} else if (Channel==2){
		Timer -> CCMR1  = TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
		Timer -> CCER |= 1<< 4 ;
	}	else if (Channel==3){
		Timer -> CCMR2  = TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2; 
		Timer -> CCER |= 1<< 8 ;
	} else if (Channel==4){
		Timer -> CCMR2  = TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2; 
		Timer -> CCER |= 1<< 12 ;
	} else {		}
	
	if (Timer== TIM1) { 
		Timer -> BDTR |= 1 <<15 ; //enable output
		switch(Channel) { 
			case 1 : MyGPIO_Init ( GPIOA , 8, AltOut_Ppull) ;	 break; 
			case 2 : MyGPIO_Init ( GPIOA , 9, AltOut_Ppull) ;	 break;  
			case 3 : MyGPIO_Init ( GPIOA , 10, AltOut_Ppull) ;	 break;  
			case 4 : MyGPIO_Init ( GPIOA , 11, AltOut_Ppull) ;	 break; 
			default: break;
		}
		
	} else if (Timer == TIM2) {   
		switch(Channel) { 
			case 1 : MyGPIO_Init ( GPIOA , 0, AltOut_Ppull) ;	 break; 
			case 2 : MyGPIO_Init ( GPIOA , 1, AltOut_Ppull) ;	 break;  
			case 3 : MyGPIO_Init ( GPIOA , 2, AltOut_Ppull) ;	 break;  
			case 4 : MyGPIO_Init ( GPIOA , 3, AltOut_Ppull) ;	 break; 
			default: break;
		}
		
	} else if (Timer  == TIM3) {
		switch(Channel) { 
			case 1 : MyGPIO_Init ( GPIOA , 6, AltOut_Ppull) ;	 break; 
			case 2 : MyGPIO_Init ( GPIOA , 7, AltOut_Ppull) ;	 break;  
			case 3 : MyGPIO_Init ( GPIOB , 0, AltOut_Ppull) ;	 break;  
			case 4 : MyGPIO_Init ( GPIOB , 1, AltOut_Ppull) ;	 break; 
			default: break;
		}
			
	} else if (Timer == TIM4) { 
		switch(Channel) { 
			case 1 : MyGPIO_Init ( GPIOB , 6, AltOut_Ppull) ;	 break; 
			case 2 : MyGPIO_Init ( GPIOB , 7, AltOut_Ppull) ;	 break;  
			case 3 : MyGPIO_Init ( GPIOB , 8, AltOut_Ppull) ;	 break;  
			case 4 : MyGPIO_Init ( GPIOB , 9, AltOut_Ppull) ;	 break; 
			default: break;
		} 
			
	} else {	} 
	 
	
} 
void MyTimer_Set_Cycle(TIM_TypeDef * Timer , float cycle, char Channel) {   
	switch(Channel) { 
			case 1 : Timer->CCR1= Timer->ARR*cycle ;	 break; 
			case 2 : Timer->CCR2= Timer->ARR*cycle ;	 break;  
			case 3 : Timer->CCR3= Timer->ARR*cycle  ;	 break;  
			case 4 : Timer->CCR4= Timer->ARR*cycle  ;	 break; 
			default: break;
		} 
}


void TIM2_IRQHandler(void) {    
	
 (*pFnc) (); /* appel indirect de la fonction */
	TIM2->SR &= ~(1<<0); //UIF
		
}

