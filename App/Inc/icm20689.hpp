/*
 * icm20689.hpp
 *
 *  Created on: Aug 30, 2024
 *      Author: IshiiLabHonda
 */

#ifndef _ICM20689_HPP_
#define _ICM20689_HPP_

#include <imu.hpp>
#include <motion_parameter.hpp>
#include <spi_driver.hpp>

namespace imu{
	class ICM20689 : public Product{
	private:
		MotionParameter imu_;

		float AccelRead(uint8_t H_reg) ;
		float OmegaRead(uint8_t H_reg) ;
	public:
		ICM20689() = default;//コンストラクタの定義はとりあえず全部した方がいいらしい
		virtual ~ICM20689() = default;//デストラクタ（子クラス）
		void Init() override ;
		void ReadVal() override ;
		MotionParameter* get_imu_ptr() override ;
	};
}

#endif /* _ICM20689_HPP_ */
