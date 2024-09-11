void tim1_wait_us(uint32_t us){
    __HAL_TIM_SET_COUNTER(&htim1,0);
    HAL_TIM_Base_Start(&htim1);
    while(htim1.Instance -> CNT < us);
    HAL_TIM_Base_Stop(&htim1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim5){
        update_wall_sensor();
    }
}