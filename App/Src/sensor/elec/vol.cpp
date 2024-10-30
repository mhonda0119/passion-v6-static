#include "vol.hpp"

namespace sensor::elec {

Vol::Vol(ADC_HandleTypeDef* hadc)
    : hadc_(hadc),
      adc_(std::make_unique<peripheral::Adc>(hadc_)){}
} // namespace sensor::elec

void Vol::Init() {
    
}

void Vol::ReadVal() {
    adc_->ReadVal();
    vol_ = adc_->get_val_ptr()[5];
}

void Vol::get_val() {
    return vol_;
}