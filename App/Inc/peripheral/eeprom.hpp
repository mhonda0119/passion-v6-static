#ifndef _EEPROM_HPP_
#define _EEPROM_HPP_

#include <cstdint>

#include "peripheral.h"

namespace peripheral {
    class EEPROM {
        private:
        static constexpr uint32_t EEPROM_START_ADDRESS = 0x080E0000;
        public:
            EEPROM() = default;
            HAL_StatusTypeDef EnableWrite(void);
            HAL_StatusTypeDef DisableWrite(void);
            HAL_StatusTypeDef WriteHalfword(uint32_t address, uint16_t data);
            HAL_StatusTypeDef WriteWord(uint32_t address, uint32_t data);
            uint16_t ReadHalfword(uint32_t address);
            uint32_t ReadWord(uint32_t address);
            ~EEPROM() = default;
    };
}

#endif /* _EEPROM_HPP_ */
