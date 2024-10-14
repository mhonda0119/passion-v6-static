#include "gpio.hpp"

namespace peripheral{

    GPIO::GPIO(GPIO_TypeDef* port,uint16_t pin):port_(port), pin_(pin) {}

    void GPIO::On(){
        HAL_GPIO_WritePin(port_,pin_,GPIO_PIN_SET);
    }

    void GPIO::Off(){
        HAL_GPIO_WritePin(port_,pin_,GPIO_PIN_RESET);
    }

    void GPIO::Toggle(){
        HAL_GPIO_TogglePin(port_,pin_);
    }

    bool GPIO::ReadVal(){
        return (HAL_GPIO_ReadPin(port_, pin_) == GPIO_PIN_RESET);
    }

}