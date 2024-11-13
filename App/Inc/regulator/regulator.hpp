#ifndef _REGULATOR_HPP_
#define _REGULATOR_HPP_

#include <iostream>
#include <memory>

#include "states.hpp"
#include "ctrl.hpp"
#include "consts.hpp"
#include "objects.hpp"
#include "motion.hpp"
#include "wall.hpp"
#include "filter.hpp"
#include "adjust.hpp"

//regulator名前空間のクラスは，指令値から目標値を生成し，センサー値(制御量)との偏差を計算し
//制御器につっこみ，操作量を吐き出す仕事をみんな受け持っている．
//制御器をどう組み合わせるかを自由自在にしたい．
//いろんなパターンを自由に使い分けられるような設計にしたい．

//なんかのデザインパターンが使えそう．．．．strategyパターンかな？
//古典制御は1対1対応の原則
namespace regulator{
    class Motor{
        private:
        //壁の閾値
        float wall_th_l_;
        float wall_th_fl_;
        float wall_th_fr_;
        float wall_th_r_;
        //Objectsクラスのインスタンス化
        std::unique_ptr<Objects> objects_;

        //Wallクラスのインスタンス化
        std::unique_ptr<sensor::Wall> wall_;
        //制御器のインスタンス化
        std::unique_ptr<ctrl::PID> pid_dist_;
        std::unique_ptr<ctrl::PID> pid_spd_;
        std::unique_ptr<ctrl::PID> pid_omega_;
        std::unique_ptr<ctrl::PID> pid_angle_;
        std::unique_ptr<ctrl::PID> pid_wall_;
        //壁切れのインスタンス化
        std::unique_ptr<adjust::WallGap> wall_gap_r_;
        std::unique_ptr<adjust::WallGap> wall_gap_l_;
        //なにもしないフィルタ
        std::unique_ptr<filter::Sieve> sieve_;
        //指令値

        //操作量
        float u_r_;
        float u_l_;
        public:
        std::unique_ptr<state::Motion> r_;
        //Motionクラスのインスタンス化
        std::unique_ptr<sensor::Motion> motion_;
        //デバッグ用
        std::unique_ptr<state::Motion> debug_;
        //センサーの値取得オブジェクト，制御器オブジェクト，操作量を格納する変数．
        Motor();
        void Init();
        void Regulate(float accel,float omega );
        void Reset();
        void PID_Reset();
        void r_Reset();
        float get_u_l();
        float get_u_r();
        ~Motor() = default;
    };
}

#endif // _REGULATOR_HPP_
