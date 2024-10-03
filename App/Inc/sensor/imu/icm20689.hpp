#ifndef _ICM20689_HPP_
#define _ICM20689_HPP_

#include "imu.hpp"

namespace sensor::imu{
	class ICM20689 : public Product{
	private:
		// SPI_HandleTypeDef* hspi_;
		// GPIO_TypeDef* port_;
		// uint16_t cs_pin_;
		parameter::Motion* imu_;
		std::unique_ptr<peripheral::SPI> spi_;
		float AccelRead(uint8_t H_reg) ;
		float OmegaRead(uint8_t H_reg) ;
	public:
		ICM20689(SPI_HandleTypeDef* hspi,GPIO_TypeDef* port,uint16_t cs_pin);//コンストラクタの定義はとりあえず全部した方がいいらしい
		void Init() override ;
		void ReadVal() override ;
		parameter::Motion* get_val_ptr() override ;
		virtual ~ICM20689() = default;//デストラクタ（子クラス）
	};
}

#endif /* _ICM20689_HPP_ */
