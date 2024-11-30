#ifndef _STATE_HPP_
#define _STATE_HPP_

#include <cstdint>

namespace state{
        // Motion
        struct Motion {
            enum struct AXIS
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
            float maccel[3] = {0};    // 加速度の大きさ mm/s^2
            float spd[3] = {0};            // 速さ mm/s
            float dist[3] = {0};           // みちのり mm
        };
        //Wall
        struct Wall {
            enum struct DIR
            {
                L = 0, FL , F , FR , R , BR , B , BL , ALL
            };
            uint16_t dir[9] = {0};// 方向
        };
        //MOTOR
        enum struct MOTOR {
            LEFT,
            RIGHT,
            FWD,
            BWD
        };
        //FLAG
        struct FLAG {
            bool WALL_CTRL = false;
        };
        //MAZE
        struct COORD_DIR{
            uint8_t x;
            uint8_t y;
            uint8_t dir;
        };
}

#endif // _STATE_HPP_
