#include "ir.hpp"

namespace ir{
    Driver::Driver(){
    std::unique_ptr<gpio::LED> r_ = std::make_unique<gpio::LED>(IR_R_GPIO_Port, IR_R_Pin);
    std::unique_ptr<gpio::LED> l_ = std::make_unique<gpio::LED>(IR_L_GPIO_Port, IR_L_Pin);
    std::unique_ptr<gpio::LED> fr_ = std::make_unique<gpio::LED>(IR_FR_GPIO_Port, IR_FR_Pin);
    std::unique_ptr<gpio::LED> fl_ = std::make_unique<gpio::LED>(IR_FL_GPIO_Port, IR_FL_Pin);
    };

    void Driver::On(DIR dir){
        switch(dir){
            case DIR::ALL:
                r_->On();
                l_->On();
                fr_->On();
                fl_->On();
            case DIR::R:
                r_->On();
                break;
            case DIR::L:
                l_->On();
                break;
            case DIR::FR:
                fr_->On();
                break;
            case DIR::FL:
                fl_->On();
                break;
        }
    }

    void Driver::Off(DIR dir){
        switch(dir){
            case DIR::ALL:
                r_->Off();
                l_->Off();
                fr_->Off();
                fl_->Off();
            case DIR::R:
                r_->Off();
                break;
            case DIR::L:
                l_->Off();
                break;
            case DIR::FR:
                fr_->Off();
                break;
            case DIR::FL:
                fl_->Off();
                break;
        }

    }

}