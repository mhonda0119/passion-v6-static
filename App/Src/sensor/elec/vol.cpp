#include "vol.hpp"

namespace sensor::elec {

Vol::Vol(ADC_HandleTypeDef* hadc)
    : hadc_(hadc),
      adc_(std::make_unique<peripheral::Adc>(hadc_)){}

void Vol::Init() {
    
}

void Vol::ReadVal() {
    adc_->ReadVal();
    vol_ = adc_->get_val_ptr()[5];
}

uint16_t Vol::get_val() {
    return vol_;
}

} // namespace sensor::elec