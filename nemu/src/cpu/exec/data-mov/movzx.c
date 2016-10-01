#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"
#define DATA_BYTE 2
#include "movzx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movzx-template.h"
#undef DATA_BTYE

make_helper_v(movzx_rmb2r)


