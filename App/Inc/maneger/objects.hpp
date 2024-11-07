#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_
//全体で共有したいオブジェクトをここに．．．．これでいいのかな？
#include <memory>
#include <iostream>
#include <cstdint>

#include "peripheral.h"
#include "imu_creater.hpp"
#include "encoder_creater.hpp"

struct Objects{
    private:
    std::unique_ptr<sensor::imu::Creater> imu_creater = std::make_unique<sensor::imu::Creater>(sensor::imu::NAME::ICM20689);
    std::unique_ptr<sensor::encoder::Creater> encoder_creater = std::make_unique<sensor::encoder::Creater>(sensor::encoder::NAME::IEH24096);
    public:
    std::unique_ptr<sensor::imu::Product> imu_ = imu_creater->Create(&hspi3,GPIOD,CS_Pin);
    std::unique_ptr<sensor::encoder::Product> encoder_r_ = encoder_creater->Create(&htim8, TIM_CHANNEL_ALL);
    std::unique_ptr<sensor::encoder::Product> encoder_l_ = encoder_creater->Create(&htim4, TIM_CHANNEL_ALL);
};


#endif // _OBJECTS_HPP_