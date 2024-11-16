#ifndef _FILTER_HPP_
#define _FILTER_HPP_

#include <iostream>
#include <memory>

#include "states.hpp"

namespace filter{
    class Sieve{
    public:
        Sieve() = default;
        void C_1(float samplingfreq, std::unique_ptr<state::Motion>& motion);//samplingfreq[hz]//センサ値用
        void C_2(float samplingfreq, std::unique_ptr<state::Motion>& motion); //目標値用
        ~Sieve() = default;
    };
}

#endif // _FILTER_HPP_
