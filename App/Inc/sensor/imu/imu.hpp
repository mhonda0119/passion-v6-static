#ifndef _IMU_HPP_
#define _IMU_HPP_

//標準ライブラリ，システムライブラリ
#include <iostream>
#include <memory>
#include <cstring>
#include <stdint.h>
//自作ヘッダファイル
#include "stdout.h"
#include "motion.hpp"
#include "spi.hpp"
#include "const.hpp"
#include "sieve.hpp"

namespace sensor::imu{
	class Product {
	private:
		std::unique_ptr<state::Motion> offset_;
		std::unique_ptr<state::Motion> val_;
		std::unique_ptr<filter::Sieve> sieve_;
	public:
		Product();
		virtual void Init() = 0;
		virtual void ReadVal() = 0;
		virtual std::unique_ptr<state::Motion>& get_raw_ptr() = 0;
		void GetOffset();
		void Update();
		std::unique_ptr<state::Motion>& get_val_ptr();
		virtual ~Product() = default;//仮想デストラクタ（親クラス）
	};
}

#endif // _IMU_HPP_
