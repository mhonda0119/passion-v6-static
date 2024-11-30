#include "wall.hpp"

namespace sensor{
    Wall::Wall(std::unique_ptr<sensor::pxstr::Product>& pxstr,std::unique_ptr<sensor::ir::OSI3CA5111A>& ir,
             std::unique_ptr<peripheral::Wait>& wait,std::unique_ptr<indicator::LED>& led)
    :raw_(std::make_unique<state::Wall>()),
    offset_(std::make_unique<state::Wall>()),
    val_(std::make_unique<state::Wall>()),
    pxstr_(pxstr),
    ir_(ir),
    wait_(wait),
    led_(led){}

    void Wall::Init(){
        pxstr_->Init();
    }

    void Wall::GetOffset(){
        //壁制御用のオフセットを取得
        //100回読んで，後ろ50回の平均を取る
        float sum_l = 0.0f;
        float sum_fl = 0.0f;
        float sum_fr = 0.0f;
        float sum_r = 0.0f;

        for(uint8_t i = 0; i < 100; i++){
            wait_->Ms(1);
            ir_->On();
            wait_->Us(20);
            pxstr_->ReadVal();
            ir_->Off();
            if(i >= 50){
                sum_l += pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::L)];
                sum_fl += pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::FL)];
                sum_fr += pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::FR)];
                sum_r += pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::R)];
            }
        }
        //代入
        offset_->dir[static_cast<int>(state::Wall::DIR::L)] = sum_l / 50.0f;
        offset_->dir[static_cast<int>(state::Wall::DIR::FL)] = sum_fl / 50.0f;
        offset_->dir[static_cast<int>(state::Wall::DIR::FR)] = sum_fr / 50.0f;
        offset_->dir[static_cast<int>(state::Wall::DIR::R)] = sum_r / 50.0f;
    }

    void Wall::ReadVal(float wall_th_l,float wall_th_fl, float wall_th_fr,float wall_th_r){
        //壁センサの値を取得
        ir_->On();
        wait_->Us(15);
        pxstr_->ReadVal();
        ir_->Off();
        //代入
        raw_->dir[static_cast<int>(state::Wall::DIR::L)] = pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::L)];
        raw_->dir[static_cast<int>(state::Wall::DIR::FL)] = pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::FL)];
        raw_->dir[static_cast<int>(state::Wall::DIR::FR)] = pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::FR)];
        raw_->dir[static_cast<int>(state::Wall::DIR::R)] = pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::R)];

        //壁センサの値をフィルタリング,壁情報の取得
        //左壁
        if(raw_->dir[static_cast<int>(state::Wall::DIR::L)] > wall_th_l){
            val_->dir[static_cast<int>(state::Wall::DIR::L)] = true;
            led_->On(1);
        }else{
            val_->dir[static_cast<int>(state::Wall::DIR::L)] = false;
            led_->Off(1);
        }
        //右壁
        if(raw_->dir[static_cast<int>(state::Wall::DIR::R)] > wall_th_r){
            val_->dir[static_cast<int>(state::Wall::DIR::R)] = true;
            led_->On(2);
        }else{
            val_->dir[static_cast<int>(state::Wall::DIR::R)] = false;
            led_->Off(2);
        }
        //前壁
        if(raw_->dir[static_cast<int>(state::Wall::DIR::FL)] > wall_th_fl ||
            raw_->dir[static_cast<int>(state::Wall::DIR::FR)] > wall_th_fr){
            val_->dir[static_cast<int>(state::Wall::DIR::F)] = true;
            led_->On(7);
        }else{
            val_->dir[static_cast<int>(state::Wall::DIR::F)] = false;
            led_->Off(7);
        }
    }

    std::unique_ptr<state::Wall>& Wall::get_raw_ref(){
        return raw_;
    }

    std::unique_ptr<state::Wall>& Wall::get_offset_ref(){
        return offset_;
    }

    std::unique_ptr<state::Wall>& Wall::get_val_ref(){
        return val_;
    }

}