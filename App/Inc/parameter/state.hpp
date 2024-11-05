#ifndef _STATE_HPP_
#define _STATE_HPP_

#include <cstdint>

namespace state{
        // Motion
        struct Motion {
            enum struct COORD
            {
                X = 0, Y, Z
            };
            enum struct DIR
            {
                C = 0, R, L
            };
            float pos[3] = {0};       // 位置mm
            float vel[3] = {0};       // 速度mm/s
            float accel[3] = {0};       // 加速度mm/s^2
            float angle[3] = {0};     // 角度deg
            float omega[3] = {0};     // 角速度 deg/s
            float alpha[3] = {0};     // 角加速度 deg/s^2
            float spd[3] = {0};            // 速さ mm/s
            float dist[3] = {0};           // 距離 mm
        };

        //Wall
        struct Wall {
            enum struct DIR
            {
                R = 0, L , FR , FL , ALL
            };
            uint16_t dir[4] = {0};// 方向
        };
}

#endif // _STATE_HPP_
