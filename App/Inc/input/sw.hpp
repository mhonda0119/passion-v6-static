#ifndef SW_HPP_
#define SW_HPP_

#include <memory>
#include "gpio.hpp"
#include "buzzer.hpp"
#include "wait.hpp"
#include "wall.hpp"
#include "consts.hpp"
#include <cstdint>

namespace input{
    class SW{
    private:
    std::unique_ptr<peripheral::GPIO> gpio_;
    std::unique_ptr<indicator::Buzzer>& buzzer_;
    std::unique_ptr<peripheral::Wait>& wait_;
    std::unique_ptr<sensor::Wall>& wall_;
    const uint32_t db_delay_ = 50;   // デバウンス遅延時間（ms）
    uint32_t last_db_time_;          // 最後に状態が変わった時間（タイマー）
    bool last_stable_state_;         // 最後に安定した状態（押された or 離された）
    bool current_state_;      // 現在のスイッチの状態
    public:
    SW(GPIO_TypeDef* port,uint16_t pin,
    std::unique_ptr<indicator::Buzzer>& buzzer,
    std::unique_ptr<peripheral::Wait>& wait,
    std::unique_ptr<sensor::Wall>& wall);
    void Update();
    bool Read();
    uint8_t ModeSelect(uint8_t mode);
    ~SW() = default;
    };
}


#endif // _SW_HPP_
