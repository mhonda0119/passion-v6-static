/*
 * phototransistor_creater.cpp
 *
 *  Created on: Sep 4, 2024
 *      Author: MasakatsuHonda
 */

#include <pxstr_creater.hpp>

namespace pxstr{
	Creater::Creater(){
		name_ = PXSTR_NAME::ST1KL3A;
	}
	std::unique_ptr<Product> Creater::Create(){
		std::unique_ptr<Product> pxstr;
		switch(name_){
			case PXSTR_NAME::ST1KL3A:
				pxstr = std::make_unique<ST1KL3A>();
				return pxstr;
			default:
				return nullptr;
		}
	}
}




