#ifndef LINEANNOTATION_H
#define LINEANNOTATION_H

#include <iostream>


enum justification {
	AXIOM, AXIOM_INDUCTION, MP, DEDUCTION_ANY, DEDUCTION_EXIST, NOT_PROOFED, ASSUMP
};

struct annotation {
	justification state;
	std::string line1;
	std::string line2;
	int numer_of_axiom = -1;
	annotation(const justification &state, const std::string &line1, const std::string &line2) noexcept : state(state), line1(line1), line2(line2) {}
	annotation(const justification &state, const std::string &line1) noexcept : state(state), line1(line1), line2() {}
	annotation(const justification &state) noexcept : state(state), line1(), line2() {}
	annotation(int i) noexcept : line1(), line2(), numer_of_axiom(i) {
		state = AXIOM;
	}
	annotation() noexcept {}
};

#endif 