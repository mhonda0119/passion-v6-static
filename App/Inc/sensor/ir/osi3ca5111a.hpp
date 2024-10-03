#ifndef _IR_HPP_
#define _IR_HPP_

#include "peripheral.h"
#include "wall_parameter.hpp"
#include "gpio.hpp"
#include "main.h"
#include <memory>
#include <iostream>

namespace sensor::ir{
    class OSI3CA5111A{
    private:
    DIR dir_;
    std::unique_ptr<peripheral::GPIO> r_;
    std::unique_ptr<peripheral::GPIO> l_;
    std::unique_ptr<peripheral::GPIO> fr_;
    std::unique_ptr<peripheral::GPIO> fl_;
    public:
        OSI3CA5111A();
        void On(DIR dir = DIR::ALL);
        void Off(DIR dir = DIR::ALL);
        ~OSI3CA5111A() = default;
    };
}

#endif //_IR_HPP_