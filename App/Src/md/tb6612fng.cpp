#include "tb6612fng.hpp"

namespace motor_driver{

    TB6612FNG::TB6612FNG() {
        //コンストラクタの中_
        pwm_r_ = std::make_unique<peripheral::pwm::Driver>(&htim2, TIM_CHANNEL_4);
        pwm_l_ = std::make_unique<peripheral::pwm::Driver>(&htim2, TIM_CHANNEL_1);
    }



    void TB6612FNG::On(){
        HAL_GPIO_WritePin(MOTOR_STBY_GPIO_Port, MOTOR_STBY_Pin, GPIO_PIN_SET);
    }

    void TB6612FNG::Dir(MOTOR motor ,DIR dir){
        if (motor == MOTOR::LEFT) {
            if (dir == DIR::CW) {
                // 左モーターを前進方向に設定
                HAL_GPIO_WritePin(MOTOR_L_CW_GPIO_Port, MOTOR_L_CW_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(MOTOR_L_CCW_GPIO_Port, MOTOR_L_CCW_Pin, GPIO_PIN_RESET);
            } else if (dir == DIR::CCW) {
                // 左モーターを後進方向に設定
                HAL_GPIO_WritePin(MOTOR_L_CW_GPIO_Port, MOTOR_L_CW_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(MOTOR_L_CCW_GPIO_Port, MOTOR_L_CCW_Pin, GPIO_PIN_SET);
            }
        } else if (motor == MOTOR::RIGHT) {
            if (dir == DIR::CW) {
                // 右モーターを前進方向に設定
                HAL_GPIO_WritePin(MOTOR_R_CW_GPIO_Port, MOTOR_R_CW_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(MOTOR_R_CCW_GPIO_Port, MOTOR_R_CCW_Pin, GPIO_PIN_RESET);
            } else if (dir == DIR::CCW) {
                // 右モーターを後進方向に設定
                HAL_GPIO_WritePin(MOTOR_R_CW_GPIO_Port, MOTOR_R_CW_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(MOTOR_R_CCW_GPIO_Port, MOTOR_R_CCW_Pin, GPIO_PIN_SET);
            }
        }
    }

    void TB6612FNG::Start(){
        pwm_r_ -> Start();
        pwm_l_ -> Start();
    }

    void TB6612FNG::Duty(float duty_l,float duty_r){
        pwm_l_ -> set_duty(duty_l);
        pwm_r_ -> set_duty(duty_r);
    }

    void TB6612FNG::Freq(uint32_t freq_l,uint32_t freq_r){
        pwm_l_ -> set_freq(freq_l);
        pwm_r_ -> set_freq(freq_r);
    }

    void TB6612FNG::Stop(){
        pwm_r_ -> Stop();
        pwm_l_ -> Stop();
    }

    void TB6612FNG::Off(){
        HAL_GPIO_WritePin(MOTOR_STBY_GPIO_Port, MOTOR_STBY_Pin, GPIO_PIN_RESET);
    }

}