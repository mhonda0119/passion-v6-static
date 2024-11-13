#ifndef _DESIGN_HPP_
#define _DESIGN_HPP_

#include <iostream>
#include <memory>

#include "peripheral.h"

namespace drive{
    class Design{
        private:
        float accel_ = 0;
        public:
        Design();
        void TrapeAccel(float dist , float spd_in , float spd_out);//台形加速
        float get_accel();
        ~Design() = default;
    };
}

#endif // _DESIGN_HPP_