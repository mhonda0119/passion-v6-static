#ifndef _SIEVE_HPP_
#define _SIEVE_HPP_

#include <iostream>
#include <memory>

#include "state.hpp"

namespace filter{
    class Sieve{
    public:
        Sieve() = default;
        void Filter(float samplingfreq, std::unique_ptr<state::Motion>& motion);//samplingfreq[hz]
        ~Sieve() = default;
    };
}

#endif // _SIEVE_HPP_
