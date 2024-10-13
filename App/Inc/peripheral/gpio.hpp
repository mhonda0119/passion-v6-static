#ifndef _GPIO_HPP_
#define _GPIO_HPP_

#include "peripheral.h"
#include "main.h"
#include "stdout.h"
#include <iostream>

namespace peripheral{
    class GPIO{
    private:
        GPIO_TypeDef* port_;
        uint16_t pin_;
    public:
        GPIO(GPIO_TypeDef* port,uint16_t pin);
        void On();
        void Off();
        void Toggle();
        bool ReadVal();
        ~GPIO() = default;
    };
}

#endif //_GPIO_HPP_