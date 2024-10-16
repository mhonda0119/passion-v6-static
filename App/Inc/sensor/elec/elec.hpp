#ifndef _ELEC_HPP_
#define _ELEC_HPP_

#include <cstdint>
#include <memory>
#include <cstring>

#include "stdout.h"
#include "adc.hpp"

namespace sensor{
	class Elec{
	public:
		Elec() = default;
		virtual void Init() = 0;//初期化
		virtual void ReadVal() = 0;//M
        virtual ~Elec() = default;
	};
}

#endif //_ELEC_HPP_





