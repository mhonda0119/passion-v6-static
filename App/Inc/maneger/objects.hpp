#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_
//全体で共有したいオブジェクトをここに．．．．これでいいのかな？
#include <memory>
#include <iostream>
#include <cstdint>

#include "peripheral.h"
#include "imu_creater.hpp"
#include "encoder_creater.hpp"
#include "pxstr_creater.hpp"
#include "osi3ca5111a.hpp"
#include "md_creater.hpp"
#include "wait.hpp"
#include "led.hpp"
#include "states.hpp"
#include "buzzer.hpp"

struct Objects{
    private:
    // static std::unique_ptr<sensor::imu::Creater> imu_creater_;
    // static std::unique_ptr<sensor::encoder::Creater> encoder_creater_;
    // static std::unique_ptr<sensor::pxstr::Creater> pxstr_creater_;
    // static std::unique_ptr<md::Creater> md_creater_;
    public:
    //Core_objects
    // static std::unique_ptr<sensor::imu::Product> imu_;
    // static std::unique_ptr<sensor::encoder::Product> encoder_r_;
    // static std::unique_ptr<sensor::encoder::Product> encoder_l_;
    // static std::unique_ptr<sensor::pxstr::Product> pxstr_;
    //static std::unique_ptr<md::Product> md_;
    static std::unique_ptr<sensor::ir::OSI3CA5111A> osi3ca5111a_;
    static std::unique_ptr<peripheral::Wait> wait_;
    static std::unique_ptr<indicator::LED> led_;
    static std::unique_ptr<indicator::Buzzer> buzzer_;
};


#endif // _OBJECTS_HPP_