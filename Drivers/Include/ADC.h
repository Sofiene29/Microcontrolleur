#ifndef ADC_H
#define ADC_H
#include "stm32f10x.h"


void 	ADC_Init(ADC_TypeDef * ADC) ;
void Set_Channel(ADC_TypeDef * ADC , char channel);
void Start_conv(ADC_TypeDef * ADC) ;
int Handler_ADC (ADC_TypeDef * ADC) ;


#endif

