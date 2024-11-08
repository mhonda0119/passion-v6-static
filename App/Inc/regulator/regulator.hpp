#ifndef _REGULATOR_HPP_
#define _REGULATOR_HPP_

#include <iostream>
#include <memory>

#include "states.hpp"
#include "ctrl.hpp"
#include "consts.hpp"
#include "objects.hpp"
#include "motion.hpp"

//regulator名前空間のクラスは，指令値から目標値を生成し，センサー値(制御量)との偏差を計算し
//制御器につっこみ，操作量を吐き出す仕事をみんな受け持っている．
//制御器をどう組み合わせるかを自由自在にしたい．
//いろんなパターンを自由に使い分けられるような設計にしたい．

//なんかのデザインパターンが使えそう．．．．strategyパターンかな？
//strategyパターンではなくて，templateを使用した静的ポリモーフィズムを使う．

namespace regulator{
    class Motion{
    private:
        std::unique_ptr<state::Motion> r_;
        std::unique_ptr<state::Motion> y_;
        float u_;
        std::unique_ptr<ctrl::PID> pid_;
    public:
        Motion() = default;
        void Gen(std::unique_ptr<state::Motion> r);
        float get_u();
        ~Motion() = default;
    };
}

#endif // _REGULATOR_HPP_
