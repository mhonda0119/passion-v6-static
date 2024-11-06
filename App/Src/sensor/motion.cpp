#include "motion.hpp"

namespace sensor {
    Motion::Motion(sensor::encoder::NAME encoder_name, sensor::imu::NAME imu_name)
    :val_(std::make_unique<state::Motion>()){
        std::unique_ptr<sensor::encoder::Creater> encoder_creater = std::make_unique<sensor::encoder::Creater>(encoder_name);
        std::unique_ptr<sensor::imu::Creater> imu_creater = std::make_unique<sensor::imu::Creater>(imu_name);
        encoder_l_ = encoder_creater->Create(&htim4, TIM_CHANNEL_ALL);
        encoder_r_ = encoder_creater->Create(&htim8, TIM_CHANNEL_ALL);
        imu_ = imu_creater->Create(&hspi3,GPIOD,CS_Pin);
    }

    void Motion::Init(){
        encoder_l_->Init();
        encoder_r_->Init();
        encoder_l_->Start();
        encoder_r_->Start();
        imu_->Init();
    }

    void Motion::ReadVal(){
        encoder_l_->ReadVal();
        encoder_r_->ReadVal();
        imu_->ReadVal();
    }

    void Motion::GetOffset(){
        encoder_l_->GetOffset();
        encoder_r_->GetOffset();
        imu_->GetOffset();
    }

    void Motion::Update(){
        encoder_l_->Update();
        encoder_r_->Update();
        imu_->Update();
    }
    std::unique_ptr<state::Motion>& Motion::get_val_ref(){
        //accel
        val_->accel[static_cast<int>(state::Motion::AXIS::X)] = 
        imu_->get_val_ref()->accel[static_cast<int>(state::Motion::AXIS::X)];
        val_->accel[static_cast<int>(state::Motion::AXIS::Y)] =
        imu_->get_val_ref()->accel[static_cast<int>(state::Motion::AXIS::Y)];
        val_->accel[static_cast<int>(state::Motion::AXIS::Z)] =
        imu_->get_val_ref()->accel[static_cast<int>(state::Motion::AXIS::Z)];
        //vel
        val_->vel[static_cast<int>(state::Motion::AXIS::X)] =
        imu_->get_val_ref()->vel[static_cast<int>(state::Motion::AXIS::X)];
        val_->vel[static_cast<int>(state::Motion::AXIS::Y)] =
        imu_->get_val_ref()->vel[static_cast<int>(state::Motion::AXIS::Y)];
        val_->vel[static_cast<int>(state::Motion::AXIS::Z)] =
        imu_->get_val_ref()->vel[static_cast<int>(state::Motion::AXIS::Z)];
        //pos
        val_->pos[static_cast<int>(state::Motion::AXIS::X)] =
        imu_->get_val_ref()->pos[static_cast<int>(state::Motion::AXIS::X)];
        val_->pos[static_cast<int>(state::Motion::AXIS::Y)] =
        imu_->get_val_ref()->pos[static_cast<int>(state::Motion::AXIS::Y)];
        val_->pos[static_cast<int>(state::Motion::AXIS::Z)] =
        imu_->get_val_ref()->pos[static_cast<int>(state::Motion::AXIS::Z)];
        //omega
        val_->omega[static_cast<int>(state::Motion::AXIS::X)] =
        imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::X)];
        val_->omega[static_cast<int>(state::Motion::AXIS::Y)] =
        imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Y)];
        val_->omega[static_cast<int>(state::Motion::AXIS::Z)] =
        imu_->get_val_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)];
        //angle
        val_->angle[static_cast<int>(state::Motion::AXIS::X)] =
        imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::X)];
        val_->angle[static_cast<int>(state::Motion::AXIS::Y)] =
        imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Y)];
        val_->angle[static_cast<int>(state::Motion::AXIS::Z)] =
        imu_->get_val_ref()->angle[static_cast<int>(state::Motion::AXIS::Z)];
        //spd
        val_->spd[static_cast<int>(state::Motion::DIR::R)] =
        encoder_r_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)];
        val_->spd[static_cast<int>(state::Motion::DIR::L)] =
        encoder_l_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)];
        val_->spd[static_cast<int>(state::Motion::DIR::C)] =
        (encoder_r_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)] +
        encoder_l_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)])/2;
        //dist
        val_->dist[static_cast<int>(state::Motion::DIR::R)] =
        encoder_r_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::R)];
        val_->dist[static_cast<int>(state::Motion::DIR::L)] =
        encoder_l_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::L)];
        val_->dist[static_cast<int>(state::Motion::DIR::C)] =
        (encoder_r_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)] +
        encoder_l_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)])/2;

        return val_;
    }
}