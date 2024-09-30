#ifndef _PERIPHERAL_H_
#define _PERIPHERAL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

 extern ADC_HandleTypeDef hadc1;
 extern ADC_HandleTypeDef hadc2;
 extern DMA_HandleTypeDef hdma_adc1;
 extern DMA_HandleTypeDef hdma_adc2;

 extern SPI_HandleTypeDef hspi1;
 extern SPI_HandleTypeDef hspi3;

 extern TIM_HandleTypeDef htim1;
 extern TIM_HandleTypeDef htim2;
 extern TIM_HandleTypeDef htim3;
 extern TIM_HandleTypeDef htim4;
 extern TIM_HandleTypeDef htim5;
 extern TIM_HandleTypeDef htim8;

 extern UART_HandleTypeDef huart1;


void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_ADC1_Init(void);
void MX_ADC2_Init(void);
void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_SPI1_Init(void);
void MX_SPI3_Init(void);
void MX_TIM5_Init(void);
void MX_TIM8_Init(void);
void MX_USART1_UART_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* _PERIPHERAL_H_ */