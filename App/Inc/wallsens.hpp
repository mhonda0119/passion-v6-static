#ifndef _WALLSENS_HPP_
#define _WALLSENS_HPP_

#include "wall_parameter.hpp"
#include <memory>
#include "pxstr_creater.hpp"
#include "ir.hpp"
#include "wait.hpp"

namespace sensor{
    class Wall{
        private:
            WallParameter* wp_;
            std::unique_ptr<pxstr::Product> pxstr_;
            std::unique_ptr<ir::Driver> ir_;
            std::unique_ptr<tim::Wait> tim1_;
        public:
            Wall();//いろんなのインスタンス化する．
            ReadVal();//wallparameterの壁のあるなしを0,1で示す．
            get_val_ptr();//その配列のポインターを返す．
            ~Wall() = default;
    };
}

#endif //_WALLSENS_HPP_

