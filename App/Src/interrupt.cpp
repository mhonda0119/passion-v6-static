#include "interrupt.hpp"

namespace tim{
		std::unique_ptr<pxstr::Product> IT::pxstr_ = nullptr;
		WallParameter* IT::wp_ = nullptr;
		std::unique_ptr<tim::Wait> IT::tim1_ = nullptr;
        //タイマー5を使用
        TIM_HandleTypeDef IT::name_ = htim5;
        std::unique_ptr<sensor::Wall> IT::wall_ = nullptr;

    void IT::Init(TIM_HandleTypeDef name){ // 戻り値の型を追加
        //ITのタイマー決定
        name_ = name;
        //pxstrのインスタンスを作成
        std::unique_ptr<pxstr::Creater> pxstr_c = std::make_unique<pxstr::Creater>();
        pxstr_ = pxstr_c->Create();
        pxstr_ -> Init();
        //WallParameterの初期化
        wp_ = nullptr;
        //Waitのインスタンスを作成Tim1WaitUs(uint32_t us)
        tim1_ = std::make_unique<tim::Wait>(htim1);

        std::cout << "Instance_created" << std::endl;
    }

    HAL_StatusTypeDef IT::Start() {
    return HAL_TIM_Base_Start_IT(&name_);
    }

    void IT::PeriodElapsedCallback(){

        std::cout << "Callback_triggered" << std::endl;
        if (pxstr_ != nullptr && tim1_ != nullptr)
        {
        HAL_GPIO_WritePin(IR_R_GPIO_Port, IR_R_Pin, GPIO_PIN_SET); // R
        HAL_GPIO_WritePin(IR_L_GPIO_Port, IR_L_Pin, GPIO_PIN_SET); // L
        HAL_GPIO_WritePin(IR_FR_GPIO_Port, IR_FR_Pin, GPIO_PIN_SET); // FR
        HAL_GPIO_WritePin(IR_FL_GPIO_Port, IR_FL_Pin, GPIO_PIN_SET); // FL
        tim1_->Us(20); // 修正: waitusをWaitUsに変更
        //Tim1WaitUs(20);
        pxstr_->ReadVal();
        HAL_GPIO_WritePin(IR_R_GPIO_Port, IR_R_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IR_L_GPIO_Port, IR_L_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IR_FR_GPIO_Port, IR_FR_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IR_FL_GPIO_Port, IR_FL_Pin, GPIO_PIN_RESET);
        wp_ = pxstr_->get_val_ptr();
        std::cout << "WallParameter_val: " << std::endl;
        std::cout << wp_ -> dir[static_cast<int>(DIR::R)] << std::endl;
        std::cout << wp_ -> dir[static_cast<int>(DIR::L)] << std::endl;
        std::cout << wp_ -> dir[static_cast<int>(DIR::FR)] << std::endl;
        std::cout << wp_ -> dir[static_cast<int>(DIR::FL)] << std::endl;
        std::cout << std::endl;
        }else{}

    }
    


    extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
        if (htim->Instance == htim5.Instance) {
            IT::PeriodElapsedCallback();
        }
    }

    HAL_StatusTypeDef IT::Stop(){
        return HAL_TIM_Base_Stop_IT(&name_);
    }

}
