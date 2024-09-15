#ifndef _WAITUS_H_
#define _WAITUS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include "peripheral.h"
#include "stdout.h"

void Tim1WaitUs(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* _WAITUS_H_ */