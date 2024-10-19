#include "ieh24096.hpp"
#include <memory>
#include <iostream>

namespace sensor::encoder {
    IEH24096::IEH24096(TIM_HandleTypeDef* htim, uint32_t channel)
    :   timencoder_(std::make_unique<peripheral::TimEncoder>(htim, channel)),  // timencoder_を初期化
        encoder_(std::make_unique<parameter::Motion>()) ,
        htim_(htim) {}


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
        encoder_->spd = cnt - 30000;
        timencoder_->set_val(30000);
        // 速度の換算 →[mm/s]
        // encoder_speed_r = (encoder_speed_r / 4096*4) * (13 / 42) * DIST_ONE_ROT *
        // 1000; encoder_speed_l = (encoder_speed_l / 4096*4) * (13 / 42) *
        // DIST_ONE_ROT * 1000;
        encoder_->spd = -(encoder_->spd *  0.018892 * 23.8F  * 3.1415);
        return encoder_.get();
    }
}

