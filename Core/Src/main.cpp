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
#include "accel_designer.h"
#include "flags.hpp"
#include "search.hpp"
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
  std::cout << "C++ : " << __cplusplus << "\n";
  //hello_world
  /*----------------------------------起動シーケンス開始----------------------------*/
  /*-------------------------------------INIT-------------------------------------*/
  //objectsのインスタンス化(本来，objectsはstaticなクラスであるが，ここではインスタンス化している)
  std::unique_ptr<Objects> objects = std::make_unique<Objects>();
  std::cout << "objects_Instance" << std::endl;
  //objectsの初期化
  //すべてのstaticなクラスのインスタンス化を行う．
  objects->Init();
  std::cout << "objects_Init" << std::endl;
  //objectsを利用した初期化を行う．
  //designのインスタンス化
  std::unique_ptr<ctrl::Design> design = std::make_unique<ctrl::Design>(Objects::accel_designer_);
  std::cout << "design_Instance" << std::endl;
  //driveのインスタンス化
  std::unique_ptr<drive::Core> core = 
  std::make_unique<drive::Core>(Objects::motor_reg_,Objects::imu_,Objects::encoder_,Objects::md_,
  design,Objects::traj_l90_,Objects::traj_r90_);
  std::cout << "drive_Instance" << std::endl;
  //Searchのインスタンス化
 std::unique_ptr<maze::Search> search = 
 std::make_unique<maze::Search>(Objects::wall_,Objects::wait_,core,Objects::encoder_,
 consts::software::GOAL_X,consts::software::GOAL_Y);
  /*----------初期化シーケンス実行------------*/

  Objects::buzzer_->Play(500,50);

  Objects::imu_->Init();
  Objects::encoder_->Init();
  Objects::pxstr_->Init();
  Objects::wall_->Init();

  /*motorの確認*/
  Objects::md_->On();
  Objects::md_->Dir(state::MOTOR::LEFT,state::MOTOR::FWD);
  Objects::md_->Dir(state::MOTOR::RIGHT,state::MOTOR::FWD);
  Objects::md_->Duty(0,0);
  Objects::buzzer_->Play(500,50,1);
  Objects::md_->Duty(5,5);
  Objects::md_->Start();
  Objects::wait_->Ms(100);
  Objects::buzzer_->Play(500,50,1);
  Objects::md_->Duty(0,0);
  Objects::md_->ShortBrake();
  /*motorの確認*/

  /*offsetを一旦とる*/
  Objects::wall_->GetOffset();
  Objects::encoder_->GetOffset();
  Objects::encoder_->Start();
  Objects::imu_->GetOffset();
  /*offsetを一旦とる*/
  /*------------初期化シーケンス終了------------*/
  //interruputの初期化を行う．
  peripheral::IT::Init(&htim5);
  /*-------------------------------------INIT-------------------------------------*/
  peripheral::IT::Start();
  /*encoderの確認*/
  core->CurveAD(90,0,100);
  while(Flag::Check(DRIVE_START)){
    if(Objects::encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] > 110){
      Objects::buzzer_->Play(1000,500);
      for(int i = 0;i < 10;i++){
        Objects::led_->On();
        Objects::wait_->Ms(50);
        Objects::led_->Off();
        Objects::wait_->Ms(50);
      }
      break;
    }
  };
  core->Stop();
  /*encoderの確認*/
  for(int i = 0; i < 4; i++){
    Objects::buzzer_->Play(500 + i * 50, 50);
    Objects::wait_->Ms(5);
  } 

  Objects::buzzer_->Play(500,50);
  Objects::wait_->Ms(100);
  Objects::buzzer_->Play(500,2000);//2秒//正しい位置に置く猶予

  Objects::wall_->GetOffset();
  Objects::encoder_->GetOffset();
  Objects::encoder_->Start();
  Objects::imu_->GetOffset();

  Objects::buzzer_->Play(500,50);
  Objects::wait_->Ms(100);
  Objects::buzzer_->Play(500,50);
  /*-------------------------------------起動シーケンス終了-------------------------------------*/


  // core->Straight(270,0,0);
  // while(true);
  // core->Slalom_L90(300);
  //   while(Flag::Check(DRIVE_START)){}
  // core->Slalom_R90(300);
  //   while(Flag::Check(DRIVE_START)){}
  // core->SpinTurn();
  //   while(Flag::Check(DRIVE_START)){}

  // Objects::led_->On();
  // core->Stop();
  // while(true);


  
  /*========================searchB====================================================*/
  std::cout << "searchB" << std::endl;
  //二次走行フラグをクリア
  Flag::Reset(SCND);
  search->set_goal(consts::software::GOAL_X,consts::software::GOAL_Y);//ゴール座標設定
  core->Ketsu();
  //機体が安定するまで
  Objects::wait_->Ms(100);
  //壁制御用のオフセットを取得
  Objects::imu_->GetOffset();
  Objects::wall_->GetOffset();
  //サーチBする
  search->SearchB();
  //なんか待つ
  Objects::wait_->Ms(500);
  //ゴール座標を設定する
  search->set_goal(consts::software::GOAL_X,consts::software::GOAL_Y);
  /*========================searchB====================================================*/



  // core->SpinTurn();
  // while(Flag::Check(DRIVE_START)){}

  // Objects::led_->On();
  //core->Ketsu();
  //core->Stop();
  // Objects::md_->Off();
  // Objects::led_->Off();

  // core->CurveAD(180,0,500);
  // while(Flag::Check(DRIVE_START)){}
  // Objects::buzzer_->Start(500,5);
  // Objects::led_->On();

  // core->CurveAD(40,500,500);
  // while(Flag::Check(DRIVE_START)){}
  // core->Slalom_R90(500);
  // while(Flag::Check(DRIVE_START)){}
  // core->CurveAD(72,500,500);
  // while(Flag::Check(DRIVE_START)){}

  // core->CurveAD(50,500,500);
  // while(Flag::Check(DRIVE_START)){}
  // core->Slalom_L90(500);
  // while(Flag::Check(DRIVE_START)){}
  // core->CurveAD(40,500,500);

  // Objects::buzzer_->Start(500,50);
  /*Flag::Check(DRIVE_START)*/
  while(true){
    Objects::wait_->Ms(5);
    // std::cout << "t_cnt_ : " << Objects::motor_reg_->t_cnt_ << "\t";
    //std::cout << "r_dist:" << Objects::motor_reg_->r_->dist[static_cast<int>(state::Motion::DIR::C)] << "\t";
    // std::cout << "s_.dq.th : " << Objects::motor_reg_->s_.dq.th*consts::physics::RAD2DEG << "\t";
    // std::cout << "s.q.th : " << Objects::motor_reg_->s_.q.th*consts::physics::RAD2DEG << "\t";
    // std::cout << "r_v" << Objects::traj_r90_->getVelocity() << "\t";
    // std::cout << "end_t " << Objects::traj_r90_->getTimeCurve() << "\t";

    // std::cout << "raw_sensor_l : " << Objects::wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::L)] << "\t";
    // std::cout << "raw_sensor_fl : " << Objects::wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FL)] << "\t";
    // std::cout << "raw_sensor_fr : " << Objects::wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FR)] << "\t";
    // std::cout << "raw_sensor_r : " << Objects::wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::R)] << "\t";

    //std::cout << "l_v" << Objects::traj_l90_->getVelocity() << "\t";
    //std::cout << "end_t " << Objects::traj_l90_->getTimeCurve() << "\t";
    // std::cout << "v : " << Objects::motor_reg_->r_->spd[static_cast<int>(state::Motion::DIR::C)] << "\t";
    // std::cout << "l_encoder:" << Objects::encoder_->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::L)] << "\t";
    // std::cout << "r_encoder:" << Objects::encoder_->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::R)]<< "\t";
    std::cout << "l_encoder:" << Objects::encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::L)] << "\t";
    std::cout << "r_encoder:" << Objects::encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::R)]<< "\t";
    //std::cout << "dist:" << Objects::encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] << "\t";
    // std::cout << "DRIVE_START : " << Flag::Check(DRIVE_START) << "\t";
    // std::cout << "DRIVE_STRAIGHT : " << Flag::Check(DRIVE_STRAIGHT) << "\t";
    // std::cout << "DRIVE_SLALOM_L90 : " << Flag::Check(DRIVE_SLALOM_L90) << std::endl;
    // std::cout << "imu_omega:" << Objects::imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)] << "\t";
    // std::cout << "omega_r" << Objects::accel_designer_->v(Objects::motor_reg_->t_cnt_) << "\t";
    // std::cout << "imu_angle: " << Objects::imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] << "\t";
    //std::cout << "x_t_end : " << Objects::accel_designer_->x(Objects::accel_designer_->t_end()) + 5<< std::endl;
    std::cout << std::endl;
  }
  // Objects::led_->Off();
  // Objects::buzzer_->Start(500,50);
  //Objects::md_->ShortBrake();
  // core->Stop();
  // Objects::wait_->Ms(100);
  //Objects::led_->Off();
  // Objects::buzzer_->Stop();
  // Objects::buzzer_->Start(500,10 );
  //Objects::md_->ShortBrake();
  // Objects::wait_->Ms(100);
  // Objects::buzzer_->Stop();
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
