#ifndef _GPIO_DRIVER_HPP_
#define _GPIO_DRIVER_HPP_

#include "peripheral.h"
#include "main.h"
#include "stdout.h"
#include <iostream>

namespace peripheral::gpio{
    class Driver{
    private:
        GPIO_TypeDef* port_;
        uint16_t pin_;
    public:
        Driver(GPIO_TypeDef* port,uint16_t pin);
        void On();
        void Off();
        void Toggle();
        ~Driver() = default;
    };
}

#endif //_GPIO_DRIVER_HPP_