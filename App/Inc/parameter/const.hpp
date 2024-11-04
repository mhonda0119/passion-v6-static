#ifndef _CONST_HPP_
#define _CONST_HPP_

namespace parameter::physics{
    static constexpr float G = 9.8F;
    static constexpr float PI = 3.1415F;
    static constexpr float m2mm = 1000.0F;
}

namespace parameter::software{
    static constexpr float SENSOR_FREQ = 1000.0F;
}

namespace parameter::hardware{
    static constexpr float D_TIRE = 23.8F;
    static constexpr float DIST_ONE_ROT = D_TIRE * parameter::physics::PI;
}

#endif // _CONST_HPP_