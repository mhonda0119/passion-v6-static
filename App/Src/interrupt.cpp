#include "interrupt.hpp"

namespace tim{
        //staticなメンバ変数の初期化
		WallParameter* IT::wp_ = nullptr;
        //タイマー5を使用
        TIM_HandleTypeDef IT::name_ = htim5;
        //wall_sensのインスタンス化
        std::unique_ptr<sensor::Wall> IT::wall_ = nullptr;

    void IT::Init(TIM_HandleTypeDef name){ // 戻り値の型を追加
        //ITのタイマー決定
        name_ = name;
        //wallsensのインスタンス化　
        wall_ = std::make_unique<sensor::Wall>();
    }

    HAL_StatusTypeDef IT::Start() {
    return HAL_TIM_Base_Start_IT(&name_);
    }

    void IT::PeriodElapsedCallback(){
        if (wall_ != nullptr)
        {   
            //実質ここから
            wall_->ReadVal();
            wp_ = wall_->get_val_ptr();
            //ここまで
            std::cout << "WallParameter: " << std::endl;
            for (int i = 0; i < 4; i++) {
                std::cout << wp_->dir[i] << " " << std::endl;
            }
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
