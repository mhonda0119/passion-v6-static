#ifndef _MOTORDRIVER_HPP_
#define _MOTORDRIVER_HPP_

#include <stdint.h>
#include <stdout.h>
#include <iostream>
#include <memory>
#include "tb6612fng.hpp"
#include "pwm.hpp"
#include "peripheral.h"
#include "states.hpp"

namespace md{

	class Product{

	public:
		Product() = default;
        virtual void On() = 0;//stbyをh
        virtual void Dir(state::MOTOR motor ,state::MOTOR dir) = 0;//SetDirする
        virtual void Start() = 0;//pwmスタート
        virtual void Duty(float duty_l,float duty_r) = 0;//モタドラによって，同時に二つ動かしたり一つだったりするのでこの辺はオーバーロードで対応
        virtual void Freq(uint32_t freq_l,uint32_t freq_r) = 0;
        virtual void ShortBrake() = 0;//pwmストップ
        virtual void Off() = 0;//stbyをl
		virtual ~Product() = default;
	};

}

#endif /* _MOTORDRIVER_HPP_ */
