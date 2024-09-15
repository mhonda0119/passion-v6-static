#include <interrupt.hpp>

void It::PeriodElapsedCallback(TIM_HandleTypeDef *htim){ // 修正: TIM_HandletyDef を TIM_HandleTypeDef に変更
    if(htim -> Instance == TIM5){
        std::cout << "seikou" << std::endl;

        HAL_GPIO_WritePin(IR_R_GPIO_Port, IR_R_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(IR_L_GPIO_Port, IR_L_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(IR_FR_GPIO_Port, IR_FR_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(IR_FL_GPIO_Port, IR_FL_Pin, GPIO_PIN_SET);

        Tim1WaitUs(20);

        adc::Driver::ReadVal(&hadc1);

        HAL_GPIO_WritePin(IR_R_GPIO_Port, IR_R_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IR_L_GPIO_Port, IR_L_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IR_FR_GPIO_Port, IR_FR_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IR_FL_GPIO_Port, IR_FL_Pin, GPIO_PIN_RESET);

        adc::Driver::get_buff_ptr();

        uint16_t *buffPtr = adc::Driver::get_buff_ptr();
        for(int i = 0; i < 5; i++){
        std::cout << "ADC Channel " << i << ": " << buffPtr[i] << std::endl;
        }
    }
}

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    timer::PeriodElapsedCallback(htim);
}