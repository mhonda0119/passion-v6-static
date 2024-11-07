#include "wall.hpp"

namespace sensor{
    Wall::Wall(std::unique_ptr<sensor::pxstr::Product>& pxstr,
    std::unique_ptr<sensor::ir::OSI3CA5111A>& ir,
    std::unique_ptr<peripheral::Wait>& wait)
    :raw_(std::make_unique<state::Wall>()),
    val_(std::make_unique<state::Wall>()),
    pxstr_(pxstr),
    ir_(ir),
    wait_(wait){}

    void Wall::Init(){
        pxstr_->Init();
    }

    void Wall::ReadVal(){
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
        if(raw_->dir[static_cast<int>(state::Wall::DIR::L)] > static_cast<uint16_t>(consts::software::WALL_TH_L)){
            val_->dir[static_cast<int>(state::Wall::DIR::L)] = true;
        }else{
            val_->dir[static_cast<int>(state::Wall::DIR::L)] = false;
        }
        //右壁
        if(raw_->dir[static_cast<int>(state::Wall::DIR::R)] > static_cast<uint16_t>(consts::software::WALL_TH_R)){
            val_->dir[static_cast<int>(state::Wall::DIR::R)] = true;
        }else{
            val_->dir[static_cast<int>(state::Wall::DIR::R)] = false;
        }
        //前壁
        if(raw_->dir[static_cast<int>(state::Wall::DIR::FL)] > static_cast<uint16_t>(consts::software::WALL_TH_FL) ||
            raw_->dir[static_cast<int>(state::Wall::DIR::FR)] > static_cast<uint16_t>(consts::software::WALL_TH_FR)){
            val_->dir[static_cast<int>(state::Wall::DIR::F)] = true;
        }else{
            val_->dir[static_cast<int>(state::Wall::DIR::F)] = false;
        }
    }

    std::unique_ptr<state::Wall>& Wall::get_raw_ref(){
        return raw_;
    }

    std::unique_ptr<state::Wall>& Wall::get_val_ref(){
        return val_;
    }
}