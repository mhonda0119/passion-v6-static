#ifndef _WALL_PARAMETER_HPP_
#define _WALL_PARAMETER_HPP_

#include <cstdint>
enum struct DIR
{
	R = 0, L , FR , FL , ALL
};

// MotionParameter 
struct WallParameter {
    uint16_t dir[4] = {0};       // 方向
};

#endif /* _WALL_PARAMETER_HPP_ */
