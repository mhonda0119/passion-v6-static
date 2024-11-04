#include "imu.hpp"

namespace sensor::imu{
    Product::Product()
    :   offset_(std::make_unique<state::Motion>()),
        val_(std::make_unique<state::Motion>()),
        sieve_(std::make_unique<filter::Sieve>()){}

    void Product::GetOffset(){
        //オフセットの実装
        this->ReadVal();
        std::unique_ptr<state::Motion>& raw = this->get_raw_ptr();
        offset_->accel[static_cast<int>(state::Motion::COORD::X)] = raw->accel[static_cast<int>(state::Motion::COORD::X)];
        offset_->accel[static_cast<int>(state::Motion::COORD::Y)] = raw->accel[static_cast<int>(state::Motion::COORD::Y)];
        offset_->accel[static_cast<int>(state::Motion::COORD::Z)] = raw->accel[static_cast<int>(state::Motion::COORD::Z)];
        offset_->omega[static_cast<int>(state::Motion::COORD::X)] = raw->omega[static_cast<int>(state::Motion::COORD::X)];
        offset_->omega[static_cast<int>(state::Motion::COORD::Y)] = raw->omega[static_cast<int>(state::Motion::COORD::Y)];
        offset_->omega[static_cast<int>(state::Motion::COORD::Z)] = raw->omega[static_cast<int>(state::Motion::COORD::Z)];
    }
    void Product::Update(){
        //更新の実装
        this->ReadVal();
        std::unique_ptr<state::Motion>& raw = this->get_raw_ptr();
        val_->accel[static_cast<int>(state::Motion::COORD::X)] = raw->accel[static_cast<int>(state::Motion::COORD::X)] - offset_->accel[static_cast<int>(state::Motion::COORD::X)];
        val_->accel[static_cast<int>(state::Motion::COORD::Y)] = raw->accel[static_cast<int>(state::Motion::COORD::Y)] - offset_->accel[static_cast<int>(state::Motion::COORD::Y)];
        val_->accel[static_cast<int>(state::Motion::COORD::Z)] = raw->accel[static_cast<int>(state::Motion::COORD::Z)] - offset_->accel[static_cast<int>(state::Motion::COORD::Z)];
        val_->omega[static_cast<int>(state::Motion::COORD::X)] = raw->omega[static_cast<int>(state::Motion::COORD::X)] - offset_->omega[static_cast<int>(state::Motion::COORD::X)];
        val_->omega[static_cast<int>(state::Motion::COORD::Y)] = raw->omega[static_cast<int>(state::Motion::COORD::Y)] - offset_->omega[static_cast<int>(state::Motion::COORD::Y)];
        val_->omega[static_cast<int>(state::Motion::COORD::Z)] = raw->omega[static_cast<int>(state::Motion::COORD::Z)] - offset_->omega[static_cast<int>(state::Motion::COORD::Z)];
        sieve_->Filter(parameter::software::SENSOR_FREQ,val_);
    }
    std::unique_ptr<state::Motion>& Product::get_val_ptr(){
        return val_;
    }
}