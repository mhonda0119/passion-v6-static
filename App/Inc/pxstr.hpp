#ifndef _PXSTR_HPP_
#define _PXSTR_HPP_

#include <stdint.h>
#include <stdout.h>
#include <iostream>
#include <memory>
#include "adc_driver.hpp"
#include "wall_parameter.hpp"

namespace pxstr {

	class Product{

	private:

	public:
		Product() = default;
		virtual void Init() = 0;
		virtual void ReadVal() = 0;
		virtual WallParameter* get_pxstr_ptr() = 0;
		virtual ~Product() = default;

	};

}

#endif /* _PXSTR_HPP_ */
