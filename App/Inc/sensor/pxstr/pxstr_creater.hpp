#ifndef _PXSTR_CREATER_HPP_
#define _PXSTR_CREATER_HPP_

#include "st1kl3a.hpp"

namespace sensor::pxstr{
	class Creater{
	private:
	std::unique_ptr<Product> pxstr_;
		enum struct NAME{
			ST1KL3A = 0,
		};
		NAME name_;
	public:
		Creater(NAME name);
		std::unique_ptr<Product> Create();
		~Creater() = default;
	};
}

#endif /* _PXSTR_CREATER_HPP_ */