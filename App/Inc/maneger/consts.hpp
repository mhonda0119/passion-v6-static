#ifndef _CONST_HPP_
#define _CONST_HPP_

namespace consts::physics{
    static constexpr float G = 9.8F;
    static constexpr float PI = 3.1415F;
    static constexpr float M2MM = 1000.0F;
    static constexpr float DEG2RAD = PI / 180.0F;
    static constexpr float RAD2DEG = 180.0F / PI;
}

namespace consts::software{
    static constexpr float SENSOR_FREQ = 1000.0F;
    static constexpr float CTRL_FREQ = 1000.0F;
    //WALLセンサの閾値
    static constexpr float WALL_TH_L = 300.0F;
    static constexpr float WALL_TH_FL = 100.0F;
    static constexpr float WALL_TH_FR = 100.0F;
    static constexpr float WALL_TH_R = 300.0F;
    //距離のPIDパラメータ
    static constexpr float KP_DIST = 0.6F;
    static constexpr float KI_DIST = 0.01F;
    static constexpr float KD_DIST = 0.05F;
    //速さのPIDパラメータ
    static constexpr float KP_SPD = 0.5F;
    static constexpr float KI_SPD = 0.1F;
    static constexpr float KD_SPD = 0.0F;
    //角速度のPIDパラメータ
    static constexpr float KP_OMEGA = 0.001F;
    static constexpr float KI_OMEGA = 0.0F;
    static constexpr float KD_OMEGA = 0.0F;
    //角度のPIDパラメータ
    static constexpr float KP_ANGLE = 0.1F;
    static constexpr float KI_ANGLE = 0.1F;
    static constexpr float KD_ANGLE = 0.01F;
    //壁制御のPIDパラメータ
    static constexpr float KP_WALL = 0.1F;
    static constexpr float KI_WALL = 0.1F;
    static constexpr float KD_WALL = 0.1F;
    //壁切れの閾値
    static constexpr float WALL_GAP_TH = 0.0F;
    //壁切れの補正値
    static constexpr float WALL_GAP_C = 0.0F;
    //jerkの最大値mm/s^3
    static constexpr float JERK_MAX = 50000.0F;
    //加速度の最大値mm/s^2
    static constexpr float ACCEL_MAX = 25000.0F;
    //速度の最大値mm/s
    static constexpr float SPD_MAX = 2000.0F;
    //超信地旋回のパラメータdeg
    static constexpr float SPIN_JERK_MAX = 80000.0F;
    static constexpr float SPIN_ALPHA_MAX = 2500.0F;
    static constexpr float SPIN_OMEGA_MAX = 200.0F;

}

namespace consts::hardware{
    static constexpr float D_TIRE = 23.8F;
    static constexpr float SUPER = 42;
    static constexpr float PINION = 13;
    static constexpr float DIST_ONE_ROT = D_TIRE * consts::physics::PI;
}

#endif // _CONST_HPP_