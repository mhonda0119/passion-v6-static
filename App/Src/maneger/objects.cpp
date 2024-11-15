#include "objects.hpp"
//Core_objects
// std::unique_ptr<sensor::imu::Creater> Objects::imu_creater_ = std::make_unique<sensor::imu::Creater>(sensor::imu::NAME::ICM20689);
// std::unique_ptr<sensor::imu::Creater> Objects::imu_creater_ = std::make_unique<sensor::imu::Creater>(sensor::imu::NAME::ICM20689);
// std::unique_ptr<sensor::encoder::Creater> Objects::encoder_creater_ = std::make_unique<sensor::encoder::Creater>(sensor::encoder::NAME::IEH24096);
// std::unique_ptr<sensor::pxstr::Creater> Objects::pxstr_creater_ = std::make_unique<sensor::pxstr::Creater>(sensor::pxstr::NAME::ST1KL3A);
// std::unique_ptr<md::Creater> Objects::md_creater_ = std::make_unique<md::Creater>(md::NAME::TB6612FNG);
//Core_objects
// std::unique_ptr<sensor::imu::Product> Objects::imu_ = Objects::imu_creater_->Create(&hspi3,GPIOD,CS_Pin);
// std::unique_ptr<sensor::encoder::Product> Objects::encoder_r_ = Objects::encoder_creater_->Create(&htim8, TIM_CHANNEL_ALL);
// std::unique_ptr<sensor::encoder::Product> Objects::encoder_l_ = Objects::encoder_creater_->Create(&htim4, TIM_CHANNEL_ALL);
// std::unique_ptr<sensor::pxstr::Product> Objects::pxstr_ = Objects::pxstr_creater_->Create(&hadc1);
// std::unique_ptr<sensor::ir::OSI3CA5111A> Objects::osi3ca5111a_ = std::make_unique<sensor::ir::OSI3CA5111A>(IR_R_GPIO_Port,IR_R_Pin,
//                                                                                                     IR_L_GPIO_Port,IR_L_Pin,
//                                                                                                     IR_FR_GPIO_Port,IR_FR_Pin,
//                                                                                                     IR_FL_GPIO_Port,IR_FL_Pin);
std::unique_ptr<peripheral::Wait> Objects::wait_ = std::make_unique<peripheral::Wait>(&htim1);
std::unique_ptr<indicator::LED> Objects::led_ = std::make_unique<indicator::LED>(LED_1_GPIO_Port,LED_1_Pin,
                                                                        LED_2_GPIO_Port,LED_2_Pin,
                                                                        LED_3_GPIO_Port,LED_3_Pin,
                                                                        LED_4_GPIO_Port,LED_4_Pin,
                                                                        LED_5_GPIO_Port,LED_5_Pin,
                                                                        LED_6_GPIO_Port,LED_6_Pin,
                                                                        LED_7_GPIO_Port,LED_7_Pin);
// std::unique_ptr<md::Product> Objects::md_ = Objects::md_creater_->Create(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_4, 
//                                                                         MOTOR_STBY_GPIO_Port, MOTOR_STBY_Pin,
//                                                                         MOTOR_L_CW_GPIO_Port, MOTOR_L_CW_Pin,
//                                                                         MOTOR_L_CCW_GPIO_Port, MOTOR_L_CCW_Pin,
//                                                                         MOTOR_R_CW_GPIO_Port, MOTOR_R_CW_Pin,
//                                                                         MOTOR_R_CCW_GPIO_Port, MOTOR_R_CCW_Pin);
std::unique_ptr<indicator::Buzzer> Objects::buzzer_ = std::make_unique<indicator::Buzzer>(&htim3, TIM_CHANNEL_2);