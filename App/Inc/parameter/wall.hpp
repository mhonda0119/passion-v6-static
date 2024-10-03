#ifndef _WALL_HPP_
#define _WALL_HPP_

#include <cstdint>
namespace parameter {
    enum struct DIR
    {
        R = 0, L , FR , FL , ALL
    };

    // MotionParameter 
    struct Wall {
        uint16_t dir[4] = {0};       // 方向
    };
}

#endif /* _WALL_HPP_ */
