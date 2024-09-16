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
            static constexpr WallParameter* thresh_;
            std::unique_ptr<pxstr::Product> pxstr_;
            std::unique_ptr<ir::Driver> ir_;
            std::unique_ptr<tim::Wait> tim1_;
        public:
            Wall();//インスタンス化とメンバ変数に代入
            ReadVal();//カベのあるなしを01で
            WallParameter* get_val_ptr();
            ~Wall() = default;
    };
}

#endif //_WALLSENS_HPP_

