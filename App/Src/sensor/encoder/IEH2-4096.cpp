#include "ieh2-4096.hpp"

namespace encoder {
    IEH2_4096::IEH2_4096(TIM_HandleTypeDef* htim, uint32_t channel) {
        // エンコーダドライバのインスタンス化
    encoder_driver_ = std::make_unique<encoder::Driver>(htim, channel);
    }

    void IEH2_4096::Init() {
        // 初期化の実装
    }

    void IEH2_4096::Start() {
        encoder_driver_->Start();
        // 開始の実装
    }

    void IEH2_4096::ReadVal() {
    encoder_driver_->ReadVal();
    uint32_t current_count = encoder_driver_->get_val();
    encoder_->spd = speed; // スピードをMotionParameterに保存
    encoder_->dist = dist;//距離をMotionParameterに保存
    }

    MotionParameter* IEH2_4096::get_encoder_ptr() {
        return encoder_;
        // エンコーダのポインタを取得する実装
    }
}


