#ifndef _CONST_HPP_
#define _CONST_HPP_

namespace consts::physics{
    static constexpr float G = 9.8F;
    static constexpr float PI = 3.1415927F;
    static constexpr float M2MM = 1000.0F;
    static constexpr float DEG2RAD = PI / 180.0F;
    static constexpr float RAD2DEG = 180.0F / PI;
}

namespace consts::software{
    static constexpr float SENSOR_FREQ = 1000.0F;
    static constexpr float CTRL_FREQ = 1000.0F;
    //WALLセンサの閾値
    static constexpr float WALL_TH_L = 600.0F;/*本番用*/
    //static constexpr float WALL_TH_L = 1000.0F;
    //static constexpr float WALL_TH_L = 750.0F;
    static constexpr float WALL_TH_FL = 900.0F;//1300.0F;
    static constexpr float WALL_TH_FR = 1050.0F;//1300.0F;
    //static constexpr float WALL_TH_R = 1500.0F;/*本番用*/
    static constexpr float WALL_TH_R = 600.0F;
    //距離のPIDパラメータ
    // static constexpr float KP_DIST = 0.6F;
    // static constexpr float KI_DIST = 0.1F;
    // static constexpr float KD_DIST = 0.01F;

    static constexpr float KP_DIST = 2.8F;//2.8F;
    static constexpr float KI_DIST = 0.01F;//0.01F;
    static constexpr float KD_DIST = 0.1F;//2.8F;

    //速さのPIDパラメータ
    static constexpr float KP_SPD = 0.20F;
    static constexpr float KI_SPD = 0.0002F;
    static constexpr float KD_SPD = 0.20F;
    // static constexpr float KP_SPD = 0.03F;
    // static constexpr float KI_SPD = 0.0F;
    // static constexpr float KD_SPD = 0.0F;
    //角速度のPIDパラメータ
    //static constexpr float KP_OMEGA = 0.044F;
    static constexpr float KP_OMEGA = 0.17F;
    //static constexpr float KI_OMEGA = 0.0013F;
    static constexpr float KI_OMEGA = 0.01F;
    //static constexpr float KD_OMEGA = 0.006F;
    static constexpr float KD_OMEGA = 0.006F;
    // static constexpr float KP_OMEGA = 0.4F;
    // static constexpr float KI_OMEGA = 0.2F;
    // static constexpr float KD_OMEGA = 0.0F;
    //角度のPIDパラメータ
    static constexpr float KP_ANGLE = 0.01F;
    static constexpr float KI_ANGLE = 0.01F;
    static constexpr float KD_ANGLE = 0.01F;
    //壁制御のPIDパラメータ
    //static constexpr float KP_WALL = 0.002F;
    static constexpr float KP_WALL = 0.10F;//0.05
    static constexpr float KI_WALL = 0.0F;
    static constexpr float KD_WALL = 0.0F;
    //壁切れの閾値
    static constexpr float WALL_GAP_TH = 0.0F;
    //壁切れの補正値
    static constexpr float WALL_GAP_C = 0.0F;
    //jerkの最大値mm/s^3
    //static constexpr float JERK_MAX = 50000.0F;
    static constexpr float JERK_MAX = 25000.0F;
    //加速度の最大値mm/s^2
    //static constexpr float ACCEL_MAX = 25000.0F;
    static constexpr float ACCEL_MAX = 1250.0F;
    //速度の最大値mm/s
    static constexpr float SPD_MAX = 300.0F;
    //超信地旋回のパラメータdeg
    static constexpr float SPIN_JERK_MAX = 80000.0F;
    static constexpr float SPIN_ALPHA_MAX = 2500.0F;
    static constexpr float SPIN_OMEGA_MAX = 360.0F;
    //Slalomのパラメータdeg
    static constexpr float SL_JERK_MAX = 80000.0F;
    static constexpr float SL_ALPHA_MAX = 2500.0F;
    static constexpr float SL_OMEGA_MAX = 500.0F;
    //探索の基準速度mm/s
    static constexpr float SPD_SEARCH = 300.0F;//300.0F;
    //1区画の長さmm
    static constexpr float ONE_BLOCK = 180.0F;
    //半区画の長さmm
    static constexpr float HALF_BLOCK = 90.0F;
    //ゴール座標
    static constexpr uint8_t GOAL_X = 7;
    static constexpr uint8_t GOAL_Y = 8;
    //CurveADのオフセット
    //static constexpr float AD_OFFSET = 6.0F;
    static constexpr float AD_OFFSET = 0.0F;
    //モード選択時のセンサー閾値
    static constexpr float MODE_TH = 2500.0F;
    //前壁制御の閾値
    static constexpr float FWALL_TH = 3000.0F;
    //スラロームのオフセット
    static constexpr float SL_R_PREV_OFFSET = 13.0F;
    //スラロームのオフセット
    static constexpr float SL_R_AFTER_OFFSET = 25.0F;//20.0F;
    //スラロームのオフセット
    static constexpr float SL_L_PREV_OFFSET = 13.0F;
    //スラロームのオフセット
    static constexpr float SL_L_AFTER_OFFSET = 25.0F;

}

namespace consts::hardware{
    static constexpr float D_TIRE = 23.8F;
    static constexpr float SUPER = 42;
    static constexpr float PINION = 13;
    static constexpr float DIST_ONE_ROT = D_TIRE * consts::physics::PI;
}

#endif /*_CONST_HPP_*/