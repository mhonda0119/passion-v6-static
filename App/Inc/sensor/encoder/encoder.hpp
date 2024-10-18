#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include <cstdint>
#include <memory>
#include <cstring>
#include <stdint.h>
#include <iostream>

#include "peripheral.h"
#include "motion.hpp"
#include "stdout.h"
#include "timencoder.hpp"

namespace sensor::encoder{
	class Product{
	public:
		Product() = default;//encorderのインスタンス化
		virtual void Init() = 0;//
		virtual void Start() = 0;//    HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);この関数使う.
		virtual void ReadVal() = 0;//MotionParameterへ読んだ値を入れます．
		virtual void Stop() = 0;
		virtual parameter::Motion* get_val_ptr() = 0;//ポインターをゲットします．こういうのも全部uniqptr使ったほうがいいかもね．
        virtual ~Product() = default;
	};
}

#endif /* _ENCODER_HPP_ */

