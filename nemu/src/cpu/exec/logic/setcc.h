#ifndef __SETCC_H__
#define __SETCC_H__

#define instr seta
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setae
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setb
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setbe
make_helper(concat(instr,_rm_b));
#undef instr

#define instr sete
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setg
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setge
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setl
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setle
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setne
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setno
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setnp
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setns
make_helper(concat(instr,_rm_b));
#undef instr

#define instr seto
make_helper(concat(instr,_rm_b));
#undef instr

#define instr setp
make_helper(concat(instr,_rm_b));
#undef instr

#define instr sets
make_helper(concat(instr,_rm_b));
#undef instr

#endif
