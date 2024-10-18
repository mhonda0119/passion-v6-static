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

    std::unique_ptr<parameter::Motion> IEH24096::get_val_ptr() {
        encoder_->spd = static_cast<float>(100);
        std::cout << "spd: " << static_cast<float>(encoder_->spd) << std::endl;
        std::cout << "pos" << encoder_->pos[0] << std::endl;
        return std::move(encoder_);
    }
}

