#ifndef _TEST_HPP_
#define _TEST_HPP_

#include <iostream>

namespace mode{
    class Test{
    public:
        Test() = default;
        void Encoder();
        void IMU();
        void Wall();
        void SW();
        void Buzzer();
        void LED();
        void MD();
        ~Test() = default;
    };
}

#endif //_TEST_HPP_
