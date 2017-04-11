#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <fstream>

class generator {

	void less_or_equal(int, int) noexcept;

	void more(int, int) noexcept;

	const std::string prefix = "proofing_templates/"; 

	const std::string input_name = prefix + "base.in";

	const std::string output_name;

	std::ifstream input;

	std::ofstream output;

public:

	generator(const std::string &output_name) : output_name(output_name) {}

	void generate(const int a, const int b) {
		output.open(output_name);
		input.open(input_name);
		if (a <= b) {
	        less_or_equal(a, b);
	    }
	    else {
	        more(a, b);
	    }
	    input.close();
	    output.close();
	}
};

#endif