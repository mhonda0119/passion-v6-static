/*
 * imu_creater.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: MasakatsuHonda
 */

#include <imu_creater.hpp>

namespace imu{
	Creater::Creater(){
		name_ = IMU_NAME::ICM20689;
	}

	std::unique_ptr<Product> Creater::Create() {
		std::unique_ptr<Product> imu;
		switch (name_) {
			case IMU_NAME::ICM20689:
				imu = std::make_unique<ICM20689>();
				return imu;
			default:
				return nullptr;
		}
	}
}
