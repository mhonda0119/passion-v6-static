#include "imu_creater.hpp"

namespace sensor::imu{
	Creater::Creater(NAME name)
	:name_(name){}
	std::unique_ptr<Product> Creater::Create() {
		switch (name_) {
			case NAME::ICM20689:
				imu_ = std::make_unique<ICM20689>();
				return std::move(imu_);//pointerの所有権の受け渡し
			default:
				return nullptr;
		}
	}
}