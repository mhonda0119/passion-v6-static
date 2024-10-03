#ifndef _SPI_HPP_
#define _SPI_HPP_

#include "stdint.h"
#include "stdout.h"
#include "peripheral.h"
#include <iostream>

namespace peripheral{
	class SPI{
	private:
	SPI_HandleTypeDef* hspi_;  // タイマのハンドル
	GPIO_TypeDef* port_;
	uint16_t cs_pin_; // CSピン

	public:
	SPI(SPI_HandleTypeDef* hspi, GPIO_TypeDef* port, uint16_t cs_pin);
	uint8_t ReadByte(uint8_t reg);
	void WriteByte(uint8_t reg , uint8_t write_val);
	~SPI() = default;
	};
}

#endif /* _SPI_HPP_ */
