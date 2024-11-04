#include "sieve.hpp"

namespace filter{
    void Sieve::Filter(float samplingfreq, std::unique_ptr<state::Motion>& motion){
        motion->vel[static_cast<int>(state::Motion::COORD::X)] += (1/samplingfreq) * motion->accel[static_cast<int>(state::Motion::COORD::X)];
        motion->vel[static_cast<int>(state::Motion::COORD::Y)] += (1/samplingfreq) * motion->accel[static_cast<int>(state::Motion::COORD::Y)];
        motion->vel[static_cast<int>(state::Motion::COORD::Z)] += (1/samplingfreq) * motion->accel[static_cast<int>(state::Motion::COORD::Z)];
        motion->pos[static_cast<int>(state::Motion::COORD::X)] += (1/samplingfreq) * motion->vel[static_cast<int>(state::Motion::COORD::X)];
        motion->pos[static_cast<int>(state::Motion::COORD::Y)] += (1/samplingfreq) * motion->vel[static_cast<int>(state::Motion::COORD::Y)];
        motion->pos[static_cast<int>(state::Motion::COORD::Z)] += (1/samplingfreq) * motion->vel[static_cast<int>(state::Motion::COORD::Z)];
        motion->angle[static_cast<int>(state::Motion::COORD::X)] += (1/samplingfreq) * motion->omega[static_cast<int>(state::Motion::COORD::X)];
        motion->angle[static_cast<int>(state::Motion::COORD::Y)] += (1/samplingfreq) * motion->omega[static_cast<int>(state::Motion::COORD::Y)];
        motion->angle[static_cast<int>(state::Motion::COORD::Z)] += (1/samplingfreq) * motion->omega[static_cast<int>(state::Motion::COORD::Z)];
        motion->dist += motion->spd/samplingfreq;
    }
}
