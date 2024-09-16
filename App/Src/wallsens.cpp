#include "wallsens.hpp"
namespace sensor{
    Wall::Wall(){
        std::unique_ptr<pxstr::Creater> Wall::pxstr_c = std::make_unique<pxstr::Creater>();
        std::unique_ptr<pxstr::Product> Wall::pxstr_ = pxstr_c->Create();
        std::unique_ptr<ir::Driver> Wall::ir_ = std::make_unique<ir::Driver>();
        std::unique_ptr<tim::Wait> Wall::tim1_ = std::make_unique<tim::Wait>(htim1);
    }
    Wall::ReadVal(){
        ir_ -> On();//ir光らせる
        tim1_ -> Us(20);//充電まつ
        pxstr_ -> ReadVal();//読む
        ir_ -> Off();//ir消す
        wp_ = pxstr_ -> get_val_ptr();

    }
}