#ifndef _ENCODER_CREATER_HPP_
#define _ENCODER_CREATER_HPP_

#include "encoder.hpp"

namespace encoder{
	class Creater{
	private:
		enum struct NAME{
			IEH2-4096 = 0,
		};
		ENCODER_NAME name_;
	public:
		Creater();
		std::unique_ptr<Product> Create();
		~Creater() = default;
	};
}

#endif /* _ENCODER_CREATER_HPP_ */