/*
 * phototoransister_creater.h
 *
 *  Created on: Sep 4, 2024
 *      Author: MasakatsuHonda
 */

#ifndef _MOTORDRIVER_CREATER_HPP_
#define _MOTORDRIVER_CREATER_HPP_

#include "tb6612fng.hpp"

namespace motor_driver{
	class Creater{
	private:
		enum struct MOTORDRIVER_NAME{
			TB6612FNG = 0,
		};
		MOTORDRIVER_NAME name_;
	public:
		Creater();
		std::unique_ptr<Product> Create();
		~Creater() = default;
	};
}

#endif /* _MOTORDRIVER_CREATER_HPP_ */