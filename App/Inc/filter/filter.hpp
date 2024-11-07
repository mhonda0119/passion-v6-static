#ifndef _FILTER_HPP_
#define _FILTER_HPP_

#include <iostream>
#include <memory>

#include "states.hpp"

namespace filter{
    class Sieve{
    public:
        Sieve() = default;
        void Filter(float samplingfreq, std::unique_ptr<state::Motion>& motion);//samplingfreq[hz]
        ~Sieve() = default;
    };
}

#endif // _FILTER_HPP_
