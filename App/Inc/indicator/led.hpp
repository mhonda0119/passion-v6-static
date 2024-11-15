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
        LED(GPIO_TypeDef* led_1_port,uint16_t led_1_pin,
            GPIO_TypeDef* led_2_port,uint16_t led_2_pin,
            GPIO_TypeDef* led_3_port,uint16_t led_3_pin,
            GPIO_TypeDef* led_4_port,uint16_t led_4_pin,
            GPIO_TypeDef* led_5_port,uint16_t led_5_pin,
            GPIO_TypeDef* led_6_port,uint16_t led_6_pin,
            GPIO_TypeDef* led_7_port,uint16_t led_7_pin);
        void On(uint8_t num = 8); //なんもしなければ全部点灯．引数入れればそのledだけ点灯
        void Off(uint8_t num = 8);//なんもしなければ全部消灯．引数入れればそのledだけ消灯
        void Toggle(uint8_t num = 8);//なんもしなければ全部toggle.引数入れればそのledだけtoggle
        ~LED() = default;
    };
}

#endif //_LED_HPP_