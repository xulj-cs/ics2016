#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define DATA_BYTE 1
#include "jz-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jz-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jz-template.h"
#undef DATA_BYTE

make_helper_v(jz_i)
