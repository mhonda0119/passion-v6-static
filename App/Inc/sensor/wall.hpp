#ifndef _WALL_HPP_
#define _WALL_HPP_

#include <iostream>
#include <memory>
#include <cstdint> 

#include "objects.hpp"
#include "states.hpp"
#include "consts.hpp"

namespace sensor {
    class Wall {
    private:
        std::unique_ptr<state::Wall> raw_;
        std::unique_ptr<state::Wall> val_;
        std::unique_ptr<state::Wall> offset_;
        std::unique_ptr<sensor::pxstr::Product>& pxstr_;
        std::unique_ptr<sensor::ir::OSI3CA5111A>& ir_;
        std::unique_ptr<peripheral::Wait>& wait_;
        std::unique_ptr<indicator::LED>& led_;
    public:
        Wall(std::unique_ptr<sensor::pxstr::Product>& pxstr,
        std::unique_ptr<sensor::ir::OSI3CA5111A>& ir,
        std::unique_ptr<peripheral::Wait>& wait,
        std::unique_ptr<indicator::LED>& led);
        void Init();
        void GetOffset();
        void ReadVal(float wall_th_l,float wall_th_fl, float wall_th_fr,float wall_th_r);
        std::unique_ptr<state::Wall>& get_raw_ref();
        std::unique_ptr<state::Wall>& get_val_ref();
        std::unique_ptr<state::Wall>& get_offset_ref();
        virtual ~Wall() = default;
    };
}

#endif //_WALL_HPP_