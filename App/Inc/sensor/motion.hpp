#ifndef _MOTION_HPP_
#define _MOTION_HPP_

#include <iostream>
#include <memory>
#include <cstdint>

#include "encoder_creater.hpp"
#include "imu_creater.hpp"
#include "objects.hpp"

namespace sensor {
    class Motion {
    private:
        
        std::unique_ptr<sensor::encoder::Product>& encoder_l_;
        std::unique_ptr<sensor::encoder::Product>& encoder_r_;
        std::unique_ptr<sensor::imu::Product>& imu_;
    public:
        std::unique_ptr<state::Motion> val_;
        Motion(std::unique_ptr<sensor::encoder::Product>& encoder_l,
        std::unique_ptr<sensor::encoder::Product>& encoder_r,
        std::unique_ptr<sensor::imu::Product>& imu);
        void Init();
        void ReadVal();
        void GetOffset();
        void Reset();//センサの値をリセット
        void Update();
        std::unique_ptr<state::Motion>& get_val_ref();
        virtual ~Motion() = default;
    };
}

#endif //_MOTION_HPP_