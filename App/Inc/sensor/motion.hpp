#ifndef _MOTION_HPP_
#define _MOTION_HPP_

#include <memory>

#include "state.hpp"
#include "sieve.hpp"
#include "imu_creater.hpp"
#include "encoder_creater.hpp"

namespace sensor{
    class Motion{
    private:
    std::unique_ptr<state::Motion> val_ = nullptr;
    std::unique_ptr<sensor::imu::Product> imu_ = nullptr;
    std::unique_ptr<sensor::encoder::Product> encoder_l_ = nullptr;
    std::unique_ptr<sensor::encoder::Product> encoder_r_ = nullptr;
    public:
        Motion() = default;
        void Fusion(std::unique_ptr<state::Motion>& imu, std::unique_ptr<state::Motion>& encoder_l , std::unique_ptr<state::Motion>& encoder_r);
        std::unique_ptr<state::Motion>& get_val_ref();
        ~Motion() = default;
    };
}

#endif // _MOTION_HPP_
