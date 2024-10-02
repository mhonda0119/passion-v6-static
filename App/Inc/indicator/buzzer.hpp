#ifndef _BUZZER_HPP_
#define _BUZZER_HPP_

#include "pwm_driver.hpp"

namespace indicator::buzzer{
    class Driver{
    private:
        uint32_t freq_;
        uint32_t duration;
        std::unique_ptr<peripheral::pwm::Driver> pwm_;
    public:
        Driver();//pwm_driverのインスタンス化
        void Start(uint32_t freq,float duty = 0.5);//指定された周波数で鳴らす
        void Play(uint32_t freq,uint32_t duration,float duty = 0.5);//指定された周波数，指定された秒数鳴らす
        void Stop();//とめる．
        ~Driver() = default;
    };
}

#endif /* _BUZZER_HPP_ */


