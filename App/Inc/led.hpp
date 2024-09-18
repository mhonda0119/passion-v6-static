#ifndef _LED_HPP_
#define _LED_HPP_

#include "peripheral.h"
#include "gpio_driver.hpp"
#include <memory>
#include <iostream>
#include "main.h"
#include <cstdint>

namespace indicator::led{
    class Driver{
    private:
    std::unique_ptr<gpio::Driver> led_[8];
    public:
        Driver();
        void On(uint8_t num = 8); //なんもしなければ全部点灯．引数入れればそのledだけ点灯
        void Off(uint8_t num = 8);//なんもしなければ全部消灯．引数入れればそのledだけ消灯
        void Toggle(uint8_t num = 8);//なんもしなければ全部toggle.引数入れればそのledだけtoggle
        ~Driver() = default;
    };
}

#endif //_LED_HPP_