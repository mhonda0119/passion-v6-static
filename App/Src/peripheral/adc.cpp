#include "adc.hpp"

namespace peripheral{
	ADC::ADC(ADC_HandleTypeDef* hadc)
	:hadc_(hadc){}
	
	void ADC::ReadVal(){//,uint32_t rank)
		HAL_ADC_Start_DMA(hadc_,(uint32_t *)buff_,channels_);
		// for(int i = 0;i < 4; i++){
		// std::cout << "adc" << "[" <<i << "]" << buff_[i] << std::endl;
		// }
	}

	uint16_t* ADC::get_val_ptr(){
		return buff_;
	}
}



