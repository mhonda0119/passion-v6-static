#include "icm20689.hpp"

namespace sensor::imu{
	ICM20689::ICM20689(){
		spi_ = std::make_unique<peripheral::SPI>(&hspi3,GPIOD,CS_Pin);
	}
	void ICM20689::Init(){
		uint8_t who_am_i = 0;
		who_am_i = spi_->ReadByte(0x75);              // check WHO_AM_I (0x75)
		printf("who_am_i = 0x%x\r\n", who_am_i); // Who am I = 0x98

		if (who_am_i != 0x98) { // recheck 0x98
			HAL_Delay(100);
			who_am_i = spi_->ReadByte(0x98);
			if (who_am_i != 0x98) {
				printf("gyro_error\r\n\n");
				while (1) {
				}
			}
		}

		// PWR_MIGHT_1 0x6B
		spi_->WriteByte(0x6B, 0x00); // Set pwr might
		HAL_Delay(50);
		// PWR_MIGHT_2 0x6C
		spi_->WriteByte(0x6C, 0x00);
		HAL_Delay(50);
		// set gyro config
		// GYRO_CONFIG 0x1B
		spi_->WriteByte(0x1B, 0x18); // use 2000 dps
		HAL_Delay(50);
		// ACCEL_CONFIG 0x1C
		spi_->WriteByte(0x1B, 0x18); // use pm 16g
		HAL_Delay(50);
	}

	float ICM20689::AccelRead(uint8_t H_reg) {
		int16_t data = (int16_t)(((uint8_t)spi_->ReadByte(H_reg) << 8) |
								 (uint8_t)spi_->ReadByte(H_reg + 1));
		float accel = (float)(data / 2048.0f);
		return accel;
	}

	float ICM20689::OmegaRead(uint8_t H_reg) {
		int16_t data = (int16_t)(((uint8_t)spi_->ReadByte(H_reg) << 8) |
								 (uint8_t)spi_->ReadByte(H_reg + 1));
		float omega =
			(float)(data / 16.4f); //[deg/s] FS_SEL=3-> Scale Factor=16.4[LSB/(dps)]
		return omega;
	}


	void ICM20689::ReadVal(){
		imu_->accel[static_cast<int>(COORD::X)] = -1 * this->AccelRead(0x3B);
		imu_->accel[static_cast<int>(COORD::Y)] = this->AccelRead(0x3D);
		imu_->accel[static_cast<int>(COORD::Z)] = this->AccelRead(0x3F);
		imu_->omega[static_cast<int>(COORD::X)] = this->OmegaRead(0x43);
		imu_->omega[static_cast<int>(COORD::Y)] = this->OmegaRead(0x45);
		imu_->omega[static_cast<int>(COORD::Z)] = this->OmegaRead(0x47);
	}

	MotionParameter* ICM20689::get_val_ptr(){
			return imu_;
		}
}




