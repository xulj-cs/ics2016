#ifndef __JCC_H__
#define __JCC_H__

#define instr ja
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jae
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jb
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jbe
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr je
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jg
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jge
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jl
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jle
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jne
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jno
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jnp
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jns
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jo
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr jp
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#define instr js
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_v));
#undef instr

#endif
