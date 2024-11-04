#include "osi3ca5111a.hpp"

namespace sensor::ir{
    OSI3CA5111A::OSI3CA5111A():
        r_ (std::make_unique<peripheral::GPIO>(IR_R_GPIO_Port, IR_R_Pin)),
        l_ (std::make_unique<peripheral::GPIO>(IR_L_GPIO_Port, IR_L_Pin)),
        fr_ (std::make_unique<peripheral::GPIO>(IR_FR_GPIO_Port, IR_FR_Pin)),
        fl_ (std::make_unique<peripheral::GPIO>(IR_FL_GPIO_Port, IR_FL_Pin)){}

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
        }

    }

}