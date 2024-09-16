#ifndef _LED_HPP_
#define _LED_HPP_

#include "peripheral.h"

namespace gpio{
    class LED{
    private:
        GPIO_TypeDef* port_;  // GPIOポート
        uint16_t pin_;    // GPIOピン番号
    public:
        LED(GPIO_TypeDef*,uint16_t);
        void On();
        void Off();
        void Toggle();
        ~LED() = default;
    };
}

#endif //_LED_HPP_