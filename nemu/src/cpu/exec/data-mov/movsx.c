#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define DATA_BYTE 2
#include "movsx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movsx-template.h"
#undef DATA_BTYE

make_helper_v(movsx_rmb2r)


