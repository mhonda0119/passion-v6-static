#include "tb6612fng.hpp"

namespace md{

    TB6612FNG::TB6612FNG(TIM_HandleTypeDef* htim,uint32_t channel_l,uint32_t channel_r,
        GPIO_TypeDef* stby_port,uint16_t stby_pin,
        GPIO_TypeDef* l_cw_port,uint16_t l_cw_pin,
        GPIO_TypeDef* l_ccw_port,uint16_t l_ccw_pin,
        GPIO_TypeDef* r_cw_port,uint16_t r_cw_pin,
        GPIO_TypeDef* r_ccw_port,uint16_t r_ccw_pin): 
        pwm_r_(std::make_unique<peripheral::PWM>(htim, channel_r)),
        pwm_l_(std::make_unique<peripheral::PWM>(htim, channel_l)),
        stby_port_ (stby_port),
        stby_pin_ (stby_pin),
        l_cw_port_ (l_cw_port),
        l_cw_pin_ (l_cw_pin),
        l_ccw_port_ (l_ccw_port),
        l_ccw_pin_ (l_ccw_pin),
        r_cw_port_ (r_cw_port),
        r_cw_pin_ (r_cw_pin),
        r_ccw_port_ (r_ccw_port),
        r_ccw_pin_ (r_ccw_pin){}

    void TB6612FNG::On(){
        std::cout << "TB6612FNG::On" << std::endl;
        HAL_GPIO_WritePin(stby_port_, stby_pin_, GPIO_PIN_SET);
    }

    void TB6612FNG::Dir(state::MOTOR motor ,state::MOTOR dir){
        if (motor == state::MOTOR::LEFT) {
            if (dir == state::MOTOR::FWD) {
                // 左モーターを前進方向に設定
                HAL_GPIO_WritePin(l_cw_port_, l_cw_pin_, GPIO_PIN_SET);
                HAL_GPIO_WritePin(l_ccw_port_, l_ccw_pin_, GPIO_PIN_RESET);
            } else if (dir == state::MOTOR::BWD) {
                // 左モーターを後進方向に設定
                HAL_GPIO_WritePin(l_cw_port_, l_cw_pin_, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(l_ccw_port_, l_ccw_pin_, GPIO_PIN_SET);
            }
        } else if (motor == state::MOTOR::RIGHT) {
            if (dir == state::MOTOR::FWD) {
                // 右モーターを前進方向に設定
                HAL_GPIO_WritePin(r_cw_port_, r_cw_pin_, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(r_ccw_port_, r_ccw_pin_, GPIO_PIN_SET);
            } else if (dir == state::MOTOR::BWD) {
                // 右モーターを後進方向に設定
                HAL_GPIO_WritePin(r_cw_port_, r_cw_pin_, GPIO_PIN_SET);
                HAL_GPIO_WritePin(r_ccw_port_, r_ccw_pin_, GPIO_PIN_RESET);
            }
        }
    std::cout << "TB6612FNG::Dir" << std::endl;
    }

    void TB6612FNG::Duty(float duty_l,float duty_r){
        pwm_l_ -> set_duty(duty_l);
        pwm_r_ -> set_duty(duty_r);
    std::cout << "TB6612FNG::Duty" << std::endl;
    }

    void TB6612FNG::Freq(uint32_t freq_l,uint32_t freq_r){
        pwm_l_ -> set_freq(freq_l);
        pwm_r_ -> set_freq(freq_r);
    }

    void TB6612FNG::Start(){
        pwm_r_ -> Start();
        pwm_l_ -> Start();
    std::cout << "TB6612FNG::Start" << std::endl;
    }

    void TB6612FNG::Stop(){
        pwm_r_ -> Stop();
        pwm_l_ -> Stop();
    }

    void TB6612FNG::Off(){
        HAL_GPIO_WritePin(stby_port_, stby_pin_, GPIO_PIN_RESET);
    }

}