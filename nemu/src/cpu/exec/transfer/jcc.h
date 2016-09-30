#ifndef __JCC_H__
#define __JCC_H__

#define instr jz
make_helper(concat(instr,_si_b));
//make_helper(concat(instr,_si_w));
//make_helper(concat(instr,_si_l));

make_helper(concat(instr,_si_v));
#undef instr


#define instr jbe
make_helper(concat(instr,_si_b));
//make_helper(concat(instr,_si_w));
//make_helper(concat(instr,_si_l));

make_helper(concat(instr,_si_v));
#undef instr

#define instr jle
make_helper(concat(instr,_si_b));
//make_helper(concat(instr,_si_w));
//make_helper(concat(instr,_si_l));

make_helper(concat(instr,_si_v));
#undef instr

#endif
