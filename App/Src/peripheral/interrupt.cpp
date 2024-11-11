#include "interrupt.hpp"

namespace peripheral{
    //staticなものはここで初期化
    TIM_HandleTypeDef* IT::htim_ = nullptr;
    std::unique_ptr<regulator::Motor> IT::reg_motor_ = std::make_unique<regulator::Motor>();
    std::unique_ptr<Objects> IT::md_ = std::make_unique<Objects>();
    //float IT::i = 0;

    void IT::Init(TIM_HandleTypeDef* htim){ 
        htim_ = htim;
        reg_motor_->Init();
        // md_->md_->On();
        // md_->md_->Dir(state::MOTOR::LEFT,state::MOTOR::FWD);
        // md_->md_->Dir(state::MOTOR::RIGHT,state::MOTOR::FWD);
    }

    HAL_StatusTypeDef IT::Start() {
    return HAL_TIM_Base_Start_IT(htim_);
    // md_->md_->Start();
    }

    void IT::PeriodElapsedCallback(){
        md_->led_->On();
        reg_motor_->Regulate(0,0);
        md_->led_->Off();
        //i++;
        // md_->md_->Duty(reg_motor_->get_u_l(),reg_motor_->get_u_r());
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
