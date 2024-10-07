#include "ieh24096.hpp"

namespace sensor::encoder {
    IEH24096::IEH24096(TIM_HandleTypeDef* htim, uint32_t channel) {
        // エンコーダドライバのインスタンス化
        encoder_ = std::make_unique<peripheral::TimEncoder>(htim, channel);
    }

    void IEH24096::Init() {
        // 初期化の実装
    }

    void IEH24096::Start() {
        encoder_->Start();
        // 開始の実装
    }

    void IEH24096::ReadVal() {
    encoder_->ReadVal();
    uint32_t current_count = count_->get_val();
    encoder_->spd = speed; // スピードをMotionParameterに保存
    encoder_->dist = dist;//距離をMotionParameterに保存
    }

    parameter::Motion* IEH24096::get_val_ptr() {
        return encoder_;
        // エンコーダのポインタを取得する実装
    }
}


