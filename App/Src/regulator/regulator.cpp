#include "regulator.hpp"

namespace regulator{
    Motor::Motor(std::unique_ptr<sensor::Wall>& wall,std::unique_ptr<sensor::imu::Product>& imu,
    std::unique_ptr<sensor::encoder::Combine>& encoder,std::unique_ptr<ctrl::AccelDesigner>& design,
    std::unique_ptr<ctrl::slalom::Trajectory>& traj_l90,std::unique_ptr<ctrl::slalom::Trajectory>& traj_r90,
    std::unique_ptr<indicator::Buzzer>& buzzer)
    :
    wall_th_l_(consts::software::WALL_TH_L),
    wall_th_fl_(consts::software::WALL_TH_FL),
    wall_th_fr_(consts::software::WALL_TH_FR),
    wall_th_r_(consts::software::WALL_TH_R),
    wall_gap_th_l_(consts::software::WALL_GAP_TH),
    wall_gap_th_r_(consts::software::WALL_GAP_TH),
    u_r_(0.0),
    u_l_(0.0),
    wall_(wall),imu_(imu),encoder_(encoder),design_(design),traj_l90_(traj_l90),traj_r90_(traj_r90),buzzer_(buzzer),
    pid_dist_(std::make_unique<ctrl::PID>(consts::software::KP_DIST,consts::software::KI_DIST,consts::software::KD_DIST)),
    pid_spd_(std::make_unique<ctrl::PID>(consts::software::KP_SPD,consts::software::KI_SPD,consts::software::KD_SPD)),
    pid_omega_(std::make_unique<ctrl::PID>(consts::software::KP_OMEGA,consts::software::KI_OMEGA,consts::software::KD_OMEGA)),
    pid_angle_(std::make_unique<ctrl::PID>(consts::software::KP_ANGLE,consts::software::KI_ANGLE,consts::software::KD_ANGLE)),
    pid_wall_(std::make_unique<ctrl::PID>(consts::software::KP_WALL,consts::software::KI_WALL,consts::software::KD_WALL)),
    pid_stop_(std::make_unique<ctrl::PID>(0.45,0.08,0)),
    wall_gap_(std::make_unique<correction::WallGap>(consts::software::WALL_GAP_TH)),
    sieve_(std::make_unique<filter::Sieve>()),
    r_(std::make_unique<state::Motion>()){}

    void Motor::Reset_PID(){
        pid_dist_->Reset();
        pid_spd_->Reset();
        pid_omega_->Reset();
        pid_angle_->Reset();
        pid_wall_->Reset();
        pid_stop_->Reset();
    }
    
