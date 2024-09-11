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
		std::cout << "ADCの値:" << std::endl;
		for (int i = 0; i < 5; i++) {
			std::cout << "buff_[" << i << "] = " << buff_[i] << std::endl;
		}
	}

	uint16_t* Driver::get_buff_ptr(){
		return const_cast<uint16_t*>(buff_);
	}
}



