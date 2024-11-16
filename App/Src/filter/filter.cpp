#include "filter.hpp"

namespace filter{
    void Sieve::C_1(float samplingfreq, std::unique_ptr<state::Motion>& motion){
        motion->vel[static_cast<int>(state::Motion::AXIS::X)] += (1/samplingfreq) * motion->accel[static_cast<int>(state::Motion::AXIS::X)];
        motion->vel[static_cast<int>(state::Motion::AXIS::Y)] += (1/samplingfreq) * motion->accel[static_cast<int>(state::Motion::AXIS::Y)];
        motion->vel[static_cast<int>(state::Motion::AXIS::Z)] += (1/samplingfreq) * motion->accel[static_cast<int>(state::Motion::AXIS::Z)];
        motion->pos[static_cast<int>(state::Motion::AXIS::X)] += (1/samplingfreq) * motion->vel[static_cast<int>(state::Motion::AXIS::X)];
        motion->pos[static_cast<int>(state::Motion::AXIS::Y)] += (1/samplingfreq) * motion->vel[static_cast<int>(state::Motion::AXIS::Y)];
        motion->pos[static_cast<int>(state::Motion::AXIS::Z)] += (1/samplingfreq) * motion->vel[static_cast<int>(state::Motion::AXIS::Z)];
        motion->angle[static_cast<int>(state::Motion::AXIS::X)] += (1/samplingfreq) * motion->omega[static_cast<int>(state::Motion::AXIS::X)];
        motion->angle[static_cast<int>(state::Motion::AXIS::Y)] += (1/samplingfreq) * motion->omega[static_cast<int>(state::Motion::AXIS::Y)];
        motion->angle[static_cast<int>(state::Motion::AXIS::Z)] += (1/samplingfreq) * motion->omega[static_cast<int>(state::Motion::AXIS::Z)];
        motion->dist[static_cast<int>(state::Motion::DIR::R)] += motion->spd[static_cast<int>(state::Motion::DIR::R)]/samplingfreq;
        motion->dist[static_cast<int>(state::Motion::DIR::L)] += motion->spd[static_cast<int>(state::Motion::DIR::L)]/samplingfreq;
        motion->dist[static_cast<int>(state::Motion::DIR::C)] += motion->spd[static_cast<int>(state::Motion::DIR::C)]/samplingfreq;
    }
    void Sieve::C_2(float samplingfreq, std::unique_ptr<state::Motion>& motion){
        motion->spd[static_cast<int>(state::Motion::DIR::R)] += motion->maccel[static_cast<int>(state::Motion::DIR::R)]/samplingfreq;
        motion->spd[static_cast<int>(state::Motion::DIR::L)] += motion->maccel[static_cast<int>(state::Motion::DIR::L)]/samplingfreq;
        motion->spd[static_cast<int>(state::Motion::DIR::C)] += motion->maccel[static_cast<int>(state::Motion::DIR::C)]/samplingfreq;
        motion->dist[static_cast<int>(state::Motion::DIR::R)] += motion->spd[static_cast<int>(state::Motion::DIR::R)]/samplingfreq;
        motion->dist[static_cast<int>(state::Motion::DIR::L)] += motion->spd[static_cast<int>(state::Motion::DIR::L)]/samplingfreq;
        motion->dist[static_cast<int>(state::Motion::DIR::C)] += motion->spd[static_cast<int>(state::Motion::DIR::C)]/samplingfreq;
        motion->omega[static_cast<int>(state::Motion::AXIS::X)] += motion->alpha[static_cast<int>(state::Motion::AXIS::X)]/samplingfreq;
        motion->omega[static_cast<int>(state::Motion::AXIS::Y)] += motion->alpha[static_cast<int>(state::Motion::AXIS::Y)]/samplingfreq;
        motion->omega[static_cast<int>(state::Motion::AXIS::Z)] += motion->alpha[static_cast<int>(state::Motion::AXIS::Z)]/samplingfreq;
        motion->angle[static_cast<int>(state::Motion::AXIS::X)] += motion->omega[static_cast<int>(state::Motion::AXIS::X)]/samplingfreq;
        motion->angle[static_cast<int>(state::Motion::AXIS::Y)] += motion->omega[static_cast<int>(state::Motion::AXIS::Y)]/samplingfreq;
        motion->angle[static_cast<int>(state::Motion::AXIS::Z)] += motion->omega[static_cast<int>(state::Motion::AXIS::Z)]/samplingfreq;
    }
}
