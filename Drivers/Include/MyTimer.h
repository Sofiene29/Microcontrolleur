#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

void MyTimer_Base_Init ( TIM_TypeDef * Timer , unsigned short ARR ,unsigned short PSC ) ;
void MyTimer_Base_Start ( TIM_TypeDef * Timer ) ;
void MyTimer_Base_Stop ( TIM_TypeDef * Timer ); 
void MyTimer_ActiveIT(TIM_TypeDef * Timer , char Prio, void (*Fct) (void));
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel); 
void MyTimer_Set_Cycle(TIM_TypeDef * Timer , float cycle , char Channel);
#endif

