#include "interrupt.hpp"

namespace tim{
		std::unique_ptr<pxstr::Product> pxstr = nullptr;
		WallParameter* wp = nullptr;
		std::unique_ptr<tim::Wait> tim1 = nullptr;

    It::It(){
        //pxstrのインスタンスを作成
        std::unique_ptr<pxstr::Creater> pxstr_c = std::make_unique<pxstr::Creater>();
        pxstr = pxstr_c->Create();
        pxstr -> Init();
        //WallParameterの初期化
        wp = nullptr;
        //Waitのインスタンスを作成
        tim1 = std::make_unique<tim::Wait>(htim1);
    }

    void It::PeriodElapsedCallback(TIM_HandleTypeDef *htim){

        if( pxstr != nullptr
            && 
            wp != nullptr
            &&
            tim1 != nullptr)
            {
            HAL_GPIO_WritePin(IR_R_GPIO_Port, IR_R_Pin, GPIO_PIN_SET); // R
            HAL_GPIO_WritePin(IR_L_GPIO_Port, IR_L_Pin, GPIO_PIN_SET); // L
            HAL_GPIO_WritePin(IR_FR_GPIO_Port, IR_FR_Pin, GPIO_PIN_SET); // FR
            HAL_GPIO_WritePin(IR_FL_GPIO_Port, IR_FL_Pin, GPIO_PIN_SET); // FL
            tim1->Us(20); // 修正: waitusをWaitUsに変更
            pxstr->ReadVal();
            HAL_GPIO_WritePin(IR_R_GPIO_Port, IR_R_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(IR_L_GPIO_Port, IR_L_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(IR_FR_GPIO_Port, IR_FR_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(IR_FL_GPIO_Port, IR_FL_Pin, GPIO_PIN_RESET);
            wp = pxstr->get_val_ptr();
            std::cout << "WallParameter_val: ";
            std::cout << wp -> dir[static_cast<int>(DIR::R)] << std::endl;
            std::cout << wp -> dir[static_cast<int>(DIR::L)] << std::endl;
            std::cout << wp -> dir[static_cast<int>(DIR::FR)] << std::endl;
            std::cout << wp -> dir[static_cast<int>(DIR::FL)] << std::endl;
            std::cout << std::endl;

        }else{
        }
    }

    extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
        It::PeriodElapsedCallback(htim);
    }

}
