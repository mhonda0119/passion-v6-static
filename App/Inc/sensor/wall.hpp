#ifndef _WALL_HPP_
#define _WALL_HPP_

#include <iostream>
#include <memory>
#include <cstdint> 

#include "states.hpp"
#include "consts.hpp"

#include "pxstr.hpp"
#include "osi3ca5111a.hpp"
#include "wait.hpp"
#include "led.hpp"

namespace sensor {
    class Wall {
    private:
        std::unique_ptr<state::Wall> raw_;//壁制御用の生の値
        std::unique_ptr<state::Wall> offset_;//壁制御用のオフセット
        std::unique_ptr<state::Wall> val_;//壁認識用の値
        std::unique_ptr<sensor::pxstr::Product>& pxstr_;
        std::unique_ptr<sensor::ir::OSI3CA5111A>& ir_;
        std::unique_ptr<peripheral::Wait>& wait_;
        std::unique_ptr<indicator::LED>& led_;
    public:
        Wall(std::unique_ptr<sensor::pxstr::Product>& pxstr,std::unique_ptr<sensor::ir::OSI3CA5111A>& ir,
             std::unique_ptr<peripheral::Wait>& wait,std::unique_ptr<indicator::LED>& led);
        void Init();
        void GetOffset();
        void ReadVal(float wall_th_l = consts::software::WALL_TH_L,
        float wall_th_fl = consts::software::WALL_TH_FL, 
        float wall_th_fr = consts::software::WALL_TH_FR,
        float wall_th_r = consts::software::WALL_TH_R);
        std::unique_ptr<state::Wall>& get_offset_ref();
        std::unique_ptr<state::Wall>& get_raw_ref();
        std::unique_ptr<state::Wall>& get_val_ref();
        virtual ~Wall() = default;
    };
}

#endif /*_WALL_HPP_*/