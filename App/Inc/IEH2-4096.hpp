#ifndef _IEH2_4096_HPP_
#define _IEH2_4096_HPP_

#include <imu.hpp>
#include <motion_parameter.hpp>
#include <spi_driver.hpp>

namespace imu{
	class IEH2_4096 : public Product{
	private:
		MotionParameter encoder_;
	public:
		IEH2_4096() = default;
		void Init() override;
        void Start() override;
		void ReadVal() override;
        virtual ~IEH2_4096() = default;
		MotionParameter* get_encoder_ptr() override ;
	};
}

#endif /* _IEH2_4096_HPP_ */