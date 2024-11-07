#ifndef _CONST_HPP_
#define _CONST_HPP_

namespace consts::physics{
    static constexpr float G = 9.8F;
    static constexpr float PI = 3.1415F;
    static constexpr float M2MM = 1000.0F;
}

namespace consts::software{
    static constexpr float SENSOR_FREQ = 1000.0F;
}

namespace consts::hardware{
    static constexpr float D_TIRE = 23.8F;
    static constexpr float SUPER = 42;
    static constexpr float PINION = 13;
    static constexpr float DIST_ONE_ROT = D_TIRE * consts::physics::PI;
}

#endif // _CONST_HPP_