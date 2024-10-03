#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include "peripheral.h"
#include <memory>
#include <iostream>
#include <cstdint>

namespace peripheral{
    class Encoder{
    private:
        TIM_HandleTypeDef* htim_;  // タイマのハンドル
        uint32_t channel_;         // タイマのチャネル
        uint32_t count_ = 0; // エンコーダのカウント
    public:
        Encoder(TIM_HandleTypeDef* htim,uint32_t channel);
        void Start();
        void ReadVal();
        void Stop();
        uint32_t get_val();
        ~Encoder() = default;
    };
}

#endif //_ENCODER_HPP_

