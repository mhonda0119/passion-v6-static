#include "osi3ca5111a.hpp"

namespace sensor::ir{
    OSI3CA5111A::OSI3CA5111A(GPIO_TypeDef* r_port,uint16_t r_pin,
        GPIO_TypeDef* l_port,uint16_t l_pin,
        GPIO_TypeDef* fr_port,uint16_t fr_pin,
        GPIO_TypeDef* fl_port,uint16_t fl_pin):
        r_ (std::make_unique<peripheral::GPIO>(r_port, r_pin)),
        l_ (std::make_unique<peripheral::GPIO>(l_port, l_pin)),
        fr_ (std::make_unique<peripheral::GPIO>(fr_port, fr_pin)),
        fl_ (std::make_unique<peripheral::GPIO>(fl_port, fl_pin)){}

    void OSI3CA5111A::On(state::Wall::DIR dir){
        switch(dir){
            case state::Wall::DIR::ALL:
                r_->On();
                l_->On();
                fr_->On();
                fl_->On();
                break;
            case state::Wall::DIR::R:
                r_->On();
                break;
            case state::Wall::DIR::L:
                l_->On();
                break;
            case state::Wall::DIR::FR:
                fr_->On();
                break;
            case state::Wall::DIR::FL:
                fl_->On();
                break;
            default:
                break;
        }
    }

    void OSI3CA5111A::Off(state::Wall::DIR dir){
        switch(dir){
            case state::Wall::DIR::ALL:
                r_->Off();
                l_->Off();
                fr_->Off();
                fl_->Off();
                break;
            case state::Wall::DIR::R:
                r_->Off();
                break;
            case state::Wall::DIR::L:
                l_->Off();
                break;
            case state::Wall::DIR::FR:
                fr_->Off();
                break;
            case state::Wall::DIR::FL:
                fl_->Off();
                break;
            default:
                break;
        }

    }

}