#include "adc_driver.hpp"

namespace peripheral::adc{
	Driver::Driver(ADC_HandleTypeDef* hadc)
	:hadc_(hadc){}
	
	void Driver::ReadVal(){//,uint32_t rank)
		HAL_ADC_Start_DMA(hadc_,(uint32_t *)buff_,channels_);
		// for(int i = 0;i < 4; i++){
		// std::cout << "adc" << "[" <<i << "]" << buff_[i] << std::endl;
		// }
	}

	uint16_t* Driver::get_val_ptr(){
		return buff_;
	}
}



