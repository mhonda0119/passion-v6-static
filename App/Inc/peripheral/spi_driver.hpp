/*
 * spi_driver.hpp
 *
 *  Created on: Aug 28, 2024
 *      Author: MasakatsuHonda
 */

#ifndef _SPI_DRIVER_HPP_
#define _SPI_DRIVER_HPP_

#include "stdint.h"
#include "stdout.h"
#include "peripheral.h"
#include <iostream>


namespace spi{
	class Driver{
	private:

	public:
	Driver() = default;
	//メンバ変数を持たない普通のクラスは，staticクラスにするべきらしいけど，.
	//reg,write_valとかが変なんなりそうな気がしている．．.
	//たぶん，reg,write_valを状態量にすべき．
	//でもprivateにおいてget関数つくるのもめんどくさいので．．．.
	uint8_t ReadByte(uint8_t reg);
	void WriteByte(uint8_t reg , uint8_t write_val);
	~Driver() = default;
	};
}

#endif /* _SPI_DRIVER_HPP_ */
