#include "wall.hpp"

namespace sensor{
    Wall::Wall()
    :raw_(std::make_unique<state::Wall>()),
    val_(std::make_unique<state::Wall>()),
    pxstr_(Objects::pxstr_),
    ir_(Objects::ir_),
    wait_(Objects::wait_),
    led_(Objects::led_){}

    void Wall::Init(){

        Objects::pxstr_->Init();
    }

    void Wall::ReadVal(float wall_th_l,float wall_th_fl, float wall_th_fr,float wall_th_r){
        //壁センサの値を取得
        ir_->On();
        wait_->Us(20);
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

    std::unique_ptr<state::Wall>& Wall::get_val_ref(){
        return val_;
    }

}