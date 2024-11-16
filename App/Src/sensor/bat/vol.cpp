#include "vol.hpp"

namespace sensor::bat {

Vol::Vol(std::shared_ptr<peripheral::ADC> adc)
    : adc_(adc),vol_(0){}

void Vol::ReadVal() {
    adc_->ReadVal();
    vol_ = adc_->get_val_ptr()[5];
}

uint16_t Vol::get_val() {
    return vol_;
}

} // namespace sensor::elec