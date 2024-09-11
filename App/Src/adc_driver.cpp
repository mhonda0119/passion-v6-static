/*
 * adc_driver.cpp
 *
 *  Created on: Aug 28, 2024
 *      Author: MasakatsuHonda
 */

#include <adc_driver.hpp>

namespace adc{
	void Driver::ReadVal(ADC_HandleTypeDef *hadc){//,uint32_t rank)
		HAL_ADC_Start_DMA(hadc,(uint32_t *)buff_,channels_);
	}

	uint16_t* Driver::get_buff_ptr(){
		return buff_;
	}
}



