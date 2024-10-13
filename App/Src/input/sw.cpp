#include "sw.hpp"

namespace input{

    SW::SW(GPIO_TypeDef* port,uint16_t pin)
    :  gpio_(std::make_unique<peripheral::GPIO>(port, pin)),
        last_db_time_(0),
        last_stable_state_(false),
        current_state_(false) {}

    void SW::Update(){
        uint32_t current_time = HAL_GetTick();

        bool reading = gpio_->ReadVal();

        if (reading != last_stable_state_) {
            // 状態が変化してからの時間がデバウンス遅延時間を超えたかを確認
            if ((current_time - last_db_time_) > db_delay_) {
                // デバウンス時間が経過したら、状態を更新
                if (reading != current_state_) {
                    current_state_ = reading;
                    // 状態が変わったので、その時点の時間を記録
                    last_db_time_ = current_time;
                }
            }
        }
        // 最後に安定した状態を更新
        last_stable_state_ = reading;
    }

    bool SW::Read(){
        return current_state_;
    }

}
