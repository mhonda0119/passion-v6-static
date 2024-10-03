#include "imu_creater.hpp"

namespace sensor::imu{
	Creater::Creater(NAME name)
	:name_(name){}
	std::unique_ptr<Product> Creater::Create(SPI_HandleTypeDef* hspi,GPIO_TypeDef* port,uint16_t cs_pin) {
		switch (name_) {
			case NAME::ICM20689:
				imu_ = std::make_unique<ICM20689>(hspi,port,cs_pin);
				return std::move(imu_);//pointerの所有権の受け渡し
			default:
				return nullptr;
		}
	}
}
