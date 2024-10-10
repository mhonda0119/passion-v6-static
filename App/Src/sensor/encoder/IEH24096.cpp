#include "ieh24096.hpp"
#include <memory>

namespace sensor::encoder {
    IEH24096::IEH24096(TIM_HandleTypeDef* htim, uint32_t channel)
        :cnt_(std::make_unique<peripheral::TimEncoder>(htim, channel)) {}


    void IEH24096::Init() {
        // 初期化の実装
    }

    void IEH24096::Start() {
        cnt_->Start();
        // 開始の実装
    }

    void IEH24096::ReadVal() {
        cnt_->ReadVal();
    }

    parameter::Motion* IEH24096::get_val_ptr() {
        return encoder_;
        // エンコーダのポインタを取得する実装
    }
}

