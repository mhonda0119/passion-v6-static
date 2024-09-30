#ifndef _IEH2_4096_HPP_
#define _IEH2_4096_HPP_


#include "encoder.hpp"

namespace encoder{
	class IEH2_4096 : public Product{
	private:
	//encoderのpin設定のmember変数は持っとくべき,かも．
		TIM_HandleTypeDef* htim_;	//タイマのハンドル
		uint32_t channel_;	//タイマのチャンネル
		MotionParameter* encoder_;	//パラメータ
		std::unique_ptr<encoder::Driver> encoder_driver_;
	public:
		IEH2_4096(TIM_HandleTypeDef* htim, uint32_t channel);//encorder_driverのインスタンス化
		void Init() override;//
		void Start() override;//    HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);この関数使う.
		void ReadVal() override;//MotionParameterへ読んだ値を入れます．
        virtual ~IEH2_4096() = default;
		MotionParameter* get_encoder_ptr() override ;//ポインターをゲットします．こういうのも全部uniqptr使ったほうがいいかもね．
	};
}

#endif /* _IEH2_4096_HPP_ */