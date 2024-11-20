#include "interrupt.hpp"

namespace peripheral{
    //staticなものはここで初期化
    TIM_HandleTypeDef* IT::htim_ = nullptr;

    void IT::Init(TIM_HandleTypeDef* htim){ 
        htim_ = htim;
    }

    HAL_StatusTypeDef IT::Start() {
    return HAL_TIM_Base_Start_IT(htim_);
    }

    void IT::PeriodElapsedCallback(){
        Objects::encoder_->Update();
        Objects::imu_->Update();
        Objects::wall_->ReadVal();
        //Objects::motor_reg_->Regulate();
        Objects::motor_reg_->DesignRegulate();
        Objects::md_->Duty(Objects::motor_reg_->get_u_l(),Objects::motor_reg_->get_u_r());
    }

    extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
        if (htim->Instance == htim5.Instance) {
            IT::PeriodElapsedCallback();
        }
    }

    HAL_StatusTypeDef IT::Stop(){
        //std::cout << "i:" << i << std::endl;
        return HAL_TIM_Base_Stop_IT(htim_);
    }

}
