#ifndef _WAITUS_H_
#define _WAITUS_H_

#ifdef __cplusplus
 extern "C" {
#endif


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void tim1_wait_us(uint32_t us);


#ifdef __cplusplus
}
#endif

#endif /* _WAITUS_H_ */