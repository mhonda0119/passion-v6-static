#ifndef _INTERRUPT_HPP_
#define _INTERRUPT_HPP_

#include <iostream>
#include <memory>
#include "pxstr_creater.hpp"
#include "peripheral.h"
#include "stdout.h"
#include "wall_parameter.hpp"
#include "wait.hpp"
#include "pxstr_creater.hpp"
#include "waitus.h"

namespace tim{
	class IT{
		private:
		static std::unique_ptr<pxstr::Product> pxstr_;
		static WallParameter* wp_;
		static std::unique_ptr<tim::Wait> tim1_;
		static TIM_HandleTypeDef name_;

		public:
		IT() = delete;
		static void Init(TIM_HandleTypeDef name); // 修正: 戻り値の型を追加
		static HAL_StatusTypeDef Start();
        static void PeriodElapsedCallback(); // 修正: 戻り値の型を追加
		static HAL_StatusTypeDef Stop();
		~IT() = default;
	};
}

#endif /* _INTERRUPT_HPP_ */