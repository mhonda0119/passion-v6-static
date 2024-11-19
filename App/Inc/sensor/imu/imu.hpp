#ifndef _IMU_HPP_
#define _IMU_HPP_

//標準ライブラリ，システムライブラリ
#include <iostream>
#include <memory>
#include <cstring>
#include <stdint.h>
//自作ヘッダファイル
#include "stdout.h"
#include "spi.hpp"
#include "consts.hpp"
#include "filter.hpp"
#include "peripheral.h"

namespace sensor::imu{
	class Product {
	private:
		std::unique_ptr<state::Motion> offset_;
		std::unique_ptr<state::Motion> val_;
		std::unique_ptr<filter::Sieve> filter_;
	public:
		Product();
		virtual void Init() = 0;
		virtual void ReadVal() = 0;
		virtual std::unique_ptr<state::Motion>& get_raw_ref() = 0;
		void GetOffset();
		void Update();
		void ResetAngle();//積算値のリセット
		std::unique_ptr<state::Motion>& get_val_ref();
		virtual ~Product() = default;//仮想デストラクタ（親クラス）
	};
}

#endif // _IMU_HPP_
