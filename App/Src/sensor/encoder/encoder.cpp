#include "encoder.hpp"

namespace sensor::encoder{
    Product::Product()
    :   offset_(std::make_unique<state::Motion>()),
        val_(std::make_unique<state::Motion>()),
        sieve_(std::make_unique<filter::Sieve>()){}
    
    void Product::GetOffset(){
        //オフセットの実装
        this->ReadVal();//なんでかわからんけど一発目の値がおかしい
        this->ReadVal();
        std::unique_ptr<state::Motion>& raw = this->get_raw_ref();
        offset_->spd[static_cast<int>(state::Motion::DIR::C)] = raw->spd[static_cast<size_t>(state::Motion::DIR::C)];
    }
    
    void Product::Update(){
        //更新の実装
        this->ReadVal();
        val_->spd[static_cast<int>(state::Motion::DIR::C)] = this->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::C)]
        - offset_->spd[static_cast<int>(state::Motion::DIR::C)];
        sieve_->Filter(consts::software::SENSOR_FREQ,val_);
    }

    std::unique_ptr<state::Motion>& Product::get_val_ref(){
        return val_;
    }
}