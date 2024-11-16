#include "imu.hpp"

namespace sensor::imu{
    Product::Product()
    :   offset_(std::make_unique<state::Motion>()),
        val_(std::make_unique<state::Motion>()),
        filter_(std::make_unique<filter::Sieve>()){}

    void Product::GetOffset(){
        //オフセットの実装
        this->ReadVal();
        std::unique_ptr<state::Motion>& raw = this->get_raw_ref();
        offset_->accel[static_cast<int>(state::Motion::AXIS::X)] = raw->accel[static_cast<int>(state::Motion::AXIS::X)];
        offset_->accel[static_cast<int>(state::Motion::AXIS::Y)] = raw->accel[static_cast<int>(state::Motion::AXIS::Y)];
        offset_->accel[static_cast<int>(state::Motion::AXIS::Z)] = raw->accel[static_cast<int>(state::Motion::AXIS::Z)];
        offset_->omega[static_cast<int>(state::Motion::AXIS::X)] = raw->omega[static_cast<int>(state::Motion::AXIS::X)];
        offset_->omega[static_cast<int>(state::Motion::AXIS::Y)] = raw->omega[static_cast<int>(state::Motion::AXIS::Y)];
        offset_->omega[static_cast<int>(state::Motion::AXIS::Z)] = raw->omega[static_cast<int>(state::Motion::AXIS::Z)];
    }
    void Product::Update(){
        //更新の実装
        this->ReadVal();
        std::unique_ptr<state::Motion>& raw = this->get_raw_ref();
        val_->accel[static_cast<int>(state::Motion::AXIS::X)] = raw->accel[static_cast<int>(state::Motion::AXIS::X)] - offset_->accel[static_cast<int>(state::Motion::AXIS::X)];
        val_->accel[static_cast<int>(state::Motion::AXIS::Y)] = raw->accel[static_cast<int>(state::Motion::AXIS::Y)] - offset_->accel[static_cast<int>(state::Motion::AXIS::Y)];
        val_->accel[static_cast<int>(state::Motion::AXIS::Z)] = raw->accel[static_cast<int>(state::Motion::AXIS::Z)] - offset_->accel[static_cast<int>(state::Motion::AXIS::Z)];
        val_->omega[static_cast<int>(state::Motion::AXIS::X)] = raw->omega[static_cast<int>(state::Motion::AXIS::X)] - offset_->omega[static_cast<int>(state::Motion::AXIS::X)];
        val_->omega[static_cast<int>(state::Motion::AXIS::Y)] = raw->omega[static_cast<int>(state::Motion::AXIS::Y)] - offset_->omega[static_cast<int>(state::Motion::AXIS::Y)];
        val_->omega[static_cast<int>(state::Motion::AXIS::Z)] = raw->omega[static_cast<int>(state::Motion::AXIS::Z)] - offset_->omega[static_cast<int>(state::Motion::AXIS::Z)];
        filter_->C_1(consts::software::SENSOR_FREQ,val_);
    }
    void Product::Reset(){
        val_->angle[static_cast<int>(state::Motion::AXIS::Z)] = 0;
        val_->angle[static_cast<int>(state::Motion::AXIS::X)] = 0;
        val_->angle[static_cast<int>(state::Motion::AXIS::Y)] = 0;
    }
    std::unique_ptr<state::Motion>& Product::get_val_ref(){
        return val_;
    }
}