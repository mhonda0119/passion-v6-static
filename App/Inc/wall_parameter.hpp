/*
 * wall_parameter.hpp
 *
 *  Created on: Sep 3, 2024
 *      Author: MasakatsuHonda
 */

#ifndef _WALL_PARAMETER_HPP_
#define _WALL_PARAMETER_HPP_

enum struct DIR
{
	R = 0, L , FR , FL
};

// MotionParameter 構造体の定義
struct WallParameter {
    uint16_t dir[4] = {0};       // 位置
};

#endif /* _WALL_PARAMETER_HPP_ */
