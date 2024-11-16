#ifndef _TB6612FNG_HPP_
#define _TB6612FNG_HPP_

#include "md.hpp"


namespace  md{

    class TB6612FNG : public Product{

    private:
        std::unique_ptr<peripheral::PWM> pwm_r_ ;
        std::unique_ptr<peripheral::PWM> pwm_l_ ;
        GPIO_TypeDef* stby_port_;
        uint16_t stby_pin_;
        GPIO_TypeDef* l_cw_port_;
        uint16_t l_cw_pin_;
        GPIO_TypeDef* l_ccw_port_;
        uint16_t l_ccw_pin_;
        GPIO_TypeDef* r_cw_port_;
        uint16_t r_cw_pin_;
        GPIO_TypeDef* r_ccw_port_;
        uint16_t r_ccw_pin_;
    public:
        TB6612FNG(TIM_HandleTypeDef* htim,uint32_t channel_l,uint32_t channel_r,
        GPIO_TypeDef* stby_port,uint16_t stby_pin,
        GPIO_TypeDef* l_cw_port,uint16_t l_cw_pin,
        GPIO_TypeDef* l_ccw_port,uint16_t l_ccw_pin,
        GPIO_TypeDef* r_cw_port,uint16_t r_cw_pin,
        GPIO_TypeDef* r_ccw_port,uint16_t r_ccw_pin);//こいつの使ってるpinを割り当てる．in1,in2,stby,pwm,(pwmはmotordriverに与えるものかぁ．)
        void On() override;//stbyをh
        void Dir(state::MOTOR motor ,state::MOTOR dir) override;//SetDirする
        void Duty(float duty_l,float duty_r) override; //dutyは0-100で指定%で指定
        void Freq(uint32_t freq_l,uint32_t freq_r)override;
        void Start() override;//pwmスタート
        void Stop() override;//pwmストップ
        void Off() override;//stbyをl
        virtual ~TB6612FNG() = default;
    };

}

#endif /* _TB6612FNG_HPP_ */

