#include "regulator.hpp"

namespace regulator{
    Motor::Motor()
        :wall_th_l_(consts::software::WALL_TH_L),
        wall_th_fl_(consts::software::WALL_TH_FL),
        wall_th_fr_(consts::software::WALL_TH_FR),
        wall_th_r_(consts::software::WALL_TH_R){
        //Objectsクラスのインスタンス化
        objects_ = std::make_unique<Objects>();
        //Motionクラスのインスタンス化
        motion_ = 
        std::make_unique<sensor::Motion>(objects_->encoder_l_, objects_->encoder_r_, objects_->imu_);
        //Wallクラスのインスタンス化
        wall_ = 
        std::make_unique<sensor::Wall>(objects_->pxstr_, objects_->osi3ca5111a_, objects_->wait_,objects_->led_);
        //制御器のインスタンス化
        pid_dist_ = std::make_unique<ctrl::PID>(consts::software::KP_DIST,consts::software::KI_DIST,consts::software::KD_DIST);
        pid_spd_ = std::make_unique<ctrl::PID>(consts::software::KP_SPD,consts::software::KI_SPD,consts::software::KD_SPD);
        pid_omega_ = std::make_unique<ctrl::PID>(consts::software::KP_OMEGA,consts::software::KI_OMEGA,consts::software::KD_OMEGA);
        pid_angle_ = std::make_unique<ctrl::PID>(consts::software::KP_ANGLE,consts::software::KI_ANGLE,consts::software::KD_ANGLE);
        pid_wall_ = std::make_unique<ctrl::PID>(consts::software::KP_WALL);
        //壁切れのインスタンス化
        wall_gap_r_ = std::make_unique<adjust::WallGap>(consts::software::WALL_GAP_TH);
        wall_gap_l_ = std::make_unique<adjust::WallGap>(consts::software::WALL_GAP_TH);
        //なにもしないフィルタ
        sieve_ = std::make_unique<filter::Sieve>();
        //指令値
        r_ = std::make_unique<state::Motion>();
        //操作量
        u_r_ = 0;
        u_l_ = 0;
        debug_ = std::make_unique<state::Motion>();
            
    }

    void Motor::Init(){
        motion_->Init();
        motion_->GetOffset();
        wall_->Init();
        wall_->GetOffset();
        // std::cout << "motion_spd:" << motion_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;
        // std::cout << "motion_dist:" << motion_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] << std::endl;
        // std::cout << "motion_angle:" << motion_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
        // std::cout << "motion_omega:" << motion_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
    }

    void Motor::Regulate(float r_maccel ,float r_alpha){ 
        //指令値はr_accelからspdに変換なのにfilterではspdからdistを出してるのでfilter使えなくて無理すぎる.
        //設定された加速度，角速度を代入
        r_->maccel[static_cast<int>(state::Motion::DIR::C)] = r_maccel;
        r_->alpha[static_cast<int>(state::Motion::AXIS::Z)] = r_alpha;
        //指令値にfilterかけて目標値生成
        sieve_->C_ff(consts::software::CTRL_FREQ,r_);
        //センサー値取得
        motion_->Update();
        wall_->ReadVal(wall_th_l_,wall_th_fl_,wall_th_fr_,wall_th_r_);
        //std::cout << "motion_spd" << motion_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;
        //std::cout << "motion_dist" << motion_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] << std::endl;
        //壁の状態取得
        //PID制御(距離)
        debug_->dist[static_cast<int>(state::Motion::DIR::C)] = motion_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)];
        debug_->spd[static_cast<int>(state::Motion::DIR::C)] = motion_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)];
        debug_->angle[static_cast<int>(state::Motion::AXIS::Z)] = motion_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)];
        debug_->omega[static_cast<int>(state::Motion::AXIS::Z)] = motion_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)];

        // std::cout << "debug_dist:" << debug_->dist[static_cast<int>(state::Motion::DIR::C)] << std::endl;
        // std::cout << "debug_spd:" << debug_->spd[static_cast<int>(state::Motion::DIR::C)] << std::endl;
        // std::cout << "debug_angle:" << debug_->angle[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
        // std::cout << "debug_omega:" << debug_->omega[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
        
        pid_dist_->Update(r_->dist[static_cast<int>(state::Motion::DIR::C)],
        motion_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)]);
        
        //PID制御(速さ)
        pid_spd_->Update(pid_dist_->get_u(),
        motion_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)]);
        //壁制御
        if(objects_->flag_->WALL_CTRL){
            //PIDの偏差
            pid_wall_->Reset();
            //壁切れ
            //壁センサー閾値の更新
            wall_gap_r_->Update(consts::software::WALL_TH_R,consts::software::WALL_GAP_TH,
            wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::R)]);
            wall_th_r_ = wall_gap_r_->get_wall_th();
            wall_gap_l_->Update(consts::software::WALL_TH_L,consts::software::WALL_GAP_TH,
            wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::L)]);
            wall_th_l_ = wall_gap_l_->get_wall_th();
            //壁の判定
            if(wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::L)] &&
            wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::R)]){
                //左右壁がある場合
                //wall_errorは機体の中心位置からのズレ(右にズレると正で，左にずれると負)
                pid_wall_->Update(
                    (wall_->get_offset_ref()->dir[static_cast<int>(state::Wall::DIR::R)]-
                    wall_->get_offset_ref()->dir[static_cast<int>(state::Wall::DIR::L)])/2,
                    (wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::R)]-
                    wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::L)])/2
                );
            }else if(wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::L)]){
                //左壁のみの場合
                //wall_error = ad_l -base_l
                pid_wall_->Update(
                    wall_->get_offset_ref()->dir[static_cast<int>(state::Wall::DIR::L)],
                    wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::L)]
                );
            }else if(wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::R)]){
                //右壁のみの場合
                //wall_error = ad_r -base_r
                pid_wall_->Update(
                    wall_->get_offset_ref()->dir[static_cast<int>(state::Wall::DIR::R)],
                    wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::R)]
                );
            }else{
                //左右の壁が両方ない場合
                //wall_errorは0
            }
            //操作量の計算

        }
        //PID制御(角度)
        // pid_angle_->Update(r_->angle[static_cast<int>(state::Motion::AXIS::Z)],
        // motion_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)]);
        //PID制御(角速度)
        pid_omega_->Update(r_->omega[static_cast<int>(state::Motion::AXIS::Z)] + pid_wall_->get_u(), //なぜか壁制御の値を足す
        motion_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)]);
        //操作量の計算
        u_r_ = pid_spd_->get_u() + pid_omega_->get_u();
        u_l_ = pid_spd_->get_u() - pid_omega_->get_u();
        
    }
    float Motor::get_u_l(){
        return u_l_;
    }
    float Motor::get_u_r(){
        return u_r_;
    }
    
}