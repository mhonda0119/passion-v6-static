#include "encoder.hpp"

namespace sensor::encoder{
    Product::Product()
    :   offset_(std::make_unique<state::Motion>()),
        val_(std::make_unique<state::Motion>()),
        sieve_(std::make_unique<filter::Sieve>()){}
    
    void Product::GetOffset(){
        //オフセットの実装
        this->ReadVal();
        std::unique_ptr<state::Motion>& raw = this->get_raw_ptr();
        offset_->spd[static_cast<int>(state::Motion::DIR::C)] = raw->spd[static_cast<size_t>(state::Motion::DIR::C)];
    }
    
    void Product::Update(){
        //更新の実装
        this->ReadVal();
        std::unique_ptr<state::Motion>& raw = this->get_raw_ptr();
        val_->spd[static_cast<int>(state::Motion::DIR::C)] = raw->spd[static_cast<int>(state::Motion::DIR::C)] - offset_->spd[static_cast<int>(state::Motion::DIR::C)];
        sieve_->Filter(parameter::software::SENSOR_FREQ,val_);
    }

    std::unique_ptr<state::Motion>& Product::get_val_ptr(){
        return val_;
    }
}