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
#include <iostream>
#include <memory>

#include "peripheral.h"
#include "stdout.h"
#include "objects.hpp"
#include "interrupt.hpp"
#include "drive.hpp"
#include "regulator.hpp"
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

  //hello_world
  printf("hello_c\n");
  std::cout << "hello_c++" << std::endl;
  long version = __cplusplus;
  std::cout << "C++ Version : " << version << "\n";
  //hello_world

  /*-------------------------------------INIT-------------------------------------*/
  //objectsのインスタンス化(本来，objectsはstaticなクラスであるが，ここではインスタンス化している)
  std::unique_ptr<Objects> objects = std::make_unique<Objects>();
  //objectsの初期化
  //すべてのstaticなクラスのインスタンス化を行う．
  objects->Init();
  //objectsを利用した初期化を行う．
  std::unique_ptr<drive::Core> core = 
  std::make_unique<drive::Core>(objects->motor_reg_,objects->imu_,objects->encoder_,objects->md_);
  /*----------初期化シーケンス実行------------*/
  Objects::buzzer_->Play(500,50,0.8);
  Objects::wait_->Ms(100);
  Objects::buzzer_->Play(500,50,0.8);

  Objects::imu_->Init();
  Objects::encoder_->Init();
  Objects::pxstr_->Init();
  Objects::wall_->Init();
  
  Objects::md_->On();
  Objects::md_->Dir(state::MOTOR::LEFT,state::MOTOR::FWD);
  Objects::md_->Dir(state::MOTOR::RIGHT,state::MOTOR::FWD);
  Objects::md_->Duty(0,0);

  Objects::wall_->GetOffset();
  Objects::encoder_->GetOffset();
  Objects::encoder_->Start();
  Objects::imu_->GetOffset();

  Objects::buzzer_->Play(500,50,0.8);
  Objects::wait_->Ms(100);
  Objects::buzzer_->Play(500,50,0.8);
  /*------------初期化シーケンス終了------------*/
  //interruputの初期化を行う．
  peripheral::IT::Init(&htim5);
  /*-------------------------------------INIT-------------------------------------*/
  peripheral::IT::Start();

  Objects::buzzer_->Play(500,500,0.8);
  Objects::wait_->Ms(1000);

  //core->AD(100,0,50);

  while(true){
  std::cout << "imu_raw_omega:" << Objects::imu_->get_raw_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
  std::cout << "encoder_c:" << Objects::encoder_->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::R)] << std::endl;
  Objects::wait_->Ms(100);
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
