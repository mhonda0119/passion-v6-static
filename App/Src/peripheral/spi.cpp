#include <spi.hpp>

namespace peripheral {
	SPI::SPI(SPI_HandleTypeDef* hspi, GPIO_TypeDef* port, uint16_t cs_pin)
	:hspi_(hspi), port_(port), cs_pin_(cs_pin) {}
	
	uint8_t SPI::ReadByte(uint8_t reg) {
		uint8_t read_val_, tx_data;
		HAL_GPIO_WritePin(port_, cs_pin_, GPIO_PIN_RESET); // cs = 0;//CSピンをenableにする.
		tx_data = reg | 0x80;
		HAL_SPI_Transmit(hspi_, &tx_data, 1, 100);
		HAL_SPI_Receive(hspi_, &read_val_, 1, 100);
		HAL_GPIO_WritePin(port_, cs_pin_, GPIO_PIN_SET); // cs = 1;
		return read_val_;
	}
	void SPI::WriteByte(uint8_t reg, uint8_t write_val) {
		uint8_t tx_data;
		tx_data = reg & 0x7F;
		HAL_GPIO_WritePin(port_, cs_pin_, GPIO_PIN_RESET); // cs = 0;
		HAL_SPI_Transmit(hspi_, &tx_data, 1, 100);
		HAL_SPI_Transmit(hspi_, &write_val, 1, 100);
		HAL_GPIO_WritePin(port_, cs_pin_, GPIO_PIN_SET); // cs = 1;
	}
}
