#ifndef _ICM20689_HPP_
#define _ICM20689_HPP_

#include "imu.hpp"

namespace sensor::imu{
	class ICM20689 : public Product{
	private:
		// SPI_HandleTypeDef* hspi_;
		// GPIO_TypeDef* port_;
		// uint16_t cs_pin_;
		std::unique_ptr<peripheral::SPI> spi_;
		std::unique_ptr<state::Motion> raw_;
		float AccelRead(uint8_t H_reg) ;
		float OmegaRead(uint8_t H_reg) ;
	public:
		ICM20689(SPI_HandleTypeDef* hspi,GPIO_TypeDef* port,uint16_t cs_pin);//コンストラクタの定義はとりあえず全部した方がいいらしい
		void Init() override ;
		void ReadVal() override ;
		std::unique_ptr<state::Motion>& get_raw_ref();
		virtual ~ICM20689() = default;//デストラクタ（子クラス）
	};
}

#endif /* _ICM20689_HPP_ */
