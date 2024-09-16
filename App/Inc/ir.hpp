#ifndef _IR_HPP_
#define _IR_HPP_

#include "peripheral.h"
#include "wall_parameter.hpp"
#include "led.hpp"
#include <memory>

namespace ir{
    class Driver{
    private:
    DIR dir_;
    std::unique_ptr<gpio::LED> r_;
    std::unique_ptr<gpio::LED> l_;
    std::unique_ptr<gpio::LED> fr_;
    std::unique_ptr<gpio::LED> fl_;
    public:
        Driver();//ledをインスタンス化して4つ分
        void On(DIR dir = DIR::ALL);//何も引数取らなかったら全部光らせて指定したら指定
        void Off(DIR dir = DIR::ALL);//何も引数取らなかったら全部光らせて指定したら指定
        ~Driver() = default;
    };
}

#endif //_IR_HPP_