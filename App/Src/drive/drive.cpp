#include "drive.hpp"

namespace drive{
    Core::Core(std::unique_ptr<regulator::Motor>& motor_reg,std::unique_ptr<sensor::imu::Product>& imu,
    std::unique_ptr<sensor::encoder::Combine>& encoder,std::unique_ptr<md::Product>& md,std::unique_ptr<ctrl::Design>& design,
    std::unique_ptr<ctrl::slalom::Trajectory>& traj_l90,
    std::unique_ptr<ctrl::slalom::Trajectory>& traj_r90,
    std::unique_ptr<sensor::Wall>& wall)
    : motor_reg_(motor_reg), imu_(imu), encoder_(encoder),md_(md), design_(design),traj_l90_(traj_l90),traj_r90_(traj_r90),wall_(wall){}

    //加減速走行
    void Core::AD(float dist,float spd_in, float spd_out){
        //回転角度をリセット
        imu_->ResetAngle();
        //回転角速度をリセット
        imu_->ResetOmega();
        //距離をリセット
        encoder_->ResetDist();
        //加速度を取得
        design_->TrapeAccel(dist,spd_in,spd_out);
        //目標値を設定
        motor_reg_->r_->maccel[static_cast<int>(state::Motion::DIR::C)] = design_->get_accel();
        //走行開始flag立てる
        Flag::Set(DRIVE_START);
        //壁制御ON
        Flag::Set(WALL_CTRL);
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
        //回転角速度をリセット
        imu_->ResetOmega();
        //フラグ折る
        Flag::Reset(DRIVE_START);
        Flag::Reset(WALL_CTRL);
        //duty比リセット 
        md_->Duty(0,0);
        motor_reg_->set_u_l(0);
        motor_reg_->set_u_r(0);

    }
    //曲線加速走行
    void Core::CurveAD(float dist , float spd_in , float spd_out){
        //回転角度をリセット
        imu_->ResetAngle();
        //距離をリセット
        encoder_->ResetDist();
        //時刻カウンタをリセット
        motor_reg_->t_cnt_ = 0.0f;
        //走行開始
        md_->Start();
        //角速度の目標値を0に
        motor_reg_->r_->omega[static_cast<int>(state::Motion::AXIS::Z)] = 0;
        //目標値を設定
        design_->CurveAccel(dist-consts::software::AD_OFFSET,spd_in,spd_out);
        // std::cout << "v:::::" << Objects::accel_designer_->v(0.1) << std::endl;
        // std::cout << "x:::::" << Objects::accel_designer_->x(0.5) << std::endl;
        //走行開始flag立てる
        Flag::Set(DRIVE_START);
        //まっすぐフラグを立てる
        Flag::Set(DRIVE_STRAIGHT);
        //壁制御ON
        Flag::Set(WALL_CTRL);
    }
    //超信地旋回
    void Core::SpinTurn(){
         //回転角度をリセット
        imu_->ResetAngle();
        //距離をリセット
        encoder_->ResetDist();
        //時刻カウンタをリセット
        motor_reg_->t_cnt_ = 0.0f;
        //走行開始
        md_->Start();
        //位置の目標を0に設定
        motor_reg_->r_->dist[static_cast<int>(state::Motion::DIR::C)] = 0;
        //目標値を設定
        Objects::accel_designer_->reset(consts::software::SPIN_JERK_MAX,
        consts::software::SPIN_ALPHA_MAX,
        consts::software::SPIN_OMEGA_MAX,0,0,200);
        //走行開始flag立てる
        Flag::Set(DRIVE_START);
        //SPINフラグを立てる
        Flag::Set(DRIVE_SPIN);
    }
    //スラローム走行
    void Core::Slalom_L90(float v){
        imu_->ResetAngle();
        //距離をリセット
        encoder_->ResetDist();
        //時刻カウンタをリセット
        motor_reg_->t_cnt_ = 0.0f;
        //走行開始
        md_->Start();
        //スラロームの軌道を生成
        traj_l90_->reset(v,0,traj_l90_->getShape().straight_prev/v);
        //走行開始フラグ立てる
        Flag::Set(DRIVE_START);
        //slalomフラグを立てる
        Flag::Set(DRIVE_SLALOM_L90);
    }
    
