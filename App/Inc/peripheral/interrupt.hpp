#ifndef _INTERRUPT_HPP_
#define _INTERRUPT_HPP_

#include <iostream>
#include <memory>
#include "pxstr_creater.hpp"
#include "peripheral.h"
#include "stdout.h"
#include "wall.hpp"
#include "wait.hpp"
#include "pxstr_creater.hpp"
#include "wallsens.hpp"

namespace peripheral{
	class IT{
		private:
		static parameter::Wall* wp_;
		static TIM_HandleTypeDef* htim_;
		static std::unique_ptr<sensor::Wall> wall_;

		public:
		IT() = default;
		static void Init(TIM_HandleTypeDef* htim); // 修正: 戻り値の型を追加
		static HAL_StatusTypeDef Start();
        static void PeriodElapsedCallback(); // 修正: 戻り値の型を追加
		static HAL_StatusTypeDef Stop();
		~IT() = default;
	};
}

#endif /* _INTERRUPT_HPP_ */