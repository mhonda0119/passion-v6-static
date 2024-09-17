/*
 * adc_driver.cpp
 *
 *  Created on: Aug 28, 2024
 *      Author: MasakatsuHonda
 */

#include "adc_driver.hpp"

namespace adc{
	void Driver::ReadVal(ADC_HandleTypeDef *hadc){//,uint32_t rank)
		HAL_ADC_Start_DMA(hadc,(uint32_t *)buff_,channels_);
		// for(int i = 0;i < 4; i++){
		// std::cout << "adc" << "[" <<i << "]" << buff_[i] << std::endl;
		// }
	}

	uint16_t* Driver::get_val_ptr(){
		return buff_;
	}
}



