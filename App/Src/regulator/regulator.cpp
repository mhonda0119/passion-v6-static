#include "regulator.hpp"

namespace regulator{
    Motor::Motor(std::unique_ptr<sensor::Wall>& wall,std::unique_ptr<sensor::imu::Product>& imu,
    std::unique_ptr<sensor::encoder::Combine>& encoder)
    :
    wall_th_l_(consts::software::WALL_TH_L),
    wall_th_fl_(consts::software::WALL_TH_FL),
    wall_th_fr_(consts::software::WALL_TH_FR),
    wall_th_r_(consts::software::WALL_TH_R),
    wall_gap_th_l_(consts::software::WALL_GAP_TH),
    wall_gap_th_r_(consts::software::WALL_GAP_TH),
    u_r_(0.0),
    u_l_(0.0),
    wall_(wall),imu_(imu),encoder_(encoder),
    pid_dist_(std::make_unique<ctrl::PID>(consts::software::KP_DIST,consts::software::KI_DIST,consts::software::KD_DIST)),
    pid_spd_(std::make_unique<ctrl::PID>(consts::software::KP_SPD,consts::software::KI_SPD,consts::software::KD_SPD)),
    pid_omega_(std::make_unique<ctrl::PID>(consts::software::KP_OMEGA,consts::software::KI_OMEGA,consts::software::KD_OMEGA)),
    pid_angle_(std::make_unique<ctrl::PID>(consts::software::KP_ANGLE,consts::software::KI_ANGLE,consts::software::KD_ANGLE)),
    pid_wall_(std::make_unique<ctrl::PID>(consts::software::KP_WALL,consts::software::KI_WALL,consts::software::KD_WALL)),
    wall_gap_(std::make_unique<correction::WallGap>(consts::software::WALL_GAP_TH)),
    sieve_(std::make_unique<filter::Sieve>()),
    r_(std::make_unique<state::Motion>()){}

    void Motor::Reset_r(){
        r_->maccel[static_cast<int>(state::Motion::DIR::C)] = 0;
        r_->spd[static_cast<int>(state::Motion::DIR::C)] = 0;
        r_->dist[static_cast<int>(state::Motion::DIR::C)] = 0;
        r_->alpha[static_cast<int>(state::Motion::DIR::C)] = 0;
        r_->omega[static_cast<int>(state::Motion::DIR::C)] = 0;
        r_->angle[static_cast<int>(state::Motion::DIR::C)] = 0;
    }
    void Motor::Reset_PID(){
        pid_dist_->Reset();
        pid_spd_->Reset();
        pid_omega_->Reset();
        pid_angle_->Reset();
        pid_wall_->Reset();
    }

    void Motor::Regulate(){
        //指令値にfilterかけて目標値生成
        sieve_->C_2(consts::software::SENSOR_FREQ,r_);
        //PID制御(距離)//encoderの値を使う
        pid_dist_->Update(r_->dist[static_cast<int>(state::Motion::DIR::C)],
        encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)]);
        //PID制御(速度)//PID制御(距離)の出力を使う
        pid_spd_->Update(pid_dist_->get_u(),encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)]);
        //壁制御
        //左右の壁がある場合
        if(wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::L)] &&
        wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::R)]){
            pid_wall_->Update(
                (wall_->get_offset_ref()->dir[static_cast<int>(state::Wall::DIR::R)]-
                wall_->get_offset_ref()->dir[static_cast<int>(state::Wall::DIR::L)])/2,
                (wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::R)]-
                wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::L)])/2
            );
        }
        //左の壁がある場合
        else if(wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::L)]){
            pid_wall_->Update(
                wall_->get_offset_ref()->dir[static_cast<int>(state::Wall::DIR::L)],
                wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::L)]
            );
        }
        //右の壁がある場合
        else if(wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::R)]){
            pid_wall_->Update(
                wall_->get_offset_ref()->dir[static_cast<int>(state::Wall::DIR::R)],
                wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::R)]
            );
        }
        //両方の壁ない
        else{
            pid_wall_->Reset();
        }
        //PID制御(角速度)
        pid_omega_->Update(r_->omega[static_cast<int>(state::Motion::AXIS::Z)] + pid_wall_->get_u(),//壁制御の出力を使う
        imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)]);
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