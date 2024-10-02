#ifndef _IMU_CREATER_HPP_
#define _IMU_CREATER_HPP_

#include "icm20689.hpp"

namespace sensor::imu{
	class Creater{
	private:
		std::unique_ptr<Product> imu_;
		enum struct NAME{//enum classはenumよりscopeが明示されていて名前の衝突を避けることが出来るらしい
			ICM20689 = 0,
		};
		NAME name_;
	public:
		Creater(NAME name);
		std::unique_ptr<Product> Create();
		~Creater() = default;
	};
}

#endif /* _IMU_CREATER_HPP_ */