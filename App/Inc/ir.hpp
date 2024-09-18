#ifndef _IR_HPP_
#define _IR_HPP_

#include "peripheral.h"
#include "wall_parameter.hpp"
#include "gpio_driver.hpp"
#include "main.h"
#include <memory>
#include <iostream>

namespace ir{
    class Driver{
    private:
    DIR dir_;
    std::unique_ptr<gpio::Driver> r_;
    std::unique_ptr<gpio::Driver> l_;
    std::unique_ptr<gpio::Driver> fr_;
    std::unique_ptr<gpio::Driver> fl_;
    public:
        Driver();
        void On(DIR dir = DIR::ALL);
        void Off(DIR dir = DIR::ALL);
        ~Driver() = default;
    };
}

#endif //_IR_HPP_