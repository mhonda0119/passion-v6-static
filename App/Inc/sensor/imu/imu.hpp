#ifndef _IMU_HPP_
#define _IMU_HPP_

#include "stdint.h"
#include "stdout.h"
#include <iostream>
#include <memory>
#include <motion_parameter.hpp>

namespace imu{
	class Product {
	public:
		Product() = default;
		virtual void Init() = 0;
		virtual void ReadVal() = 0;
		virtual MotionParameter* get_imu_ptr() = 0;
		virtual ~Product() = default;//仮想デストラクタ（親クラス）
	};
}


#endif // _IMU_HPP_
