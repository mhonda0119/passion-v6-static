#include "ieh24096.hpp"
#include <memory>
#include <iostream>


namespace sensor::encoder {

    IEH24096::IEH24096(TIM_HandleTypeDef* htim, uint32_t channel)
    :   timencoder_(std::make_unique<peripheral::TimEncoder>(htim, channel)),  // timencoder_を初期化
        raw_(std::make_unique<state::Motion>()) ,
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

    std::unique_ptr<state::Motion>& IEH24096::get_raw_ptr() {
        float cnt = static_cast< float>(timencoder_->get_val());
        raw_->spd[static_cast<int>(state::Motion::DIR::C)] = cnt - static_cast< float>(timencoder_->period_/2);
        timencoder_->set_val(static_cast< float>(timencoder_->period_/2));
        raw_->spd[static_cast<int>(state::Motion::DIR::C)] = (raw_->spd[static_cast<int>(state::Motion::DIR::C)]/resolution_*timencoder_->edge_) * parameter::hardware::DIST_ONE_ROT;
        return raw_;
    }
}