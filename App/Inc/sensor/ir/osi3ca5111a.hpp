#ifndef _IR_HPP_
#define _IR_HPP_

#include "peripheral.h"
#include "states.hpp"
#include "gpio.hpp"
#include "main.h"
#include <memory>
#include <iostream>

namespace sensor::ir{
    class OSI3CA5111A{
    private:
    state::Wall dir_;
    std::unique_ptr<peripheral::GPIO> r_;
    std::unique_ptr<peripheral::GPIO> l_;
    std::unique_ptr<peripheral::GPIO> fr_;
    std::unique_ptr<peripheral::GPIO> fl_;
    public:
        OSI3CA5111A(GPIO_TypeDef* r_port,uint16_t r_pin,
        GPIO_TypeDef* l_port,uint16_t l_pin,
        GPIO_TypeDef* fr_port,uint16_t fr_pin,
        GPIO_TypeDef* fl_port,uint16_t fl_pin);
        void On(state::Wall::DIR dir = state::Wall::DIR::ALL);
        void Off(state::Wall::DIR dir = state::Wall::DIR::ALL);
        ~OSI3CA5111A() = default;
    };
}

#endif //_IR_HPP_