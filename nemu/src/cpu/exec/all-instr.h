#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/push.h"
#include "data-mov/pop.h"
#include "data-mov/leave.h"
#include "data-mov/movsx.h"
#include "data-mov/movzx.h"
#include "data-mov/cwtl-cltd.h"
#include "data-mov/mov-r2sreg.h"
#include "data-mov/pusha.h"
#include "data-mov/popa.h"

#include "arith/dec.h"
#include "arith/inc.h"
#include "arith/neg.h"
#include "arith/imul.h"
#include "arith/mul.h"
#include "arith/idiv.h"
#include "arith/div.h"
#include "arith/cmp.h"
#include "arith/sub.h"
#include "arith/add.h"
#include "arith/adc.h"
#include "arith/sbb.h"
#include "arith/sign-extend.h"

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"
#include "logic/test.h"
#include "logic/setcc.h"
#include "logic/bt.h"

#include "string/rep.h"
#include "string/movs.h"
#include "string/lods.h"
#include "string/scas.h"
#include "string/stos.h"
#include "string/std-cld.h"

#include "misc/misc.h"

#include "special/special.h"

#include "transfer/call.h"
#include "transfer/jcc.h"
#include "transfer/ret.h"
#include "transfer/jmp.h"
#include "transfer/ljmp.h"

#include "privileged/lgdt.h"
#include "privileged/lidt.h"

#include "interrupt/int.h"
#include "interrupt/cli.h"
#include "interrupt/sti.h"
#include "interrupt/iret.h"

#include "device/in.h"
#include "device/out.h"
#include "device/hlt.h"
