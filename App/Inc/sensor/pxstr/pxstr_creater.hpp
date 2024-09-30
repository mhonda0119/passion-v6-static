/*
 * phototoransister_creater.h
 *
 *  Created on: Sep 4, 2024
 *      Author: MasakatsuHonda
 */

#ifndef _PXSTR_CREATER_HPP_
#define _PXSTR_CREATER_HPP_

#include "st1kl3a.hpp"

namespace pxstr{
	class Creater{
	private:
		enum struct PXSTR_NAME{
			ST1KL3A = 0,
		};
		PXSTR_NAME name_;
	public:
		Creater();
		std::unique_ptr<Product> Create();
		~Creater() = default;
	};
}

#endif /* _PXSTR_CREATER_HPP_ */
