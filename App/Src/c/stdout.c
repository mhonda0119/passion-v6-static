#include "stdint.h"
#include "stdout.h"
#include "peripheral.h"


void __io_putchar(uint8_t ch) {
	HAL_UART_Transmit(&huart1, &ch, 1, 1);
}
