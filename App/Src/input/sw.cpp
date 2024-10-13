#include "sw.hpp"

namespace input{
SW::SW(GPIO_TypeDef* port,uint16_t pin)
 :  gpio_(std::make_unique<peripheral::GPIO>(port, pin)),
    last_db_time_(0),
    last_stable_state_(false),
    current_state_(false) {}



}
