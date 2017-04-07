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

	std::ifstream finput;

	const std::string input_mp;
	const std::string input_deduction_any;
	const std::string input_deduction_exist;
	const std::string input_axiom_and_assump;
	const std::string input_last_assump;

public:

	void generate(const node_ptr &root, const annotation &state) noexcept;

	proofer() noexcept : 
	input_mp("proof_generation_templates/mp.txt"),
	input_deduction_any("proof_generation_templates/deduction_any.txt"),
	input_deduction_exist("proof_generation_templates/deduction_exist.txt"),
	input_axiom_and_assump("proof_generation_templates/axiom_and_assumption.txt"),
	input_last_assump("proof_generation_templates/last_assumption.txt") {}
};

#endif