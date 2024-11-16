#ifndef _REGULATOR_HPP_
#define _REGULATOR_HPP_

#include <iostream>
#include <memory>

#include "objects.hpp"
#include "wall.hpp"
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
        //wallクラスのインスタンス
        std::unique_ptr<sensor::Wall> wall_;
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
        //操作量//左右のモータの操作量//duty比
        float u_r_;
        float u_l_;
        public:
        //目標値
        std::unique_ptr<state::Motion> r_;
        

    };
}


#endif /* _REGULATOR_HPP_ */