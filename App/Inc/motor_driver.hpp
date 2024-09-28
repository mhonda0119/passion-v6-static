#ifndef _MOTORDRIVER_HPP_
#define _MOTORDRIVER_HPP_

#include <stdint.h>
#include <stdout.h>
#include <iostream>
#include <memory>
#include "tb6612fng.hpp"
#include "pwm_driver.hpp"
#include "peripheral.h"
#include "motor_driver_parameter.hpp"

namespace motor_driver {

	class Product{

	public:
		Product() = default;
        virtual void On() = 0;//stbyをh
        virtual void Dir(MOTOR motor ,DIR dir) = 0;//SetDirする
        virtual void Start() = 0;//pwmスタート
        virtual void Duty(float duty_l,float duty_r) = 0;
        virtual void Freq(uint32_t freq_l,uint32_t freq_r) = 0;
        virtual void Stop() = 0;//pwmストップ
        virtual void Off() = 0;//stbyをl
		virtual ~Product() = default;

	};

}

#endif /* _MOTORDRIVER_HPP_ */