    void Motor::StopRegulate(){
        //目標値
        if(Flag::Check(DRIVE_START)){
        pid_stop_->Update(r_->spd[static_cast<int>(state::Motion::DIR::C)],
        encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)]);
        //操作量の計算
        u_r_ = pid_stop_->get_u();
        u_l_ = pid_stop_->get_u();
        }
    }

    void Motor::Regulate(){
        if(Flag::Check(DRIVE_START)){
        //指令値にfilterかけて目標値生成
        sieve_->C_2(consts::software::SENSOR_FREQ,r_);
        //現在の値を取得して差分をとる
        //PID制御(距離)//encoderの値を使う
        if(Flag::Check(DRIVE_SPIN)){
            r_->dist[static_cast<int>(state::Motion::DIR::C)] = 0;
        }
        //PID制御(距離)
        pid_dist_->Update(r_->dist[static_cast<int>(state::Motion::DIR::C)],
        encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)]);
        //PID制御(速度)//PID制御(距離)の出力を使う
        //pid_spd_->Update(pid_dist_->get_u(),encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)]);
        //壁制御
        if(Flag::Check(WALL_CTRL)){
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
        }
        //PID制御(角速度)
        pid_omega_->Update(r_->omega[static_cast<int>(state::Motion::AXIS::Z)] + pid_wall_->get_u(),//壁制御の出力を使う
        imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)]);
        //操作量の計算
        //PID制御(距離)の出力と壁制御の出力の和を操作量とする．
        u_r_ = pid_dist_->get_u() + pid_omega_->get_u();
        u_l_ = pid_dist_->get_u() - pid_omega_->get_u();

        }
    }

    void Motor::DesignRegulate(){
        //0.走行開始フラグの確認
        if(Flag::Check(DRIVE_START)){
        //1.現在の時刻の目標距離を取得
        r_->dist[static_cast<int>(state::Motion::DIR::C)] = design_->x(t_cnt_);
        // //現在の時刻を表示
        // std::cout << "\tt_cnt_ : " << t_cnt_;
        // //目標距離を表示
        // std::cout << "\ttarget dist: " << design_->x(t_cnt_) << std::endl;
        // std::cout << "\tencoder dist : " << encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] << std::endl;
        //距離pidにかける
        pid_dist_->Update(r_->dist[static_cast<int>(state::Motion::DIR::C)],
        encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)]);
        //壁制御
        //左右の壁がある場合
        if(Flag::Check(WALL_CTRL)){
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
                   -wall_->get_offset_ref()->dir[static_cast<int>(state::Wall::DIR::L)],
                    -wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::L)]
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
        }
        //角速度pidかける
        pid_omega_->Update(r_->omega[static_cast<int>(state::Motion::AXIS::Z)] - pid_wall_->get_u(),
        imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)]);
        //pidの出力保存
        u_l_ = pid_dist_->get_u() - pid_omega_->get_u();
        u_r_ = pid_dist_->get_u() + pid_omega_->get_u();
        // u_l_ = pid_dist_->get_u();
        // u_r_ = pid_dist_->get_u();
        //距離が目標値になったら，目標値をリセット,時刻カウンタをリセット,
        //encoder,imuの積算値をリセット,走行開始フラグをリセット
                if(encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)]
                >= (design_->x(design_->t_end())))
                
                {
                    std::cout << "end" << std::endl;
                    //buzzer_->Start(800);
                    
                    r_->dist[static_cast<int>(state::Motion::DIR::C)] = 0;
                    pid_omega_->Reset();
                    pid_dist_->Reset();
                    t_cnt_ = 0;
                    encoder_->ResetDist();
                    imu_->ResetAngle();
                    pid_omega_->set_kp(consts::software::KP_OMEGA);
                    pid_omega_->set_ki(consts::software::KI_OMEGA);
                    Flag::Reset(DRIVE_START);
                    Flag::Reset(DRIVE_STRAIGHT);
                    Flag::Reset(WALL_CTRL);

                    //Flag::Reset(WALL_CTRL);
                }else{t_cnt_ += 1/consts::software::CTRL_FREQ;}
        }
        
    }

    void Motor::TrajL90Regulate(){
        //0.走行開始フラグの確認
        if(Flag::Check(DRIVE_START)){
        //1.現在の時刻の目標状態を取得
        traj_l90_->update(s_,t_cnt_,1/consts::software::CTRL_FREQ);
        //現在の目標値を代入(角速度)
        r_->omega[static_cast<int>(state::Motion::AXIS::Z)] = consts::physics::RAD2DEG*s_.dq.th;
        //現在の目標値を代入(速度)
        r_->spd[static_cast<int>(state::Motion::DIR::C)] = traj_l90_->getVelocity();
        // //角速度PIDにかける
        pid_omega_->set_kp(0.3);
        pid_omega_->set_ki(0.08);
        pid_omega_->Update(r_->omega[static_cast<int>(state::Motion::AXIS::Z)],
        imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)]);
        //速度PIDにかける
        pid_spd_->Update(r_->spd[static_cast<int>(state::Motion::DIR::C)],
        encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)]);
        //操作量の計算
        u_r_ = pid_spd_->get_u() + pid_omega_->get_u();
        u_l_ = pid_spd_->get_u() - pid_omega_->get_u();
        //角度が目標値になったら
        if(t_cnt_ >= traj_l90_->getTimeCurve()){
            std::cout << "end_slalom" << std::endl;
            //タイマーリセット
            t_cnt_ = 0;
            //目標値リセット
            r_->omega[static_cast<int>(state::Motion::AXIS::Z)] = 0;
            r_->spd[static_cast<int>(state::Motion::DIR::C)] = 0;
            //PIDリセット
            pid_omega_->Reset();
            pid_spd_->Reset();
            pid_omega_->set_kp(consts::software::KP_OMEGA);
            pid_omega_->set_ki(consts::software::KI_OMEGA);
            //走行距離リセット
            encoder_->ResetDist();
            //角度リセット
            imu_->ResetAngle();
            //フラグ折る
            Flag::Reset(DRIVE_START);
            Flag::Reset(DRIVE_SLALOM_L90);
            //duty比リセット
            // u_l_ = 0;
            // u_r_ = 0;
 
        }else{t_cnt_ += 1/consts::software::CTRL_FREQ;}

        }
    }

    void Motor::TrajR90Regulate(){
        //0.走行開始フラグの確認
        if(Flag::Check(DRIVE_START)){
        //1.現在の時刻の目標状態を取得
        traj_r90_->update(s_,t_cnt_,1/consts::software::CTRL_FREQ);
        //現在の目標値を代入(角速度)
        r_->omega[static_cast<int>(state::Motion::AXIS::Z)] = consts::physics::RAD2DEG*s_.dq.th;
        //現在の目標値を代入(速度)
        r_->spd[static_cast<int>(state::Motion::DIR::C)] = traj_r90_->getVelocity();
        //角速度PIDにかける
        // pid_omega_->set_kp(0.6);
        // pid_omega_->set_ki(0.2);
        pid_omega_->set_kp(0.3);
        pid_omega_->set_ki(0.08);

        pid_omega_->Update(r_->omega[static_cast<int>(state::Motion::AXIS::Z)],
        imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)]);
        //速度PIDにかける
        pid_spd_->Update(r_->spd[static_cast<int>(state::Motion::DIR::C)],
        encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)]);
        //操作量の計算
        u_l_ = pid_spd_->get_u() - pid_omega_->get_u();
        u_r_ = pid_spd_->get_u() + pid_omega_->get_u();
        //角度が目標値になったら
        // if(imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] <= s_.q.th*consts::physics::RAD2DEG
        // || t_cnt_ >= traj_r90_->getTimeCurve())
        if(t_cnt_ >= traj_r90_->getTimeCurve()){
            std::cout << "end_slalom" << std::endl;
            //タイマーリセット
            t_cnt_ = 0;
            //目標値リセット
            r_->omega[static_cast<int>(state::Motion::AXIS::Z)] = 0;
            r_->spd[static_cast<int>(state::Motion::DIR::C)] = 0;
            //PIDリセット
            pid_omega_->Reset();
            pid_spd_->Reset();
            pid_omega_->set_kp(consts::software::KP_OMEGA);
            pid_omega_->set_ki(consts::software::KI_OMEGA);
            //走行距離リセット
            encoder_->ResetDist();
            //角度リセット
            imu_->ResetAngle();
            //フラグ折る
            Flag::Reset(DRIVE_START);
            Flag::Reset(DRIVE_SLALOM_R90);
            //duty比リセット
            // u_l_ = 0;
            // u_r_ = 0;
 
        }else{t_cnt_ += 1/consts::software::CTRL_FREQ;}

        }
    }

    void Motor::SpinRegulate(){
         //0.走行開始フラグの確認
        if(Flag::Check(DRIVE_START)){
        //1.現在の時刻の目標角度を取得
        r_->omega[static_cast<int>(state::Motion::AXIS::Z)] = design_->v(t_cnt_);
        //角速度pidにかける
        pid_omega_->set_kp(0.3);
        pid_omega_->set_ki(0.08);
        pid_omega_->Update(r_->omega[static_cast<int>(state::Motion::AXIS::Z)],
        imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)]);
        //距離pidにかける
        pid_dist_->Update(r_->dist[static_cast<int>(state::Motion::DIR::C)],
        encoder_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)]);
        //pidの出力保存
        u_l_ = pid_dist_->get_u() -(+ pid_omega_->get_u());
        u_r_ = pid_dist_->get_u() -(-pid_omega_->get_u());
        // u_l_ = pid_dist_->get_u();
        // u_r_ = pid_dist_->get_u();
        // u_l_ = + pid_omega_->get_u();
        // u_r_ = - pid_omega_->get_u();
        //距離が目標値になったら，目標値をリセット,時刻カウンタをリセット,
        //encoder,imuの積算値をリセット,走行開始フラグをリセット
            if(imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] 
            >= 178.0f
            /*||t_cnt_ >= design_->t_end()*/
            ){  
                std::cout << "end" << std::endl;
                pid_omega_->set_kp(consts::software::KP_OMEGA);
                pid_omega_->set_ki(consts::software::KI_OMEGA);
                r_->dist[static_cast<int>(state::Motion::DIR::C)] = 0;
                r_->angle[static_cast<int>(state::Motion::AXIS::Z)] = 0;
                r_->omega[static_cast<int>(state::Motion::AXIS::Z)] = 0;
                pid_dist_->Reset();
                pid_omega_->Reset();
                t_cnt_ = 0;
                encoder_->ResetDist();
                imu_->ResetAngle();
                this->set_u_l(0);
                this->set_u_r(0);
                Flag::Reset(DRIVE_START);
                Flag::Reset(DRIVE_SPIN);
                //Flag::Reset(WALL_CTRL);
            }else{t_cnt_ += 1/consts::software::CTRL_FREQ;}
        }
    }

    float Motor::get_u_l(){
        return u_l_;
    }
    float Motor::get_u_r(){
        return u_r_;
    }

    void Motor::set_u_l(float u_l){
        u_l_ = u_l;
    }
    void Motor::set_u_r(float u_r){
        u_r_ = u_r;
    }
}