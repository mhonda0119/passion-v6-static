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
#include "wallsens.hpp"
#include "interrupt.hpp"
#include "wait.hpp"
#include "sw.hpp"
#include "led.hpp"
/* USER CODE END Includes */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(int argc, char** argv)
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
  std::unique_ptr<sensor::imu::Creater> imu_creater = std::make_unique<sensor::imu::Creater>(sensor::imu::NAME::ICM20689);
  std::unique_ptr<sensor::imu::Product> imu = imu_creater->Create(&hspi3,GPIOD,CS_Pin);
  //pxstrのインスタンス化
  //std::unique_ptr<sensor::pxstr::Creater> pxstr_creater = std::make_unique<sensor::pxstr::Creater>(sensor::pxstr::NAME::ST1KL3A);
  //std::unique_ptr<sensor::pxstr::Product> pxstr = pxstr_creater->Create(&hadc1);
  //mdのインスタンス化
   std::unique_ptr<md::Creater> md_creater = std::make_unique<md::Creater>(md::NAME::TB6612FNG);
   std::unique_ptr<md::Product> md = md_creater->Create(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_4);
  //encoderのインスタンス化
  std::unique_ptr<sensor::encoder::Creater> encoder_creater = std::make_unique<sensor::encoder::Creater>(sensor::encoder::NAME::IEH24096);
  std::unique_ptr<sensor::encoder::Product> encoder_R = encoder_creater->Create(&htim8, TIM_CHANNEL_ALL);
  //std::unique_ptr<sensor::encoder::Product> encoder_L = encoder_creater->Create(&htim4, TIM_CHANNEL_ALL);
  //buzzerのインスタンス化
  //std::unique_ptr<indicator::Buzzer> buzzer = std::make_unique<indicator::Buzzer>(&htim3, TIM_CHANNEL_2);
  //ledのインスタンス化
  //std::unique_ptr<indicator::LED> led = std::make_unique<indicator::LED>();
  //wallsensのインスタンス化
  //std::unique_ptr<sensor::Wall> wallsens = std::make_unique<sensor::Wall>();
  //interruptのインスタンス化
  //std::unique_ptr<peripheral::IT> it = std::make_unique<peripheral::IT>();
  //waitのインスタンス化
  std::unique_ptr<peripheral::Wait> wait = std::make_unique<peripheral::Wait>(&htim1);
  //SWのインスタンス化
  std::unique_ptr<input::SW> sw = std::make_unique<input::SW>(PUSH_IN_1_GPIO_Port, PUSH_IN_1_Pin);
  //timencoderのインスタンス化
  //std::unique_ptr<peripheral::TimEncoder> timencoder_r = std::make_unique<peripheral::TimEncoder>(&htim8, TIM_CHANNEL_ALL);
  //std::unique_ptr<peripheral::TimEncoder> timencoder_l = std::make_unique<peripheral::TimEncoder>(&htim8, TIM_CHANNEL_ALL);

  //led->Toggle();
  //buzzer->Play(440, 100, 0.5);

  while(true){
    // sw->Update();
    // if(sw->Read() == true){
    //   led->Toggle();
    //   buzzer->Play(294, 100, 0.5); // ド
    //   buzzer->Play(330, 100, 0.5); // レ
    //   buzzer->Play(349, 100, 0.5); // ミ
    //   buzzer->Play(392, 100, 0.5); // ファ
    //   buzzer->Play(440, 100, 0.5); // ソ
    //   buzzer->Play(494, 100, 0.5); // ラ
    //   buzzer->Play(523, 100, 0.5); // シ
    //   buzzer->Play(587, 100, 0.5); // ド
    // }
    // md->On();
    // md->Dir(parameter::MOTOR::LEFT,parameter::MOTOR::CW);
    // md->Dir(parameter::MOTOR::RIGHT,parameter::MOTOR::CW);
    // md->Duty(0.2,0.2);
    //std::cout << "0" << std::endl;
    //encoder_R->Init();
    encoder_R->Start();
    // encoder_L->Init();
    // encoder_L->Start();
    //timencoder_r->Start();
    imu->Init();
    parameter::Motion* mp;
    while(true){
    // md->Start();
    // std::cout << "0" << std::endl;
    encoder_R->ReadVal();
    // encoder_L->ReadVal();
    //std::cout << "1" << std::endl;
    parameter::Motion* encoder_val_R = encoder_R->get_val_ptr();
    //parameter::Motion* encoder_val_L = encoder_L->get_val_ptr();
    std::cout << "encoder_r: " << encoder_val_R->spd << std::endl;
    // std::cout << "encoder_l: " << encoder_val_L->spd << std::endl;
    //timencoder_r->ReadVal();
    //std::cout << "Encoder Value: " << timencoder_r->get_val() << std::endl;
    // wait->Ms(1000);
    // md->Stop();
    imu->ReadVal();
    mp = imu->get_val_ptr();
     std::cout <<"omega:"<< mp->omega[0] << std::endl; 
    wait->Ms(1000);
    }
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
