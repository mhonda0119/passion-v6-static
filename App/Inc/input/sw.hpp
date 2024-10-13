#ifndef SW_HPP
#define SW_HPP

#include <memory>
#include "gpio.hpp"

namespace input{
    class SW{
    private:
    std::unique_ptr<peripheral::GPIO> gpio_;
    const uint32_t db_delay_ = 50;   // デバウンス遅延時間（ms）
    uint32_t last_db_time_;          // 最後に状態が変わった時間（タイマー）
    bool last_stable_state_;         // 最後に安定した状態（押された or 離された）
    bool current_state_;             // 現在のスイッチの状態
    public:
    SW(GPIO_TypeDef* port,uint16_t pin);
    void Update();
    bool Read();
    ~SW() = default;
    };
}


#endif // _SW_HPP
