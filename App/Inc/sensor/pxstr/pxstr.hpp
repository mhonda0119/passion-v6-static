#ifndef _PXSTR_HPP_
#define _PXSTR_HPP_

//標準ライブラリ，システムライブラリ
#include <stdint.h>
#include <iostream>
#include <memory>
#include <cstring>
//自作ヘッダファイル
#include "stdout.h"
#include "adc.hpp"
#include "wall.hpp"

namespace sensor::pxstr {

	class Product{

	private:
	public:
		Product() = default;
		virtual void Init() = 0;
		virtual void ReadVal() = 0;
		virtual parameter::Wall* get_val_ptr() = 0;
		virtual ~Product() = default;
	};

}

#endif /* _PXSTR_HPP_ */
