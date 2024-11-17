#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include <cstdint>
#include <memory>
#include <cstring>
#include <stdint.h>
#include <iostream>

#include "peripheral.h"
#include "stdout.h"
#include "timencoder.hpp"
#include "consts.hpp"
#include "filter.hpp"


namespace sensor::encoder{
	class Product{
	protected:
		std::unique_ptr<state::Motion> offset_;
		std::unique_ptr<state::Motion> val_;
		std::unique_ptr<filter::Sieve> sieve_;
	public:
		Product();//encorderのインスタンス化
		virtual void Init() = 0;//
		virtual void Start() = 0;//HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);この関数使う.
		virtual void ReadVal() = 0;//MotionParameterへ読んだ値を入れます．
		virtual void Reset() = 0;//積算値のリセット
		virtual void Stop() = 0;
		void GetOffset();
		void Update();
		virtual std::unique_ptr<state::Motion>& get_raw_ref() = 0;
		std::unique_ptr<state::Motion>& get_val_ref();
        virtual ~Product() = default;
	};

}

#endif /* _ENCODER_HPP_ */