#ifndef _INTERRUPT_HPP_
#define _INTERRUPT_HPP_

#include <iostream>
#include <memory>
#include "pxstr_creater.hpp"
#include "peripheral.h"
#include "stdout.h"
#include "states.hpp"
#include "wait.hpp"
#include "pxstr_creater.hpp"

namespace peripheral{
	class IT{
		private:
		static TIM_HandleTypeDef* htim_;
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