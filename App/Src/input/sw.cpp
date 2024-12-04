#include "sw.hpp"

namespace input{

    SW::SW(GPIO_TypeDef* port,uint16_t pin,
    std::unique_ptr<indicator::Buzzer>& buzzer,
    std::unique_ptr<peripheral::Wait>& wait,
    std::unique_ptr<sensor::Wall>& wall)
    :  gpio_(std::make_unique<peripheral::GPIO>(port, pin)),
        buzzer_(buzzer),
        wait_(wait),
        wall_(wall),
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

    uint8_t SW::ModeSelect(uint8_t mode){
        while (true) {
        if (wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FR)] < consts::software::MODE_TH 
            && 
            wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FL)] > consts::software::MODE_TH) 
            {
            mode++;
            if (mode > 8) {
                mode = 0;
            }

            std::cout << "Mode : " << mode << std::endl;

            buzzer_->Play(((10 - mode) * 0.5 * 200),200);
        }

        if (wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FR)] > consts::software::MODE_TH 
            && 
            wall_->get_raw_ref()->dir[static_cast<int>(state::Wall::DIR::FL)] < consts::software::MODE_TH
            ) {//モード選択のセンサ閾値
            buzzer_->Play(300,50);
            wait_->Ms(100);
            buzzer_->Play(300,50);
            return mode;
        }
        }
    std::cout << "Mode : " << mode << std::endl;
    }

}
