#include "wallsens.hpp"
namespace sensor{
    Wall::Wall(){
        std::unique_ptr<pxstr::Creater> pxstr_c = std::make_unique<pxstr::Creater>();
        std::unique_ptr<pxstr::Product> pxstr_ = pxstr_c->Create();
        std::unique_ptr<ir::Driver> ir_ = std::make_unique<ir::Driver>();
    }
}