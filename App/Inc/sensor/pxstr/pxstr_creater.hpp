#ifndef _PXSTR_CREATER_HPP_
#define _PXSTR_CREATER_HPP_

#include "st1kl3a.hpp"

namespace sensor::pxstr{
	class Creater{
	public:
	enum struct NAME{
	ST1KL3A = 0,
	};
	Creater(NAME name);
	std::unique_ptr<Product> Create();
	~Creater() = default;
	private:
	std::unique_ptr<Product> pxstr_;
	NAME name_;
	};
}

#endif /* _PXSTR_CREATER_HPP_ */