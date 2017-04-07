#ifndef AXIOMS_H
#define AXIOMS_H

#include <iostream>
#include <memory.h>
#include <vector>
#include "parser.h"
#include "node.h"

class axioms_and_assumptions {
    std::vector<std::string> string_axioms = {
            "A->B->A",
            "(A->B)->(A->B->C)->(A->C)",
            "A->B->A&B",
            "A&B->A",
            "A&B->B",
            "A->A|B",
            "B->A|B",
            "(A->C)->(B->C)->(A|B->C)",
            "(A->B)->(A->!B)->!A",
            "!!A->A",

            "a=b->a'=b'",
            "a=b->a=c->b=c",
            "a'=b'->a=b",
            "!a'=0",
            "a+b'=(a+b)'",
            "a+0=a",
            "a*0=0",
            "a*b'=a*b+a"};


    void parse_assumptions(parser &p, std::string &s, std::string &all_fun_is_for) {
        std::string tmp;
        s += ' ';
        int balance = 0;
        for (size_t i = 0; i < s.length() - 1; i++) {
            if (s[i] == ' ') {
                continue;
            } else if (s[i] == '(') {
                ++balance;
                tmp += s[i];
            } else if (s[i] == ')') {
                --balance;
                tmp += s[i];
            } else if ((s[i] != ',' && !(s[i] == '|' && s[i + 1] == '-')) || (s[i] == ',' && balance != 0)) {
                tmp += s[i];
            } else {
                if (tmp != "") {
                    parsed_assumptions.push_back(p.parse(tmp)->expression);
                }
                if ((s[i] == '|' && s[i + 1] == '-')) {
                    i++;
                    last_assumption = tmp;
                }
                tmp = "";
            }
        }
        if (tmp != "") {
            all_fun_is_for = p.parse(tmp)->expression;
        }
    }

public:

    std::string all_fun_is_for;

    std::string last_assumption;

    std::vector<std::shared_ptr<node>> parsed_axioms;

    std::vector<std::string> parsed_assumptions;

    axioms_and_assumptions(std::string &assump) noexcept {
        parser p;
        parse_assumptions(p, assump, all_fun_is_for);
        for (auto s: string_axioms) {
            parsed_axioms.push_back(p.parse(s));
        }
    }

};

#endif