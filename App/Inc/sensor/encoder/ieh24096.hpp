#ifndef _IEH24096_HPP_
#define _IEH24096_HPP_

#include "encoder.hpp"
#include "timencoder.hpp"
namespace sensor::encoder{
	class IEH24096 : public Product{
	private:
	//encoderのpin設定のmember変数は持っとくべき,かも．
		parameter::Motion* encoder_;	//パラメータ
		std::unique_ptr<peripheral::TimEncoder> timencoder_ = nullptr;
		TIM_HandleTypeDef* htim_;
	public:
		IEH24096(TIM_HandleTypeDef* htim, uint32_t channel);//encorderのインスタンス化
		void Init() override;//
		void Start() override;//    HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);この関数使う.
		void ReadVal() override;//MotionParameterへ読んだ値を入れます．
		void Stop() override;
		parameter::Motion* get_val_ptr() override ;//ポインターをゲットします．こういうのも全部uniqptr使ったほうがいいかもね．
        virtual ~IEH24096() = default;
	};
}

#endif /* _IEH2_4096_HPP_ */