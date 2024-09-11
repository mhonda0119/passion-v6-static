#ifndef _WAITUS_H_
#define _WAITUS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "peripheral.h"

void tim1_wait_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* _WAITUS_H_ */