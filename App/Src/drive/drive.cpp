#include "drive.hpp"

namespace drive{
    Core::Core(std::unique_ptr<regulator::Motor>& motor_reg,std::unique_ptr<sensor::imu::Product>& imu,
    std::unique_ptr<sensor::encoder::Combine>& encoder,std::unique_ptr<md::Product>& md)
    : motor_reg_(motor_reg), imu_(imu), encoder_(encoder),md_(md), design_(std::make_unique<drive::Design>()){}

    void Core::AD(float dist,float spd_in, float spd_out){
        //加速度を取得
        design_->TrapeAccel(dist,spd_in,spd_out);
        //目標値を設定
        motor_reg_->r_->maccel[static_cast<int>(state::Motion::DIR::C)] = design_->get_accel();
        //回転角度をリセット
        imu_->Reset();
        //エンコーダの値をリセット(距離と速さ)
        encoder_->Reset();
        //走行開始
        md_->Start();
        //実際の距離が目標距離になるまで走行
        if(motor_reg_->r_->maccel[static_cast<int>(state::Motion::DIR::C)] >= 0){
            while(encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] < dist){}
        }else if(motor_reg_->r_->maccel[static_cast<int>(state::Motion::DIR::C)] < 0){
            while(encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] < dist
                && motor_reg_->r_->spd[static_cast<int>(state::Motion::DIR::C)] > 0){}
        }
        //regulator内の変数をリセット
        motor_reg_->r_->maccel[static_cast<int>(state::Motion::DIR::C)] = 0;
        motor_reg_->r_->spd[static_cast<int>(state::Motion::DIR::C)] = 0;
        motor_reg_->r_->dist[static_cast<int>(state::Motion::DIR::C)] = 0;
        motor_reg_->r_->alpha[static_cast<int>(state::Motion::DIR::C)] = 0;
        motor_reg_->r_->omega[static_cast<int>(state::Motion::DIR::C)] = 0;
        motor_reg_->r_->angle[static_cast<int>(state::Motion::DIR::C)] = 0;
        //PIDのリセット
        motor_reg_->PIDReset();
        //走行距離カウンタをリセット
        encoder_->Reset();
    }
}