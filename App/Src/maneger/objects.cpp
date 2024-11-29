#include "objects.hpp"

//全てnullptrで一旦初期化
std::unique_ptr<sensor::imu::Product> Objects::imu_ = nullptr;
std::unique_ptr<sensor::encoder::Combine> Objects::encoder_ = nullptr;
std::unique_ptr<sensor::pxstr::Product> Objects::pxstr_ = nullptr;
std::unique_ptr<sensor::ir::OSI3CA5111A> Objects::ir_ = nullptr;
std::unique_ptr<sensor::Wall> Objects::wall_ = nullptr;
std::unique_ptr<ctrl::AccelDesigner> Objects::accel_designer_ = nullptr;
std::unique_ptr<regulator::Motor> Objects::motor_reg_ = nullptr;
std::unique_ptr<md::Product> Objects::md_ = nullptr;
std::unique_ptr<peripheral::Wait> Objects::wait_ = nullptr;
std::unique_ptr<indicator::LED> Objects::led_ = nullptr;
std::unique_ptr<indicator::Buzzer> Objects::buzzer_ = nullptr;
std::unique_ptr<sensor::bat::Vol> Objects::vol_ = nullptr;
std::unique_ptr<ctrl::slalom::Trajectory> Objects::traj_l90_ = nullptr;
std::unique_ptr<ctrl::slalom::Trajectory> Objects::traj_r90_ = nullptr;
void Objects::Init(){
    //shared_ptrの初期化
    std::shared_ptr<peripheral::ADC> adc = std::make_shared<peripheral::ADC>(&hadc1);
    //std::cout << "adc_Instance" << std::endl;
    //imuの初期化
    std::unique_ptr<sensor::imu::Creater> imu_creater_ = std::make_unique<sensor::imu::Creater>(sensor::imu::NAME::ICM20689);
    Objects::imu_ = imu_creater_->Create(&hspi3,GPIOD,CS_Pin);
    //std::cout << "imu_Instance" << std::endl;
    //エンコーダの初期化
    Objects::encoder_ = std::make_unique<sensor::encoder::Combine>();
    //std::cout << "encoder_Instance" << std::endl;
    //フォトトランジスタの初期化
    std::unique_ptr<sensor::pxstr::Creater> pxstr_creater_ = std::make_unique<sensor::pxstr::Creater>(sensor::pxstr::NAME::ST1KL3A);
    Objects::pxstr_ = pxstr_creater_->Create(adc);
    //std::cout << "pxstr_Instance" << std::endl;
    //赤外線センサの初期化
    Objects::ir_ = std::make_unique<sensor::ir::OSI3CA5111A>(IR_R_GPIO_Port,IR_R_Pin,
                                                                        IR_L_GPIO_Port,IR_L_Pin,
                                                                        IR_FR_GPIO_Port,IR_FR_Pin,
                                                                        IR_FL_GPIO_Port,IR_FL_Pin);
    //std::cout << "ir_Instance" << std::endl;
    //waitの初期化
    Objects::wait_ = std::make_unique<peripheral::Wait>(&htim1);
    //std::cout << "wait_Instance" << std::endl;
    //ledの初期化
    Objects::led_ = std::make_unique<indicator::LED>(LED_1_GPIO_Port,LED_1_Pin,
                                                    LED_2_GPIO_Port,LED_2_Pin,
                                                    LED_3_GPIO_Port,LED_3_Pin,
                                                    LED_4_GPIO_Port,LED_4_Pin,
                                                    LED_5_GPIO_Port,LED_5_Pin,
                                                    LED_6_GPIO_Port,LED_6_Pin,
                                                    LED_7_GPIO_Port,LED_7_Pin);
    //std::cout << "led_Instance" << std::endl;
    //Wallの初期化
    Objects::wall_ = std::make_unique<sensor::Wall>(Objects::pxstr_,Objects::ir_,Objects::wait_,Objects::led_);
    //std::cout << "wall_Instance" << std::endl;  
    //accel_designerの初期化
    Objects::accel_designer_ = std::make_unique<ctrl::AccelDesigner>();
    //std::cout << "accel_designer_Instance" << std::endl;
    //traj_l90_の初期化
        //slalomの事前設計
        //設計パラメータ定義
        const ctrl::Pose pose_total_l90 = ctrl::Pose(90, 90, consts::physics::PI / 2); //< 探索90度ターンを想定
        const float y_curve = 90;
        //スラロームの形状を定義
        ctrl::slalom::Shape shape_l90 = ctrl::slalom::Shape(pose_total_l90, y_curve,0,
        consts::software::SL_JERK_MAX*consts::physics::DEG2RAD,
        consts::software::SL_ALPHA_MAX*consts::physics::DEG2RAD,
        consts::software::SL_OMEGA_MAX*consts::physics::DEG2RAD);
        //スラロームの軌道を生成(trajectory_の初期化)
        Objects::traj_l90_ = std::make_unique<ctrl::slalom::Trajectory>(shape_l90);
    //std::cout << "traj_l90_Instance" << std::endl;
    //traj_r90_の初期化
        //slalomの事前設計
        //設計パラメータ定義
        ctrl::Pose pose_total_r90 = ctrl::Pose(90, -90, -consts::physics::PI / 1.8); //< 探索90度ターンを想定
        //スラロームの形状を定義
        ctrl::slalom::Shape shape_r90 = ctrl::slalom::Shape(pose_total_r90, -y_curve,0,
        consts::software::SL_JERK_MAX*consts::physics::DEG2RAD,
        consts::software::SL_ALPHA_MAX*consts::physics::DEG2RAD,
        consts::software::SL_OMEGA_MAX*consts::physics::DEG2RAD);
        //スラロームの軌道を生成(trajectory_の初期化)
        Objects::traj_r90_ = std::make_unique<ctrl::slalom::Trajectory>(shape_r90);
    //std::cout << "traj_r90_Instance" << std::endl;
    //regulatorの初期化
    Objects::motor_reg_ = std::make_unique<regulator::Motor>(Objects::wall_,Objects::imu_,Objects::encoder_,Objects::accel_designer_,
                                                                Objects::traj_l90_,Objects::traj_r90_);
    //std::cout << "motor_reg_Instance" << std::endl;
    //モタドラの初期化
    std::unique_ptr<md::Creater> md_creater_ = std::make_unique<md::Creater>(md::NAME::TB6612FNG);
    Objects::md_ = md_creater_->Create(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_4, 
                                        MOTOR_STBY_GPIO_Port, MOTOR_STBY_Pin,
                                        MOTOR_L_CW_GPIO_Port, MOTOR_L_CW_Pin,
                                        MOTOR_L_CCW_GPIO_Port, MOTOR_L_CCW_Pin,
                                        MOTOR_R_CW_GPIO_Port, MOTOR_R_CW_Pin,
                                        MOTOR_R_CCW_GPIO_Port, MOTOR_R_CCW_Pin);
    //std::cout << "md_Instance" << std::endl;

    //buzzerの初期化
    Objects::buzzer_ = std::make_unique<indicator::Buzzer>(&htim3, TIM_CHANNEL_2);
    //std::cout << "buzzer_Instance" << std::endl;
    //volの初期化
    Objects::vol_ = std::make_unique<sensor::bat::Vol>(adc);
    //std::cout << "vol_Instance" << std::endl;


}