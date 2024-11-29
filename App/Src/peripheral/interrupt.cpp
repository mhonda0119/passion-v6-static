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
        if(Flag::Check(DRIVE_STOP)){
            Objects::motor_reg_->StopRegulate();
        }
        else if(Flag::Check(DRIVE_STRAIGHT)){
            Objects::motor_reg_->DesignRegulate();
        }else if(Flag::Check(DRIVE_SLALOM_L90)){
            Objects::motor_reg_->TrajL90Regulate();
        }else if(Flag::Check(DRIVE_SLALOM_R90)){
            Objects::motor_reg_->TrajR90Regulate();
        }else if(Flag::Check(DRIVE_SPIN)){
            Objects::motor_reg_->SpinRegulate();
        }
        if((abs(Objects::encoder_->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::L)]) > 3000 ||
        abs(Objects::encoder_->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::R)]) > 3000)||
        abs((Objects::encoder_->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::L)]) -
        (Objects::encoder_->get_raw_ref()->spd[static_cast<int>(state::Motion::DIR::R)]))> 6000||
        abs(Objects::imu_->get_raw_ref()->omega[static_cast<int>(state::Motion::AXIS::Z)]) > 2000){
        Objects::md_->ShortBrake();
        Objects::md_->Off();
        Objects::buzzer_->Play(1000,1000,80);
        std::cout << "FAILSAFE" << std::endl;
        }
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
