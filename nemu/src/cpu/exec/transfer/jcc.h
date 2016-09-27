#define instr jz
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_w));
make_helper(concat(instr,_si_l));

make_helper(concat(instr,_si_v));
#undef instr


#define instr jbe
make_helper(concat(instr,_si_b));
make_helper(concat(instr,_si_w));
make_helper(concat(instr,_si_l));

make_helper(concat(instr,_si_v));
#undef instr
