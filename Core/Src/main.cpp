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
  //imuのインスタンス化
  // std::unique_ptr<sensor::imu::Creater> imu_creater = std::make_unique<sensor::imu::Creater>(sensor::imu::NAME::ICM20689);
  // std::unique_ptr<sensor::imu::Product> imu = imu_creater->Create(&hspi3,GPIOD,CS_Pin);
  //pxstrのインスタンス化
  //std::unique_ptr<sensor::pxstr::Creater> pxstr_creater = std::make_unique<sensor::pxstr::Creater>(sensor::pxstr::NAME::ST1KL3A);
  //std::unique_ptr<sensor::pxstr::Product> pxstr = pxstr_creater->Create(&hadc1);
  //mdのインスタンス化
  std::unique_ptr<md::Creater> md_creater = std::make_unique<md::Creater>(md::NAME::TB6612FNG);
  std::unique_ptr<md::Product> md = md_creater->Create(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_4);
  //encoderのインスタンス化
  // std::unique_ptr<sensor::encoder::Creater> encoder_creater = std::make_unique<sensor::encoder::Creater>(sensor::encoder::NAME::IEH24096);
  // std::unique_ptr<sensor::encoder::Product> encoder_R = encoder_creater->Create(&htim8, TIM_CHANNEL_ALL);
  // std::unique_ptr<sensor::encoder::Product> encoder_L = encoder_creater->Create(&htim4, TIM_CHANNEL_ALL);
  //buzzerのインスタンス化
  std::unique_ptr<indicator::Buzzer> buzzer = std::make_unique<indicator::Buzzer>(&htim3, TIM_CHANNEL_2);
  //ledのインスタンス化
  //std::unique_ptr<indicator::LED> led = std::make_unique<indicator::LED>();
  //wallsensのインスタンス化
  //std::unique_ptr<sensor::Wall> wallsens = std::make_unique<sensor::Wall>();
  //interruptのインスタンス化
  //std::unique_ptr<peripheral::IT> it = std::make_unique<peripheral::IT>();
  //waitのインスタンス化
  //  std::unique_ptr<peripheral::Wait> wait = std::make_unique<peripheral::Wait>(&htim1);
  //SWのインスタンス化
  // std::unique_ptr<input::SW> sw = std::make_unique<input::SW>(PUSH_IN_1_GPIO_Port, PUSH_IN_1_Pin);
  //timencoderのインスタンス化
  //std::unique_ptr<peripheral::TimEncoder> timencoder_r = std::make_unique<peripheral::TimEncoder>(&htim8, TIM_CHANNEL_ALL);
  //std::unique_ptr<peripheral::TimEncoder> timencoder_l = std::make_unique<peripheral::TimEncoder>(&htim8, TIM_CHANNEL_ALL);
  //motionのインスタンス化
  //motionのインスタンス化
  //objectsのインスタンス化

  std::unique_ptr<Objects> objects = std::make_unique<Objects>();
  std::unique_ptr<sensor::Motion> motion = 
  std::make_unique<sensor::Motion>(objects->encoder_l_, objects->encoder_r_, objects->imu_);
  std::unique_ptr<sensor::Wall> wall = 
  std::make_unique<sensor::Wall>(objects->pxstr_, objects->osi3ca5111a_, objects->wait_,objects->led);

  //wait->Ms(100);

  motion->Init();
  motion->ReadVal();
  motion->GetOffset();

  wall->Init();

  // encoder_R->ReadVal();
  // std::unique_ptr<state::Motion>& main_offset = encoder_R->get_raw_ref();
  // std::cout << "main_offset: " << main_offset->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;

  //wait->Ms(100);

  md->On();

  md->Dir(state::MOTOR::LEFT,state::MOTOR::FWD);
  md->Dir(state::MOTOR::RIGHT,state::MOTOR::FWD);
  md->Duty(0.2,0.2);
  md->Start();

  while(true){
    //   led->Toggle();
    
    //buzzer->Play(261.63, 100, 0.1);
    motion->Update();
    wall->ReadVal();
    std::cout << "wall:L " << wall->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::L)] << std::endl;
    std::cout << "wall:R " << wall->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::R)] << std::endl;
    std::cout << "wall:F " << wall->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::F)] << std::endl;
    std::cout << "raw:L " << wall->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::L)] << std::endl;
    std::cout << "raw:R " << wall->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::R)] << std::endl;
    std::cout << "raw:FR " << wall->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FL)] << std::endl;
    std::cout << "raw:FL " << wall->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FR)] << std::endl;
    //std::unique_ptr<state::Motion>& motion_val = motion->get_val_ref();
    objects->wait_->Ms(1000);
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
