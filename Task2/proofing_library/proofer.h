#ifndef PROOFER_H
#define PROOFER_H

#include "string_handler.h"
#include <iostream>
#include <memory>
#include "node.h"
#include "line_annotation.h"
#include <fstream>
#include <vector>
/*
 * Takes line of correct to that line proofment and generating proofment for A->B, where A is assumption and B is taken line.
 */
class proofer : private string_handler {
	using node_ptr = std::shared_ptr<node>;

	const std::string A;

	std::ifstream finput;

	const std::string prefix = "proof_generation_templates/";

	const std::string input_mp = prefix + "mp.txt";
	const std::string input_deduction_any = prefix + "deduction_any.txt";
	const std::string input_deduction_exist = prefix + "deduction_exist.txt";
	const std::string input_axiom_and_assump = prefix + "axiom_and_assumption.txt";
	const std::string input_last_assump = prefix + "last_assumption.txt";

	void generation(const std::string &file_name, const std::string &B,const std::string &C,const std::string &variable) noexcept;

public:

	static void generate_caption(const std::vector<std::string> &, const std::string &) noexcept;

	void generate(const node_ptr &root, const annotation &ann) noexcept;

	proofer() noexcept : A() {}

	proofer(const std::string &A) noexcept : A(A) {}
};

#endif