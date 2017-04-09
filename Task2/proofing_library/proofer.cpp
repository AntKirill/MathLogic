#include "proofer.h"

using node_ptr = std::shared_ptr<node>;

static int cnt = 0;

void proofer::generation(const std::string &file_name, const std::string &B,const std::string &C, const std::string &variable) noexcept {
	finput.open(file_name.c_str());
	std::string s;
    std::string A1 = "(" + A + ")";
    std::string B1 = "(" + B + ")";
    std::string C1 = "(" + C + ")";
	while (std::getline(finput, s)) {
		pos = 0;
		cur_token = BEGIN;
		std::string ans;
        size_t prev = 0;
		while (cur_token != END) {
			while (cur_token != PREDICATE_NAME && cur_token != VARIABLE && cur_token!=END) 
                string_handler::get_token(s);
			for (size_t i = prev; i < pos-1; i++) {
				ans += s[i];
			}
            if (cur_token == END) {
                ans += s[pos - 1];
                break;
            }
			if (cur_variable == "A") ans += A1;
			else if (cur_variable == "B") ans += B1;
			else if (cur_variable == "C") ans += C1;
            else if (cur_variable == "x") ans += variable;
			prev = pos;
            string_handler::get_token(s);
		}
		printf("%s\n", ans.data());
		cnt++;
	}
	finput.close();
}

void proofer::generate(const node_ptr &root, const annotation &ann) noexcept {
	if (A == "") {
		printf("%s\n", (root->expression).data());
		return;
	}
	if (root->expression == A) {
		generation(input_last_assump, "", "","");
		return;
	}
    switch (ann.state) {
        case AXIOM :
            generation(input_axiom_and_assump, root->expression, "", "");
            return;
        case AXIOM_INDUCTION:
            generation(input_axiom_and_assump, root->expression, "", "");
            return;
        case ASSUMP:
            generation(input_axiom_and_assump, root->expression, "", "");
            return;
        case MP:
        	generation(input_mp, ann.line1, root->expression, "");
        	return;
        case DEDUCTION_ANY:
        	generation(input_deduction_any, root->children[0]->expression, 
        		root->children[1]->children[0]->children[0]->expression, string_handler::get_variable_name(root->children[1]->children[0]->expression));
        	return;
        case DEDUCTION_EXIST:
        	generation(input_deduction_exist, root->children[0]->children[0]->children[0]->expression, 
        		root->children[1]->expression, string_handler::get_variable_name(root->children[0]->children[0]->expression));
        	return;
        case NOT_PROOFED:return;
    }
}