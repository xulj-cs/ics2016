#include "cpu/exec/helper.h"
#include "cpu/reg.h"
#include "cpu/exec/eflags.h"

#define DATA_BYTE 1
#include "sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "sub-template.h"
#undef DATA_BYTE

make_helper_v(sub_rm_imm)
