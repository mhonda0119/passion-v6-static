/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "imu_creater.hpp"
#include "pxstr_creater.hpp"
#include <iostream>
#include <memory>
#include "peripheral.h"
#include "stdout.h"
#include "buzzer.hpp"
#include "led.hpp"
#include "md_creater.hpp"
#include "encoder_creater.hpp"
#include "interrupt.hpp"
#include "wait.hpp"
#include "sw.hpp"
#include "led.hpp"
#include "states.hpp"
#include "motion.hpp"
#include "objects.hpp"
#include "wall.hpp"
/* USER CODE END Includes */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main()
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_SPI1_Init();
  MX_TIM5_Init();
  MX_SPI3_Init();
  MX_TIM1_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */
  printf("hello_c\n");
  std::cout << "hello_c++" << std::endl;
  long version = __cplusplus;
  std::cout << "C++ Version : " << version << "\n";

  //オブジェクトの生成
  std::unique_ptr<Objects> objects = std::make_unique<Objects>();

  std::unique_ptr<peripheral::IT> it = std::make_unique<peripheral::IT>();
  objects->wait_->Ms(1000);
  it->Init(&htim5);
  it->Start();

    // objects->buzzer_->Play(400,500);
    // objects->wait_->Ms(500);
    // objects->buzzer_->Play(400,500);
    // objects->wait_->Ms(500);
    // objects->buzzer_->Play(400,500);
    // objects->wait_->Ms(500);

  //it->Stop();

  std::unique_ptr<regulator::Motor> reg_motor = std::make_unique<regulator::Motor>();
  reg_motor->Init();


  while(true){
    // objects->wait_->Ms(1);
    // std::cout << "dist:" << peripheral::IT::reg_motor_->debug_->dist[static_cast<int>(state::Motion::DIR::C)] << std::endl;
    // std::cout << "spd:" << peripheral::IT::reg_motor_->debug_->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;
    // std::cout << "angle:" << peripheral::IT::reg_motor_->debug_->angle[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
    // std::cout << "omega:" << peripheral::IT::reg_motor_->debug_->omega[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
    // reg_motor->Regulate(40,0);
    // objects->buzzer_->Play(400,500);
    // objects->wait_->Ms(500);
    // objects->buzzer_->Play(400,500);
    // objects->wait_->Ms(500);
    // objects->buzzer_->Play(400,500);
    // objects->wait_->Ms(500);
    

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */


/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
