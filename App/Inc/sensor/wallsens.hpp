#ifndef _WALLSENS_HPP_
#define _WALLSENS_HPP_


#include <memory>
#include <cstdint>
#include "wall.hpp"
#include "pxstr_creater.hpp"
#include "osi3ca5111a.hpp"
#include "wait.hpp"

namespace sensor{
    class Wall{
        private:
            parameter::Wall* wp_;
            static parameter::Wall* thresh_;
            std::unique_ptr<sensor::pxstr::Product> pxstr_;
            std::unique_ptr<sensor::ir::OSI3CA5111A> ir_;
            std::unique_ptr<tim::Wait> tim1_;
        public:
            Wall();//インスタンス化とメンバ変数に代入
            void ReadVal();//カベのあるなしを01で
            parameter::Wall* get_val_ptr();
            ~Wall() = default;
    };
}

#endif //_WALLSENS_HPP_

