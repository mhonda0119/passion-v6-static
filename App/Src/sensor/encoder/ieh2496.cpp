#include "ieh24096.hpp"
#include <memory>
#include <iostream>

namespace sensor::encoder {
    IEH24096::IEH24096(TIM_HandleTypeDef* htim, uint32_t channel)
        :cnt_(std::make_unique<peripheral::TimEncoder>(htim, channel)) ,
        htim_(htim){}


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

    void IEH24096::Stop(){
        cnt_ -> Stop();
    }

    parameter::Motion* IEH24096::get_val_ptr() {
        //std::cout << "2-1" << std::endl;
        //encoder_->spd = static_cast<float>(cnt_->get_val()); 
        //get_val()を呼び出して値を取得し、floatにキャスト
        //std::cout << "2-2" << std::endl;
        float cnt =  static_cast<float>(cnt_->get_val());
        float speed = cnt - 30000;
        //マイナス速度用にパルスカウントを30000にセット
        cnt_->set_val(30000);
        //右の速度の符号を補正
        if(htim_ == &htim8){
            speed = -speed;
        }
        //速度の換算[mm/s]
        speed = speed * 0.018892 * D_TIRE * 3.1415;
        //走行距離カウンタを加算
        distance += 
        // エンコーダのポインタを取得する実装
    }
}

