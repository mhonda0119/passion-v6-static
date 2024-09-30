#ifndef _MOTIONPARAMETER_HPP_
#define _MOTIONPARAMETER_HPP_

// 座標の列挙型
enum struct COORD
{
	X = 0, Y, Z
};

// MotionParameter 構造体の定義
struct MotionParameter {
    float pos[3] = {0};       // 位置
    float vel[3] = {0};       // 速度
    float accel[3] = {0};       // 加速度
    float angle[3] = {0};     // 角度
    float omega[3] = {0};     // 角速度 (angle_velocity)
    float alpha[3] = {0};     // 角加速度 (angle_accel)
    float spd = 0;            // 速度 (speed)
    float dist = 0;           // 距離 (distance)
};

#endif // _MOTIONPARAMETER_HPP_
