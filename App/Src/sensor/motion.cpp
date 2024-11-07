#include "motion.hpp"

namespace sensor {
    Motion::Motion(std::unique_ptr<sensor::encoder::Product>& encoder_l,
    std::unique_ptr<sensor::encoder::Product>& encoder_r,
    std::unique_ptr<sensor::imu::Product>& imu)
    :val_(std::make_unique<state::Motion>()),
    encoder_l_(encoder_l),
    encoder_r_(encoder_r),
    imu_(imu){}

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
        -(encoder_r_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)]);
        val_->spd[static_cast<int>(state::Motion::DIR::L)] =
        encoder_l_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)];
        val_->spd[static_cast<int>(state::Motion::DIR::C)] =
        (-(encoder_r_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)]) +
        encoder_l_->get_val_ref()->spd[static_cast<int>(state::Motion::DIR::C)])/2;
        //dist
        val_->dist[static_cast<int>(state::Motion::DIR::R)] =
        -(encoder_r_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::R)]);
        val_->dist[static_cast<int>(state::Motion::DIR::L)] =
        encoder_l_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::L)];
        val_->dist[static_cast<int>(state::Motion::DIR::C)] =
        (-(encoder_r_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)]) +
        encoder_l_->get_val_ref()->dist[static_cast<int>(state::Motion::DIR::C)])/2;

        //std::cout << "a" << std::endl;

        return val_;
    }
}