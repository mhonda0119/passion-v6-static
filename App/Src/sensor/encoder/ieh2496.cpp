#include "ieh24096.hpp"
#include <memory>
#include <iostream>


namespace sensor::encoder {

    IEH24096::IEH24096(TIM_HandleTypeDef* htim, uint32_t channel)
    :   timencoder_(std::make_unique<peripheral::TimEncoder>(htim, channel)),  // timencoder_を初期化
        encoder_(std::make_unique<parameter::Motion>()) ,
        htim_(htim){}


    void IEH24096::Init() {
        // 初期化の実装
    }

    void IEH24096::Start() {
        timencoder_->Start();
        // 開始の実装
    }

    void IEH24096::ReadVal() {
        timencoder_->ReadVal();
    }

    void IEH24096::Stop(){
        timencoder_ -> Stop();
    }

    parameter::Motion* IEH24096::get_val_ptr() {
        float cnt = static_cast<float>(timencoder_->get_val());
        encoder_->spd = cnt - static_cast<float>(timencoder_->period_/2);
        timencoder_->set_val(static_cast<float>(timencoder_->period_/2));
        encoder_->spd = (encoder_->spd/resolution_*timencoder_->edge_) * parameter::Hardware::DIST_ONE_ROT;
        return encoder_.get();
    }
}

