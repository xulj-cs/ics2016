#define instr jz
make_helper(concat(instr,_i_b));
make_helper(concat(instr,_i_w));
make_helper(concat(instr,_i_l));

make_helper(concat(instr,_i_v));
#undef instr


#define instr jbe
make_helper(concat(instr,_i_b));
make_helper(concat(instr,_i_w));
make_helper(concat(instr,_i_l));

make_helper(concat(instr,_i_v));
#undef instr
