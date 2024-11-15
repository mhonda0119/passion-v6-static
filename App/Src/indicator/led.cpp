#include "led.hpp"

namespace indicator{
    LED::LED(GPIO_TypeDef* led_1_port,uint16_t led_1_pin,
            GPIO_TypeDef* led_2_port,uint16_t led_2_pin,
            GPIO_TypeDef* led_3_port,uint16_t led_3_pin,
            GPIO_TypeDef* led_4_port,uint16_t led_4_pin,
            GPIO_TypeDef* led_5_port,uint16_t led_5_pin,
            GPIO_TypeDef* led_6_port,uint16_t led_6_pin,
            GPIO_TypeDef* led_7_port,uint16_t led_7_pin){
        led_[0] = std::make_unique<peripheral::GPIO>(led_1_port, led_1_pin);
        led_[1] = std::make_unique<peripheral::GPIO>(led_2_port, led_2_pin);
        led_[2] = std::make_unique<peripheral::GPIO>(led_3_port, led_3_pin);
        led_[3] = std::make_unique<peripheral::GPIO>(led_4_port, led_4_pin);
        led_[4] = std::make_unique<peripheral::GPIO>(led_5_port, led_5_pin);
        led_[5] = std::make_unique<peripheral::GPIO>(led_6_port, led_6_pin);
        led_[6] = std::make_unique<peripheral::GPIO>(led_7_port, led_7_pin);
}
    void LED::On(uint8_t num){
        switch(num){
            case 1:
                led_[0] -> On();
                break;
            case 2:
                led_[1] -> On();
                break;
            case 3:
                led_[2] -> On();
                break;
            case 4:
                led_[3] -> On();
                break;
            case 5:
                led_[4] -> On();
                break;
            case 6:
                led_[5] -> On();
                break;
            case 7:
                led_[6] -> On();
                break;
            case 8:
                for(int i = 0; i < 7; i++){
                    led_[i] -> On();
                }
                break;
            default:
                break;
        }
    }

    void LED::Off(uint8_t num){
        switch(num){
            case 1:
                led_[0] -> Off();
                break;
            case 2:
                led_[1] -> Off();
                break;
            case 3:
                led_[2] -> Off();
                break;
            case 4:
                led_[3] -> Off();
                break;
            case 5:
                led_[4] -> Off();
                break;
            case 6:
                led_[5] -> Off();
                break;
            case 7:
                led_[6] -> Off();
                break;
            case 8:
                for(int i = 0; i < 7; i++){
                    led_[i] -> Off();
                }
                break;
            default:
                break;
        }
    }

    void LED::Toggle(uint8_t num){
        switch(num){
            case 1:
                led_[0] -> Toggle();
                break;
            case 2:
                led_[1] -> Toggle();
                break;
            case 3:
                led_[2] -> Toggle();
                break;
            case 4:
                led_[3] -> Toggle();
                break;
            case 5:
                led_[4] -> Toggle();
                break;
            case 6:
                led_[5] -> Toggle();
                break;
            case 7:
                led_[6] -> Toggle();
                break;
            case 8:
                for(int i = 0; i < 7; i++){
                    led_[i] -> Toggle();
                }
                break;
            default:
                break;
        }
    }
} // namespace indicator