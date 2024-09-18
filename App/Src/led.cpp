#include "led.hpp"

namespace indicator::led{
    Driver::Driver(){
    led_[0] = std::make_unique<gpio::Driver>(LED_1_GPIO_Port, LED_1_Pin);
    led_[1] = std::make_unique<gpio::Driver>(LED_2_GPIO_Port, LED_2_Pin);
    led_[2] = std::make_unique<gpio::Driver>(LED_3_GPIO_Port, LED_3_Pin);
    led_[3] = std::make_unique<gpio::Driver>(LED_4_GPIO_Port, LED_4_Pin);
    led_[4] = std::make_unique<gpio::Driver>(LED_5_GPIO_Port, LED_5_Pin);
    led_[5] = std::make_unique<gpio::Driver>(LED_6_GPIO_Port, LED_6_Pin);
    led_[6] = std::make_unique<gpio::Driver>(LED_7_GPIO_Port, LED_7_Pin);
    }
    void Driver::On(uint8_t num){
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
        }
    }
    void Driver::Off(uint8_t num){
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
        }
    }
    void Driver::Toggle(uint8_t num){
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
        }
    }

}