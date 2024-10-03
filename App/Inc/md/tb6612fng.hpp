#ifndef _TB6612FNG_HPP_
#define _TB6612FNG_HPP_

#include "md.hpp"


namespace  md{

    class TB6612FNG : public Product{

    private:
        std::unique_ptr<peripheral::PWM> pwm_r_ ;
        std::unique_ptr<peripheral::PWM> pwm_l_ ;
    public:
        TB6612FNG(TIM_HandleTypeDef* htim,uint32_t channel_l,uint32_t channel_r);//こいつの使ってるpinを割り当てる．in1,in2,stby,pwm,(pwmはmotordriverに与えるものかぁ．)
        void On() override;//stbyをh
        void Dir(parameter::MOTOR motor ,parameter::MOTOR dir) override;//SetDirする
        void Start() override;//pwmスタート
        void Duty(float duty_l,float duty_r) override;
        void Freq(uint32_t freq_l,uint32_t freq_r)override;
        void Stop() override;//pwmストップ
        void Off() override;//stbyをl
        virtual ~TB6612FNG() = default;
    };

}

#endif /* _TB6612FNG_HPP_ */

