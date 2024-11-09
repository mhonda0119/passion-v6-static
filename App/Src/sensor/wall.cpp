#include "wall.hpp"

namespace sensor{
    Wall::Wall(
    std::unique_ptr<sensor::pxstr::Product>& pxstr,
    std::unique_ptr<sensor::ir::OSI3CA5111A>& ir,
    std::unique_ptr<peripheral::Wait>& wait,
    std::unique_ptr<indicator::LED>& led
    )
    :raw_(std::make_unique<state::Wall>()),
    val_(std::make_unique<state::Wall>()),
    offset_(std::make_unique<state::Wall>()),
    pxstr_(pxstr),
    ir_(ir),
    wait_(wait),
    led_(led){}

    void Wall::Init(){
        pxstr_->Init();
    }

    void Wall::GetOffset(){
        //平均値用の変数
        float l=0,fl=0,fr=0,r=0;
        //壁センサのオフセットを取得
        for(int i = 0; i < 100; i++){
            this->ReadVal(consts::software::WALL_TH_L,consts::software::WALL_TH_FL,consts::software::WALL_TH_FR,consts::software::WALL_TH_R);
            //100回のうち後半70回の平均を取る
            if(i > 30){
            l += pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::L)];
            fl += pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::FL)];
            fr += pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::FR)];
            r += pxstr_->get_val_ref()->dir[static_cast<int>(state::Wall::DIR::R)];
            }
            wait_->Ms(10);
        }
        //平均の計算
        offset_->dir[static_cast<int>(state::Wall::DIR::L)] = l/70;
        offset_->dir[static_cast<int>(state::Wall::DIR::FL)] = fl/70;
        offset_->dir[static_cast<int>(state::Wall::DIR::FR)] = fr/70;
        offset_->dir[static_cast<int>(state::Wall::DIR::R)] = r/70;

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
            led_->On(2);
        }else{
            val_->dir[static_cast<int>(state::Wall::DIR::L)] = false;
            led_->Off(2);
        }
        //右壁
        if(raw_->dir[static_cast<int>(state::Wall::DIR::R)] > wall_th_r){
            val_->dir[static_cast<int>(state::Wall::DIR::R)] = true;
            led_->On(1);
        }else{
            val_->dir[static_cast<int>(state::Wall::DIR::R)] = false;
            led_->Off(1);
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

    std::unique_ptr<state::Wall>& Wall::get_offset_ref(){
        return offset_;
    }
}