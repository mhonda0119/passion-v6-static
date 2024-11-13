#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include <iostream>
#include <memory>

#include "states.hpp"
#include "ctrl.hpp"
#include "consts.hpp"
#include "objects.hpp"
#include "motion.hpp"
#include "design.hpp"
#include "interrupt.hpp"

namespace drive{

    class Core{
        private:
        //壁の閾値
        std::unique_ptr<Objects> objects_;
        std::unique_ptr<drive::Design> design_;
        public:
        Core();
        void Init();
        void AD(float dist , float spd_in , float spd_out);
        ~Core() = default;
    };
}

#endif