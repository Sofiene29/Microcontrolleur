#include "stm32f10x.h"
#include "U:\4 IR\Drivers\Include\GPIO.h" 
#include "U:\4 IR\Drivers\Include\MyTimer.h"
#include "U:\4 IR\Drivers\Include\ADC.h"

GPIO_TypeDef * GPIO = GPIOC;   
ADC_TypeDef * ADC= ADC2; 

int toto ;
int GPIO_Pin_LED = 10 ;
int GPIO_Pin_UB = 8 ;

void maFonction(void) {
	 //MyGPIO_Toggle (GPIO , GPIO_Pin_LED);   
		toto = Handler_ADC(ADC);
}


int main ( void ) {  
	 

	//Configuration du TIM2
	unsigned short ARR=65535;	  
	unsigned short PSC= (72*10)/(ARR+1)-1; //FREQUENCE pwm a 100KHZ
 
	MyTimer_Base_Init (TIM2, ARR, PSC);
	MyTimer_Base_Start(TIM2);
	
	//CONFIGURATION GPIO
	
	MyGPIO_Init(GPIO,GPIO_Pin_LED,Out_OD);//LED PC10 output open drain
	MyGPIO_Init(GPIO,GPIO_Pin_UB,In_Floating); //B1 user PC8 input floating

	
	
	
	
	//Configuration PWM
	//MyTimer_PWM( TIM2 , 1); 
	//MyTimer_Set_Cycle(TIM2 , 0.5 , 1); 
	
	//Config ADC
	ADC_Init(ADC); 
	Set_Channel(ADC , 2);	

	
	
	MyTimer_ActiveIT(TIM2,3,maFonction); // ? desactiver pour tester pwm
	while(1) { 
		
		
	
	
	}; 
}
