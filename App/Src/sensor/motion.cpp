#include "motion.hpp"

namespace sensor{

    Motion::Motion()
    :   val_(std::make_unique<state::Motion>()){
        //imu_のインスタンス化
        std::unique_ptr<sensor::imu::Creater> imu_creater = std::make_unique<sensor::imu::Creater>(sensor::imu::NAME::ICM20689);
        imu_ = imu_creater->Create(&hspi3,GPIOD,CS_Pin);
        //encoderのインスタンス化
        std::unique_ptr<sensor::encoder::Creater> encoder_creater = std::make_unique<sensor::encoder::Creater>(sensor::encoder::NAME::IEH24096);
        //encoder_lとencoder_rのインスタンス化
        encoder_l_ = encoder_creater->Create(&htim4, TIM_CHANNEL_ALL);
        encoder_r_ = encoder_creater->Create(&htim8, TIM_CHANNEL_ALL);
    }

    void Motion::Init(){
        imu_->Init();
        encoder_l_->Init();
        encoder_r_->Init();
        encoder_l_->Start();
        encoder_r_->Start();
    }

    void Motion::GetOffset(){
        imu_->GetOffset();
        encoder_l_->GetOffset();
        encoder_r_->GetOffset();
    }

    void Motion::Update(){
        imu_->Update();
        encoder_l_->Update();
        encoder_r_->Update();
        //合わせる
        val_->accel[static_cast<int>(state::Motion::COORD::X)] = imu_->get_val_ptr()->accel[static_cast<int>(state::Motion::COORD::X)];
        val_->accel[static_cast<int>(state::Motion::COORD::Y)] = imu_->get_val_ptr()->accel[static_cast<int>(state::Motion::COORD::Y)];
        val_->accel[static_cast<int>(state::Motion::COORD::Z)] = imu_->get_val_ptr()->accel[static_cast<int>(state::Motion::COORD::Z)];
        val_->vel[static_cast<int>(state::Motion::COORD::X)] = imu_->get_val_ptr()->vel[static_cast<int>(state::Motion::COORD::X)];
        val_->vel[static_cast<int>(state::Motion::COORD::Y)] = imu_->get_val_ptr()->vel[static_cast<int>(state::Motion::COORD::Y)];
        val_->vel[static_cast<int>(state::Motion::COORD::Z)] = imu_->get_val_ptr()->vel[static_cast<int>(state::Motion::COORD::Z)];
        val_->pos[static_cast<int>(state::Motion::COORD::X)] = imu_->get_val_ptr()->pos[static_cast<int>(state::Motion::COORD::X)];
        val_->pos[static_cast<int>(state::Motion::COORD::Y)] = imu_->get_val_ptr()->pos[static_cast<int>(state::Motion::COORD::Y)];
        val_->pos[static_cast<int>(state::Motion::COORD::Z)] = imu_->get_val_ptr()->pos[static_cast<int>(state::Motion::COORD::Z)];
        val_->omega[static_cast<int>(state::Motion::COORD::X)] = imu_->get_val_ptr()->omega[static_cast<int>(state::Motion::COORD::X)];
        val_->omega[static_cast<int>(state::Motion::COORD::Y)] = imu_->get_val_ptr()->omega[static_cast<int>(state::Motion::COORD::Y)];
        val_->omega[static_cast<int>(state::Motion::COORD::Z)] = imu_->get_val_ptr()->omega[static_cast<int>(state::Motion::COORD::Z)];
        val_->angle[static_cast<int>(state::Motion::COORD::X)] = imu_->get_val_ptr()->angle[static_cast<int>(state::Motion::COORD::X)];
        val_->angle[static_cast<int>(state::Motion::COORD::Y)] = imu_->get_val_ptr()->angle[static_cast<int>(state::Motion::COORD::Y)];
        val_->angle[static_cast<int>(state::Motion::COORD::Z)] = imu_->get_val_ptr()->angle[static_cast<int>(state::Motion::COORD::Z)];
        val_->spd[static_cast<int>(state::Motion::DIR::R)]= encoder_r_->get_val_ptr()->spd[static_cast<int>(state::Motion::DIR::C)];
        val_->spd[static_cast<int>(state::Motion::DIR::L)]= encoder_l_->get_val_ptr()->spd[static_cast<int>(state::Motion::DIR::C)];
        val_->spd[static_cast<int>(state::Motion::DIR::C)] = (val_->spd[static_cast<int>(state::Motion::DIR::R)] + val_->spd[static_cast<int>(state::Motion::DIR::L)])/2;
    }

    std::unique_ptr<state::Motion>& Motion::get_val_ref(){
        return val_;
    }
}
