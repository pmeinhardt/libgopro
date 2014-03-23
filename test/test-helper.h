#ifndef INCLUDE_TEST_HELPER_H
#define INCLUDE_TEST_HELPER_H

#include <stdlib.h>
#include <string.h>

#include "tap.h"

#define mem_is(a, b, len, ...) ok(memcmp(a, b, len) == 0, __VA_ARGS__)

#endif
