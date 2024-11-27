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
#include "vol.hpp"
#include "wall.hpp"
#include "regulator.hpp"
#include "accel_designer.h"
#include "trajectory.h"

class Objects{
    public:
    static std::unique_ptr<sensor::imu::Product> imu_;
    static std::unique_ptr<sensor::encoder::Combine> encoder_;
    static std::unique_ptr<sensor::pxstr::Product> pxstr_;
    static std::unique_ptr<sensor::ir::OSI3CA5111A> ir_;
    static std::unique_ptr<sensor::Wall> wall_;
    static std::unique_ptr<ctrl::AccelDesigner> accel_designer_;
    static std::unique_ptr<regulator::Motor> motor_reg_;
    static std::unique_ptr<md::Product> md_;
    static std::unique_ptr<peripheral::Wait> wait_;
    static std::unique_ptr<indicator::LED> led_;
    static std::unique_ptr<indicator::Buzzer> buzzer_;
    static std::unique_ptr<sensor::bat::Vol> vol_;
    static std::unique_ptr<ctrl::slalom::Trajectory> traj_l90_;
    static std::unique_ptr<ctrl::slalom::Trajectory> traj_r90_;
    //objectsの中に，使用するインスタンスをすべてstaticで用意する．そのためのInit関数の中で，
    //あらかじめ用意したメンバ変数の中に順番に代入していく．
    Objects() = default;
    void Init();//ここでインスタンス化する．
    ~Objects() = default;
};

#endif // _OBJECTS_HPP_