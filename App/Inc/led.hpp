#ifndef _LED_HPP_
#define _LED_HPP_

#include "peripheral.h"
#include "main.h"
#include "stdout.h"
#include <iostream>

namespace gpio{
    class LED{
    private:
        GPIO_TypeDef* port_;
        uint16_t pin_;
    public:
        LED(GPIO_TypeDef *,uint16_t);
        void On();
        void Off();
        void Toggle();
        ~LED() = default;
    };
}

#endif //_LED_HPP_