#include "led.hpp"

namespace gpio{

    LED::LED(GPIO_TypeDef* port,uint16_t pin){
        port_ = port;
        pin_ = pin;
    }

    void LED::On(){
        HAL_GPIO_WritePin(port_,pin_,GPIO_PIN_SET);
    }

    void LED::Off(){
        HAL_GPIO_WritePin(port_,pin_,GPIO_PIN_RESET);
    }

    void LED::Toggle(){
        HAL_GPIO_TogglePin(port_,pin_);
    }

}