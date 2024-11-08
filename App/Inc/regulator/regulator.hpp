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
//古典制御は1対1対応の原則
namespace regulator{
    class Motor{
        private:
        public:
        //センサーの値取得オブジェクト，制御器オブジェクト，操作量を格納する変数．
        Motor();

        ~Motor() = default;
    };
}

#endif // _REGULATOR_HPP_