    void Core::Slalom_R90(float v){
        imu_->ResetAngle();
        //距離をリセット
        encoder_->ResetDist();
        //時刻カウンタをリセット
        motor_reg_->t_cnt_ = 0.0f;
        //走行開始
        md_->Start();
        //スラロームの軌道を生成
        traj_r90_->reset(v,0,traj_r90_->getShape().straight_prev/v);
        //走行開始フラグ立てる
        Flag::Set(DRIVE_START);
        //slalomフラグを立てる
        Flag::Set(DRIVE_SLALOM_R90);
    }

    void Core::Stop(){
        std::cout << "STOP" << std::endl;
        //回転角度をリセット
        imu_->ResetAngle();
        //距離をリセット
        encoder_->ResetDist();
        //走行開始
        md_->Start();
        //目標値をつっこむ
        motor_reg_->r_->spd[static_cast<int>(state::Motion::DIR::C)] = 0;
        //走行開始フラグ立てる
        Flag::Set(DRIVE_START);
        //STOPフラグを立てる
        Flag::Set(DRIVE_STOP);
        // 0.1秒待つ
        Objects::wait_->Ms(100);
        //それでも止まっていなかったら強制停止
        if(encoder_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)] != 0){
            md_->ShortBrake();
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
        //回転角速度をリセット
        imu_->ResetOmega();
        //指令値リセット
        motor_reg_->set_u_l(0);
        motor_reg_->set_u_r(0);
        //フラグ折る
        Flag::Reset(DRIVE_STOP);
        Flag::Reset(DRIVE_START);
        }
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
        //回転角速度をリセット
        imu_->ResetOmega();
        //指令値リセット
        motor_reg_->set_u_l(0);
        motor_reg_->set_u_r(0);
        //フラグ折る
        Flag::Reset(DRIVE_STOP);
        Flag::Reset(DRIVE_START);
    }

    void Core::Ketsu(){
        std::cout << "KETSU" << std::endl;
        //回転角度をリセット
        imu_->ResetAngle();
        //距離をリセット
        encoder_->ResetDist();
        //Dutyセット
        motor_reg_->set_u_l(-5);
        motor_reg_->set_u_r(-5);
        std::cout << "md->duty" << std::endl;
        //走行開始
        md_->Start();
        //wait
        Objects::wait_->Ms(1000);
        //停止
        md_->ShortBrake();
        Objects::md_->Dir(state::MOTOR::LEFT,state::MOTOR::FWD);
        Objects::md_->Dir(state::MOTOR::RIGHT,state::MOTOR::FWD);
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
        //回転角速度をリセット
        imu_->ResetOmega();
        //指令値リセット
        motor_reg_->set_u_l(0);
        motor_reg_->set_u_r(0);
        
    }

    void Core::Straight(float dist,float v_in,float v_out){
        this->CurveAD(dist,v_in,v_out);
        while(Flag::Check(DRIVE_START)){}
    }

    void Core::TurnL90(float v,float prev_d,float after_d){
        if(prev_d <= consts::software::AD_OFFSET|| after_d <= consts::software::AD_OFFSET){
        this->Slalom_L90(v);
        while(Flag::Check(DRIVE_START)){}
        }else{
            if(Flag::Check(FWALL_CTRL)&&
            wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::F)]){
                while(
                wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FL)]+
                wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FR)] < 
                consts::software::FWALL_TH){
                this->Straight(prev_d,v,v);
                break;
                }
                this->Slalom_L90(v);
                while(Flag::Check(DRIVE_START)){}
                this->Straight(after_d,v,v);
            }else{
                this->Straight(prev_d,v,v);
                this->Slalom_L90(v);
                while(Flag::Check(DRIVE_START)){}
                this->Straight(after_d,v,v);
            }
        }

    }

    void Core::TurnR90(float v,float prev_d,float after_d){
        if(prev_d <= consts::software::AD_OFFSET|| after_d <= consts::software::AD_OFFSET){
        this->Slalom_R90(v);
        while(Flag::Check(DRIVE_START)){}
        }else{
            if(Flag::Check(FWALL_CTRL)&&
            wall_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::F)]){
                while(
                wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FL)]+
                wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FR)] < 
                consts::software::FWALL_TH){
                this->Straight(prev_d,v,v);
                break;
                }
                this->Slalom_R90(v);
                while(Flag::Check(DRIVE_START)){}
                this->Straight(after_d,v,v);
            }else{
                this->Straight(prev_d,v,v);
                this->Slalom_R90(v);
                while(Flag::Check(DRIVE_START)){}
                this->Straight(after_d,v,v);
            }
        }
    }

}