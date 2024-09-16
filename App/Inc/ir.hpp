#ifndef _IR_HPP_
#define _IR_HPP_

#include "peripheral.h"
#include "wall_parameter.hpp"
#include "led.hpp"
#include "main.h"
#include <memory>
#include <iostream>

namespace ir{
    class Driver{
    private:
    DIR dir_;
    std::unique_ptr<gpio::LED> r_;
    std::unique_ptr<gpio::LED> l_;
    std::unique_ptr<gpio::LED> fr_;
    std::unique_ptr<gpio::LED> fl_;
    public:
        Driver();
        void On(DIR dir = DIR::ALL);
        void Off(DIR dir = DIR::ALL);
        ~Driver() = default;
    };
}

#endif //_IR_HPP_