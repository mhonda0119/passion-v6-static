#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include <iostream>
#include <memory>

#include "states.hpp"
#include "ctrl.hpp"
#include "consts.hpp"
#include "design.hpp"
#include "regulator.hpp"
#include "interrupt.hpp"
#include "flags.hpp"

namespace drive{

    class Core{
        private:
        //regulator
        std::unique_ptr<regulator::Motor>& motor_reg_;
        //imu
        std::unique_ptr<sensor::imu::Product>& imu_;
        //encoder
        std::unique_ptr<sensor::encoder::Combine>& encoder_;
        //md
        std::unique_ptr<md::Product>& md_;
        //軌道設計
        std::unique_ptr<ctrl::Design>& design_;
        public:
        Core(std::unique_ptr<regulator::Motor>& motor_reg,std::unique_ptr<sensor::imu::Product>& imu,
        std::unique_ptr<sensor::encoder::Combine>& encoder,std::unique_ptr<md::Product>& md,std::unique_ptr<ctrl::Design>& design);
        void AD(float dist , float spd_in , float spd_out);
        void CurveAD(float dist , float spd_in , float spd_out);
        void SpinTurn(float angle,float omega_in,float omega_out);
        ~Core() = default;
    };
}

#endif