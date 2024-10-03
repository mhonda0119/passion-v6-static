#ifndef _LED_HPP_
#define _LED_HPP_

#include <memory>
#include <iostream>
#include <cstdint>
#include "peripheral.h"
#include "gpio.hpp"
#include "main.h"

namespace indicator{
    class LED{
    private:
    std::unique_ptr<peripheral::GPIO> led_[8];
    public:
        LED();
        void On(uint8_t num = 8); //なんもしなければ全部点灯．引数入れればそのledだけ点灯
        void Off(uint8_t num = 8);//なんもしなければ全部消灯．引数入れればそのledだけ消灯
        void Toggle(uint8_t num = 8);//なんもしなければ全部toggle.引数入れればそのledだけtoggle
        ~LED() = default;
    };
}

#endif //_LED_HPP_