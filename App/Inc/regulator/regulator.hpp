#ifndef _REGULATOR_HPP_
#define _REGULATOR_HPP_

#include <iostream>
#include <memory>

#include "wall.hpp"
#include "imu.hpp"
#include "encoder_creater.hpp"
#include "consts.hpp"
#include "ctrl.hpp"
#include "correction.hpp"
#include "filter.hpp"
#include "states.hpp"

namespace regulator{
    class Motor{
        private:
        //制御用の壁の閾値
        float wall_th_l_;
        float wall_th_fl_;
        float wall_th_fr_;
        float wall_th_r_;
        //壁切れ制御の閾値
        float wall_gap_th_l_;
        float wall_gap_th_r_;
        //操作量//左右のモータの操作量//duty比
        float u_r_;
        float u_l_;
        //wallクラスのインスタンス
        std::unique_ptr<sensor::Wall>& wall_;
        //imuクラスのインスタンス
        std::unique_ptr<sensor::imu::Product>& imu_;
        //エンコーダのインスタンス
        std::unique_ptr<sensor::encoder::Combine>& encoder_;
        //制御器のインスタンス
        std::unique_ptr<ctrl::PID> pid_dist_;
        std::unique_ptr<ctrl::PID> pid_spd_;
        std::unique_ptr<ctrl::PID> pid_omega_;
        std::unique_ptr<ctrl::PID> pid_angle_;
        std::unique_ptr<ctrl::PID> pid_wall_;
        //壁切れのインスタンス
        std::unique_ptr<correction::WallGap> wall_gap_;
        //なにもしないフィルター
        std::unique_ptr<filter::Sieve> sieve_;

        public:
        //目標値
        std::unique_ptr<state::Motion> r_;
        Motor(std::unique_ptr<sensor::Wall>& wall,std::unique_ptr<sensor::imu::Product>& imu,
        std::unique_ptr<sensor::encoder::Combine>& encoder);
        void Regulate();
        void Reset_PID();
        float get_u_l();
        float get_u_r();
        ~Motor() = default;
    };
}


#endif /* _REGULATOR_HPP_ */