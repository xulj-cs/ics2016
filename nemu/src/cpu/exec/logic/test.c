#include "cpu/exec/helper.h"
#include "cpu/exec/eflags.h"
#include "cpu/reg.h"

#define DATA_BYTE 1
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "test-template.h"
#undef DATA_BYTE

make_helper_v(test_r2rm)
