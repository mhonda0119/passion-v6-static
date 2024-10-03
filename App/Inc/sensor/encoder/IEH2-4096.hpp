#ifndef _IEH2_4096_HPP_
#define _IEH2_4096_HPP_


#include "encoder.hpp"
#include "peripheral.h"
#include "motion_parameter.hpp"

namespace sensor{
	class IEH2_4096 : public Product{
	private:
	//encoderのpin設定のmember変数は持っとくべき,かも．
		MotionParameter* encoder_;	//パラメータ
		std::unique_ptr<peripheral::Encoder> encoder_;
	public:
		IEH2_4096();//encorder_driverのインスタンス化
		void Init() override;//
		void Start() override;//    HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);この関数使う.
		void ReadVal() override;//MotionParameterへ読んだ値を入れます．
        virtual ~IEH2_4096() = default;
		MotionParameter* get_encoder_ptr() override ;//ポインターをゲットします．こういうのも全部uniqptr使ったほうがいいかもね．
	};
}

#endif /* _IEH2_4096_HPP_ */