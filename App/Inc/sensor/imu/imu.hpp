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

namespace sensor::imu{
	class Product {
	public:
		Product() = default;
		virtual void Init() = 0;
		virtual void ReadVal() = 0;
		virtual parameter::Motion* get_val_ptr() = 0;
		void Offset();
		void Update();
		virtual ~Product() = default;//仮想デストラクタ（親クラス）
	};
}


#endif // _IMU_HPP_
