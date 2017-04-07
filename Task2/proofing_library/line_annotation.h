#ifndef PROOFER_H
#define PROOFER_H

#include <iostream>


enum justification {
	AXIOM1, AXIOM2, AXIOM3, AXIOM4, AXIOM5, AXIOM6, AXIOM7, AXIOM8, AXIOM9, AXIOM10, AXIOM11, AXIOM12,
	AXIOM13, AXIOM14, AXIOM15, AXIOM16, AXIOM17, AXIOM18, AXIOM19, AXIOM20, AXIOM_INDUCTION, MP, DEDUCTION_ANY, DEDUCTION_EXIST, NOT_PROOFED, ASSUMP
};

static justification make_justification(int i) {
	switch(i) {
		case 1:
			return AXIOM1;
		case 2:
			return AXIOM2;
		case 3:
			return AXIOM3;
		case 4:
			return AXIOM4;
		case 5:
			return AXIOM5;
		case 6:
			return AXIOM6;
		case 7:
			return AXIOM7;
		case 8:
			return AXIOM8;
		case 9:
			return AXIOM9;
		case 10:
			return AXIOM10;
		case 11:
			return AXIOM11;
		case 12:
			return AXIOM12;
		case 13:
			return AXIOM13;
		case 14:
			return AXIOM14;
		case 15:
			return AXIOM15;
		case 16:
			return AXIOM16;
		case 17:
			return AXIOM17;
		case 18:
			return AXIOM18;
		case 19:
			return AXIOM19;
		case 20:
			return AXIOM20;
		default:
			return NOT_PROOFED;
		
	}
}

struct annotation {
	justification state;
	std::string line1;
	std::string line2;
	annotation(const justification &state, const std::string &line1, const std::string &line2) : state(state), line1(line1), line2(line2) {}
	annotation(const justification &state, const std::string &line1) : state(state), line1(line1), line2() {}
	annotation(const justification &state) : state(state), line1(), line2() {}
	annotation(int i) : line1(), line2() {
		state = make_justification(i);
	}
	annotation() {}
};

#endif 