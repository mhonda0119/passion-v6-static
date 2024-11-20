#ifndef _DESIGN_HPP_
#define _DESIGN_HPP_

#include <iostream>
#include <memory>

#include "peripheral.h"
#include "accel_designer.h"
#include "consts.hpp"

namespace ctrl{
    class Design{
        private:
        std::unique_ptr<ctrl::AccelDesigner>& accel_designer_;
        float accel_ = 0;
        public:
        Design(std::unique_ptr<ctrl::AccelDesigner>& accel_designer);
        void TrapeAccel(float dist , float spd_in , float spd_out);//台形加速
        void CurveAccel(float dist , float spd_in , float spd_out);//曲線加速
        float get_accel();
        ~Design() = default;
    };
}

#endif // _DESIGN_HPP_