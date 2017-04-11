#ifndef AXIOMS_H
#define AXIOMS_H

#include <iostream>
#include <memory.h>
#include <vector>
#include <unordered_set>
#include "parser.h"
#include "node.h"
#include "tokens.h"
#include "string_handler.h"

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
        std::string tmp = "";
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
                std::shared_ptr<node> root = p.parse(tmp);
                if (tmp != "") {
                    parsed_assumptions.push_back(root->expression);
                }
                if ((s[i] == '|' && s[i + 1] == '-')) {
                    i++;
                    if (tmp != "") {
                        last_assumption = root->expression;
                        std::unordered_map<std::string, int> busy;
                        get_free_variables(root, busy, free_variables_from_last_assumption);
                    }
                }
                tmp = "";
            }
        }
        //std::cerr << tmp << std::endl;
        if (tmp != "") {
            all_fun_is_for = p.parse(tmp)->expression;
        }
    }

    void get_free_variables(std::shared_ptr<node> &v, std::unordered_map<std::string, int> &busy, std::unordered_set<std::string> &fr) noexcept
    {
        std::string name;
        if (v->op == ANY || v->op == EXIST) {
            name = string_handler::get_variable_name(v->children[0]->expression);
            if (busy.count(name)) busy[name]++;
            else busy[name] = 1;
        }
        for (size_t i = 0; i != v->children.size() && v->children[i] != nullptr; i++) {
            get_free_variables(v->children[i], busy, fr);
        }
        if (v->op == ANY || v->op == EXIST) {
            if (busy[name] == 1) busy.erase(name);
            else busy[name]--;
        }
        if (v->children[0] == nullptr && !busy.count(v->expression)) {
            fr.insert(v->expression);
        }
    }

public:

    std::string all_fun_is_for;

    std::string last_assumption;

    std::unordered_set<std::string> free_variables_from_last_assumption;

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