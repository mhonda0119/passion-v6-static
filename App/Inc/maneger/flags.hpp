#ifndef _FLAGS_HPP_
#define _FLAGS_HPP_

#include <iostream>

constexpr uint32_t DRIVE_START (1<<0);
constexpr uint32_t WALL_CTRL (1<<1);
constexpr uint32_t DRIVE_SPIN (1<<2);

class Flag{
    private:
    inline static uint32_t flags_ = 0;

    public:
    Flag() = default;
    void static Set(uint32_t flag){
        flags_ |= flag;
    }
    void static Reset(uint32_t flag){
        flags_ &= ~flag;
    }

    void static Toggle(uint32_t flag){
        flags_ ^= flag;
    }

    bool static Check(uint32_t flag) {
        return (flags_ & flag) != 0;
    }

    void static SetAll(){
        flags_ = ~0;
    }

    void static ResetAll(){
        flags_ = 0;
    }
    ~Flag() = default;
};


#endif // _FLAGS_HPP_
