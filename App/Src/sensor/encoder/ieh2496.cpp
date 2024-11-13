#include "ieh24096.hpp"
#include <memory>
#include <iostream>


namespace sensor::encoder {

    IEH24096::IEH24096(TIM_HandleTypeDef* htim, uint32_t channel)
    :   timencoder_(std::make_unique<peripheral::TimEncoder>(htim, channel)),  // timencoder_を初期化
        raw_(std::make_unique<state::Motion>()) ,
        htim_(htim){}


    void IEH24096::Init() {
        // 初期化の実装;
    }

    void IEH24096::Start() {
        timencoder_->Start();
        // 開始の実装
    }

    void IEH24096::ReadVal() {
        timencoder_->ReadVal();
        //パルスカウンタの増加量を速さとして取得
        //std::cout << "cnt:" << cnt << std::endl;
        raw_->spd[static_cast<int>(state::Motion::DIR::C)] = static_cast<float>(timencoder_->get_val()) - 30000;
        // raw_->spd[static_cast<int>(state::Motion::DIR::C)] = static_cast<float>(timencoder_->get_val());
        //カウンタの真ん中の値を基準にする
        timencoder_->set_val(30000);
        //timencoder_->set_val(static_cast<float>(timencoder_->period_/2));
        //速度の換算(mm/s)
        raw_->spd[static_cast<int>(state::Motion::DIR::C)] =  raw_->spd[static_cast<int>(state::Motion::DIR::C)] * 0.018892 *
        consts::hardware::DIST_ONE_ROT;
        // (consts::hardware::SUPER/consts::hardware::PINION) * 
        // consts::hardware::DIST_ONE_ROT * consts::software::SENSOR_FREQ) / (resolution_*4);
        // (raw_->spd[static_cast<int>(state::Motion::DIR::C)] /(resolution_*4)) * //timencoder_->edge_ = 4
        // (consts::hardware::PINION/consts::hardware::SUPER) *
        // consts::hardware::DIST_ONE_ROT * consts::software::SENSOR_FREQ;
        // std::cout << "edge_:" << timencoder_->edge_ << std::endl;
        //std::cout << "raw_spd::::::" << raw_->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;
    }

    void IEH24096::Stop(){
        timencoder_->Stop();
    }

    std::unique_ptr<state::Motion>& IEH24096::get_raw_ref() {
        return raw_;
    }
}