#include "cpu/exec/helper.h"
#include "cpu/reg.h"
#include "cpu/exec/eflags.h"

#define DATA_BYTE 1
#include "cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmp-template.h"
#undef DATA_BYTE

make_helper_v(cmp_ib2rm)