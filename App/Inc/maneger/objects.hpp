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
    std::unique_ptr<sensor::imu::Creater> imu_creater = std::make_unique<sensor::imu::Creater>(sensor::imu::NAME::ICM20689);
    std::unique_ptr<sensor::encoder::Creater> encoder_creater = std::make_unique<sensor::encoder::Creater>(sensor::encoder::NAME::IEH24096);
    std::unique_ptr<sensor::pxstr::Creater> pxstr_creater = std::make_unique<sensor::pxstr::Creater>(sensor::pxstr::NAME::ST1KL3A);
    std::unique_ptr<md::Creater> md_creater = std::make_unique<md::Creater>(md::NAME::TB6612FNG);

    public:
    std::unique_ptr<sensor::imu::Product> imu_ = imu_creater->Create(&hspi3,GPIOD,CS_Pin);
    std::unique_ptr<sensor::encoder::Product> encoder_r_ = encoder_creater->Create(&htim8, TIM_CHANNEL_ALL);
    std::unique_ptr<sensor::encoder::Product> encoder_l_ = encoder_creater->Create(&htim4, TIM_CHANNEL_ALL);
    std::unique_ptr<sensor::pxstr::Product> pxstr_ = pxstr_creater->Create(&hadc1);
    std::unique_ptr<sensor::ir::OSI3CA5111A> osi3ca5111a_ = std::make_unique<sensor::ir::OSI3CA5111A>();
    std::unique_ptr<peripheral::Wait> wait_ = std::make_unique<peripheral::Wait>(&htim1);
    std::unique_ptr<indicator::LED> led_ = std::make_unique<indicator::LED>();
    std::unique_ptr<state::FLAG>flag_ = std::make_unique<state::FLAG>();
    std::unique_ptr<md::Product> md_ = md_creater->Create(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_4);
    std::unique_ptr<indicator::Buzzer> buzzer_ = std::make_unique<indicator::Buzzer>(&htim3, TIM_CHANNEL_2);
};


#endif // _OBJECTS_HPP_