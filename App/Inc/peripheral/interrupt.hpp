#ifndef _INTERRUPT_HPP_
#define _INTERRUPT_HPP_

#include <iostream>
#include <memory>
#include "regulator.hpp"
#include "objects.hpp"

namespace peripheral{
	class IT{
		private:
		static TIM_HandleTypeDef* htim_;
		
		static float i;
		public:
		static std::unique_ptr<Objects> md_;
		static float r_maccel_;
		static float r_alpha_;
		static std::unique_ptr<regulator::Motor> reg_motor_;
		IT() = default;
		static void Init(TIM_HandleTypeDef* htim); // 修正: 戻り値の型を追加
		static HAL_StatusTypeDef Start();
        static void PeriodElapsedCallback(); // 修正: 戻り値の型を追加
		static HAL_StatusTypeDef Stop();
		~IT() = default;
	};
}

#endif /* _INTERRUPT_HPP_ */