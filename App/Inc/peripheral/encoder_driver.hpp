#ifndef _ENCODER_DRIVER_HPP_
#define _ENCODER_DRIVER_HPP_

#include "peripheral.h"
#include <memory>
#include <iostream>
#include <cstdint>

namespace peripheral::encoder{
    class Driver{
    private:
        TIM_HandleTypeDef* htim_;  // タイマのハンドル
        uint32_t channel_;         // タイマのチャネル
        uint32_t count_ = 0; // エンコーダのカウント
    public:
        Driver(TIM_HandleTypeDef* htim,uint32_t channel);
        void Start();
        void ReadVal();
        void Stop();
        uint32_t get_val();
        ~Driver() = default;
    };
}

#endif //_ENCODER_DRIVER_HPP_

