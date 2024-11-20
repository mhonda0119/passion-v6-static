#include "drive.hpp"

namespace drive{
    Core::Core(std::unique_ptr<regulator::Motor>& motor_reg,std::unique_ptr<sensor::imu::Product>& imu,
    std::unique_ptr<sensor::encoder::Combine>& encoder,std::unique_ptr<md::Product>& md,std::unique_ptr<ctrl::Design>& design)
    : motor_reg_(motor_reg), imu_(imu), encoder_(encoder),md_(md), design_(design){}

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
        //目標値を設定
        design_->CurveAccel(dist,spd_in,spd_out);
        //走行開始flag立てる
        Flag::Set(DRIVE_START);
        //壁制御ON
        Flag::Set(WALL_CTRL);
    }
    //超信地旋回
    void Core::SpinTurn(float angle,float omega_in,float omega_out){

        // std::cout << "\tr_accel:"<<motor_reg_->r_->maccel[static_cast<int>(state::Motion::AXIS::Z)];
        // std::cout << "\timu_accel : " << imu_->get_val_ref()->accel[static_cast<int>(state::Motion::AXIS::Z)];
        // std::cout << "\tr_spd : " << Objects::motor_reg_->r_->spd[static_cast<int>(state::Motion::AXIS::Z)];
        // std::cout << "\timu_spd : " << imu_->get_val_ref()->spd[static_cast<int>(state::Motion::AXIS::Z)];
        // std::cout << "\tr_omega : " << Objects::motor_reg_->r_->omega[static_cast<int>(state::Motion::AXIS::Z)];
        // std::cout << "\timu_omega : " << imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)];
        // std::cout << "\tr_angle : " << Objects::motor_reg_->r_->angle[static_cast<int>(state::Motion::AXIS::Z)];
        // std::cout << "\timu_angle : " << imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;

        //回転角度をリセット
        imu_->ResetAngle();
        // //回転角速度をリセット
        // imu_->ResetOmega();
        //距離をリセット
        encoder_->ResetDist();
        //角加速度を取得
        design_->TrapeAccel(angle,omega_in,omega_out);
        //目標値を設定
        motor_reg_->r_->alpha[static_cast<int>(state::Motion::AXIS::Z)] = design_->get_accel();
        //走行開始フラグ
        Flag::Set(DRIVE_START);
        //壁制御OFF
        Flag::Reset(WALL_CTRL);
        //SPINフラグ
        Flag::Set(DRIVE_SPIN);
        //走行開始
        md_->Start();
         //実際の角度が目標角度になるまで走行
        if(angle>= 0){
            // std::cout << "CCW" << std::endl;
            //     std::cout << "\tangle : " << angle;
            //     std::cout << "\tr_omega : " << Objects::motor_reg_->r_->omega[static_cast<int>(state::Motion::AXIS::Z)];
            //     std::cout << "\timu_omega : " << imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)];
            //     std::cout << "\tr_angle : " << Objects::motor_reg_->r_->angle[static_cast<int>(state::Motion::AXIS::Z)];
            //     std::cout << "\timu_angle : " << imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;

            while(imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] < angle &&
            Objects::motor_reg_->r_->omega[static_cast<int>(state::Motion::AXIS::Z)] > 0){
                //ccw->cwのとき，
                //omegaにリセットをかけてないのでomegaがまだ目標値に達してないのに,angleが目標値に達した場合，omegaがでかいまま減加速度．
                //運動に移ることがあり，そうなると，omegaが下がりきらずに,CWの条件をすり抜けることがある．
                //逆もそう．
                //ccw->ccwのとき，
                //omegaにリセットをかけてないのでomegaが逆に小さくなりすぎたとき，angleが目標値に達してしまうと，omega...?なんでだ？
                //ともかく次の動作に移るとき，r_をspd_outにしとくか．
                // std::cout << "\tangle : " << angle;
                // std::cout << "\tr_omega : " << Objects::motor_reg_->r_->omega[static_cast<int>(state::Motion::AXIS::Z)];
                // std::cout << "\timu_omega : " << imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)];
                // std::cout << "\tr_angle : " << Objects::motor_reg_->r_->angle[static_cast<int>(state::Motion::AXIS::Z)];
                // std::cout << "\timu_angle : " << imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
            }
        }else{
            // std::cout << "CW" << std::endl;
            // std::cout << "\tangle : " << angle;
            // std::cout << "\tr_omega : " << Objects::motor_reg_->r_->omega[static_cast<int>(state::Motion::AXIS::Z)];
            // std::cout << "\timu_omega : " << imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)];
            // std::cout << "\tr_angle : " << Objects::motor_reg_->r_->angle[static_cast<int>(state::Motion::AXIS::Z)];
            // std::cout << "\timu_angle : " << imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
            while(imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] > angle && 
            Objects::motor_reg_->r_->omega[static_cast<int>(state::Motion::AXIS::Z)] < 0){
            // std::cout << "\tangle : " << angle;
            // std::cout << "\tr_omega : " << Objects::motor_reg_->r_->omega[static_cast<int>(state::Motion::AXIS::Z)];
            // std::cout << "\timu_omega : " << imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)];
            // std::cout << "\tr_angle : " <<  Objects::motor_reg_->r_->angle[static_cast<int>(state::Motion::AXIS::Z)];
            // std::cout << "\timu_angle : " << imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)] << std::endl;
            }
        }
        //終わりコメント
        //  std::cout << "End Turn" << std::endl;
        //目標値ごまかし//角速度
        motor_reg_->r_->omega[static_cast<int>(state::Motion::AXIS::Z)] = omega_out;
        //目標値リセット//加速度
        motor_reg_->r_->alpha[static_cast<int>(state::Motion::AXIS::Z)] = 0;
        //目標値リセット//距離
        motor_reg_->r_->angle[static_cast<int>(state::Motion::AXIS::Z)] = 0;
        //PIDのリセット
        motor_reg_->Reset_PID();
        //走行距離をリセット
        encoder_->ResetDist();
        //回転角度をリセット
        imu_->ResetAngle();
        //フラグ折る
        Flag::Reset(DRIVE_START);
        Flag::Reset(DRIVE_SPIN);
        // std::cout << "DRIVE_START flag : " << Flag::Check(DRIVE_START) << std::endl;
        //duty比リセット
        md_->Duty(0,0);
        motor_reg_->set_u_l(0);
        motor_reg_->set_u_r(0);

    }


}