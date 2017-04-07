#ifndef PROOFER_H
#define PROOFER_H

#include "string_handler.h"
#include <iostream>
#include <memory>
#include "node.h"
#include "line_annotation.h"
#include <fstream>
/*
 * Takes line of correct to that line proofment and generating proofment for A->B, where A is assumption and B is taken line.
 */
class proofer : private string_handler {
	using node_ptr = std::shared_ptr<node>;

	const std::string A;

	std::ifstream finput;

	const std::string input_mp = "proof_generation_templates/mp.txt";
	const std::string input_deduction_any = "proof_generation_templates/deduction_any.txt";
	const std::string input_deduction_exist = "proof_generation_templates/deduction_exist.txt";
	const std::string input_axiom_and_assump = "proof_generation_templates/axiom_and_assumption.txt";
	const std::string input_last_assump = "proof_generation_templates/last_assumption.txt";

	void generation(const std::string &file_name, const std::string &B,const std::string &C) noexcept;

public:

	void generate(const node_ptr &root, const annotation &ann) noexcept;

	proofer() noexcept : A() {}

	proofer(const std::string &A) noexcept : A(A) {}
};

#endif