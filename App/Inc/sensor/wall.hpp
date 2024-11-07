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
        std::unique_ptr<sensor::pxstr::Product>& pxstr_;
        std::unique_ptr<sensor::ir::OSI3CA5111A>& ir_;
        std::unique_ptr<peripheral::Wait>& wait_;
    public:
        Wall(std::unique_ptr<sensor::pxstr::Product>& pxstr,
        std::unique_ptr<sensor::ir::OSI3CA5111A>& ir,
        std::unique_ptr<peripheral::Wait>& wait);
        void Init();
        void ReadVal();
        std::unique_ptr<state::Wall>& get_raw_ref();
        std::unique_ptr<state::Wall>& get_val_ref();
        virtual ~Wall() = default;
    };
}

#endif //_WALL_HPP_