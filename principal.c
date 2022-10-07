#include "stm32f10x.h"
#include "U:\4 IR\Drivers\Include\GPIO.h" 
#include "U:\4 IR\Drivers\Include\MyTimer.h"

GPIO_TypeDef * GPIO = GPIOC;
int GPIO_Pin_LED = 10 ;
int GPIO_Pin_UB = 8 ;

void maFonction(void)
{
	 MyGPIO_Toggle (GPIO , GPIO_Pin_LED); 
}


int main ( void ) {  
	 

	//Configuration du TIM2
	unsigned short PSC=0xF;	  
	unsigned short ARR=(500*72*1000)/(PSC+1)-1;
 
	MyTimer_Base_Init (TIM2, ARR, PSC);
	MyTimer_Base_Start(TIM2);
	
	//CONFIGURATION GPIO
	
	MyGPIO_Init(GPIO,GPIO_Pin_LED,Out_OD);//LED PC10 output open drain
	MyGPIO_Init(GPIO,GPIO_Pin_UB,In_Floating); //B1 user PC8 input floating 
	MyTimer_ActiveIT(TIM2,3,maFonction);
	

	while(1) { 
		
		
	
	
	}; 
}
