#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include <iostream>
#include <memory>
#include <optional>

#include "states.hpp"
#include "ctrl.hpp"
#include "consts.hpp"
#include "design.hpp"
#include "regulator.hpp"
#include "interrupt.hpp"
#include "flags.hpp"
#include "trajectory.h"

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
        //スラロームの軌道
        std::unique_ptr<ctrl::slalom::Trajectory>& traj_l90_; 
        std::unique_ptr<ctrl::slalom::Trajectory>& traj_r90_;
        public:
        Core(std::unique_ptr<regulator::Motor>& motor_reg,std::unique_ptr<sensor::imu::Product>& imu,
        std::unique_ptr<sensor::encoder::Combine>& encoder,std::unique_ptr<md::Product>& md,std::unique_ptr<ctrl::Design>& design,
        std::unique_ptr<ctrl::slalom::Trajectory>& traj_l90,
        std::unique_ptr<ctrl::slalom::Trajectory>& traj_r90);
        void AD(float dist , float spd_in , float spd_out);
        void CurveAD(float dist , float spd_in , float spd_out);
        void SpinTurn();
        void Slalom_L90(float v);
        void Slalom_R90(float v);
        void TurnL90(float v,float prev_d = 25,float after_d = 15);
        void TurnR90(float v,float prev_d = 15,float after_d = 47);
        void Straight(float dist,float v_in,float v_out);
        void Stop();
        void Ketsu();
        ~Core() = default;
    };
}

#endif