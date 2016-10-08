#include "cpu/exec/helper.h"

#define DATA_BYTE 1

#define instr seta
#define SETA
#include "setcc-template.h"
#undef SETA
#undef instr

#define instr setae
#define SETAE
#include "setcc-template.h"
#undef SETAE
#undef instr

#define instr setb
#define SETB
#include "setcc-template.h"
#undef SETB
#undef instr

#define instr setbe
#define SETBE
#include "setcc-template.h"
#undef SETBE
#undef instr

#define instr sete
#define SETE
#include "setcc-template.h"
#undef SETE
#undef instr

#define instr setg
#define SETG
#include "setcc-template.h"
#undef SETG
#undef instr

#define instr setge
#define SETGE
#include "setcc-template.h"
#undef SETGE
#undef instr

#define instr setl
#define SETL
#include "setcc-template.h"
#undef SETL
#undef instr

#define instr setle
#define SETLE
#include "setcc-template.h"
#undef SETLE
#undef instr

#define instr setne
#define SETNE
#include "setcc-template.h"
#undef SETNE
#undef instr

#define instr setno
#define SETNO
#include "setcc-template.h"
#undef SETNO
#undef instr

#define instr setnp
#define SETNP
#include "setcc-template.h"
#undef SETNP
#undef instr

#define instr setns
#define SETNS
#include "setcc-template.h"
#undef SETNS
#undef instr

#define instr seto
#define SETO
#include "setcc-template.h"
#undef SETO
#undef instr

#define instr setp
#define SETP
#include "setcc-template.h"
#undef SETP
#undef instr

#define instr sets
#define SETS
#include "setcc-template.h"
#undef SETS
#undef instr

#undef DATA_BYTE 
