#include "drive.hpp"

namespace drive{
    Core::Core(std::unique_ptr<regulator::Motor>& motor_reg,std::unique_ptr<sensor::imu::Product>& imu,
    std::unique_ptr<sensor::encoder::Combine>& encoder,std::unique_ptr<md::Product>& md)
    : motor_reg_(motor_reg), imu_(imu), encoder_(encoder),md_(md), design_(std::make_unique<drive::Design>()){}

    //加減速走行
    void Core::AD(float dist,float spd_in, float spd_out){
        //回転角度をリセット
        imu_->ResetAngle();
        //距離をリセット
        encoder_->ResetDist();
        //加速度を取得
        design_->TrapeAccel(dist,spd_in,spd_out);
        //目標値を設定
        motor_reg_->r_->maccel[static_cast<int>(state::Motion::DIR::C)] = design_->get_accel();
        //走行開始
        md_->Start();
        //実際の距離が目標距離になるまで走行
        if(motor_reg_->r_->maccel[static_cast<int>(state::Motion::DIR::C)] >= 0){
            // std::cout << "Start AD" << std::endl;
            while(encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] < dist){
            // std::cout << "\tencoder dist : " << Objects::encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)];
            // std::cout << "\tencoder spd : " << Objects::encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;
            }

        }else if(motor_reg_->r_->maccel[static_cast<int>(state::Motion::DIR::C)] < 0){
            // std::cout << "Start AD Reverse" << std::endl;
            // std::cout << "\tencoder dist : " << Objects::encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] << std::endl;
            // std::cout << "\tr_spd :"<<motor_reg_->r_->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;
            while(encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] < dist
                && motor_reg_->r_->spd[static_cast<int>(state::Motion::DIR::C)] > 0){
            // std::cout << "\tr_spd : " <<motor_reg_->r_->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;
            // std::cout << "\tencoder dist : " << Objects::encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)];
            // std::cout << "\tencoder spd : " << Objects::encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;
                }
        }
        //終わりコメント
        // std::cout << "End AD" << std::endl;
        //目標値リセット//加速度
        motor_reg_->r_->maccel[static_cast<int>(state::Motion::DIR::C)] = 0;
        //目標値リセット//距離
        motor_reg_->r_->dist[static_cast<int>(state::Motion::DIR::C)] = 0;
        //PIDのリセット
        motor_reg_->Reset_PID();
        //走行距離をリセット
        encoder_->ResetDist();
        //回転角度をリセット
        imu_->ResetAngle();
    }
}