#include "gpio_driver.hpp"

namespace gpio{

    Driver::Driver(GPIO_TypeDef* port,uint16_t pin):port_(port), pin_(pin) {}

    void Driver::On(){
        HAL_GPIO_WritePin(port_,pin_,GPIO_PIN_SET);
    }

    void Driver::Off(){
        HAL_GPIO_WritePin(port_,pin_,GPIO_PIN_RESET);
    }

    void Driver::Toggle(){
        HAL_GPIO_TogglePin(port_,pin_);
    }

}