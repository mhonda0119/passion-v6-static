#ifndef _IEH24096_HPP_
#define _IEH24096_HPP_

#include "encoder.hpp"
#include "timencoder.hpp"
#include "consts.hpp"

namespace sensor::encoder{
	class IEH24096 : public Product{
	private:
		std::unique_ptr<peripheral::TimEncoder> timencoder_ = nullptr; // timencoderを先に宣言
		std::unique_ptr<state::Motion> raw_;	//パラメータ
		TIM_HandleTypeDef* htim_;
		constexpr static uint32_t resolution_ = 4096;//分解能
	public:
		IEH24096(TIM_HandleTypeDef* htim, uint32_t channel);//encorderのインスタンス化
		void Init() override;//
		void Start() override;//    HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);この関数使う.
		void ReadVal() override;//MotionParameterへ読んだ値を入れます．
		void ResetDist() override;//積算値のリセット
		void ResetSpd() override;//速度のリセット
		void Stop() override;
		std::unique_ptr<state::Motion>& get_raw_ref() override ;//ポインターをゲットします．こういうのも全部uniqptr使ったほうがいいかもね．
        virtual ~IEH24096() = default;
	};
}

#endif /* _IEH2_4096_HPP_ */
