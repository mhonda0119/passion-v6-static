#ifndef _CONST_HPP_
#define _CONST_HPP_

namespace consts::physics{
    static constexpr float G = 9.8F;
    static constexpr float PI = 3.1415F;
    static constexpr float M2MM = 1000.0F;
}

namespace consts::software{
    static constexpr float SENSOR_FREQ = 1000.0F;
    static constexpr float CTRL_FREQ = 1000.0F;
    //WALLセンサの閾値
    static constexpr float WALL_TH_L = 100.0F;
    static constexpr float WALL_TH_FL = 100.0F;
    static constexpr float WALL_TH_FR = 100.0F;
    static constexpr float WALL_TH_R = 100.0F;
    //距離のPIDパラメータ
    static constexpr float KP_DIST = 0.0F;
    static constexpr float KI_DIST = 0.0F;
    static constexpr float KD_DIST = 0.0F;
    //速さのPIDパラメータ
    static constexpr float KP_SPD = 0.0F;
    static constexpr float KI_SPD = 0.0F;
    static constexpr float KD_SPD = 0.0F;
    //角速度のPIDパラメータ
    static constexpr float KP_OMEGA = 0.0F;
    static constexpr float KI_OMEGA = 0.0F;
    static constexpr float KD_OMEGA = 0.0F;
    //角度のPIDパラメータ
    static constexpr float KP_ANGLE = 0.0F;
    static constexpr float KI_ANGLE = 0.0F;
    static constexpr float KD_ANGLE = 0.0F;
    //壁制御のPIDパラメータ
    static constexpr float KP_WALL = 0.0F;
    static constexpr float KI_WALL = 0.0F;
    static constexpr float KD_WALL = 0.0F;
    //壁切れの閾値
    static constexpr float WALL_GAP_TH = 0.0F;

}

namespace consts::hardware{
    static constexpr float D_TIRE = 23.8F;
    static constexpr float SUPER = 42;
    static constexpr float PINION = 13;
    static constexpr float DIST_ONE_ROT = D_TIRE * consts::physics::PI;
}

#endif // _CONST_HPP_