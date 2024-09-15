#ifndef _ST1KL3A_HPP_
#define _ST1KL3A_HPP_

#include "pxstr.hpp"

namespace pxstr{

	class ST1KL3A : public Product{
	private:
		WallParameter pxstr_;
		std::unique_ptr<adc::Driver> adc_;
	public:
		ST1KL3A() = default;
		void Init() override ;
		void ReadVal() override ;
		WallParameter* get_pxstr_ptr() override;
		virtual ~ST1KL3A() = default;
	};
}





#endif /* INC_ST1KL3A_H_ */
