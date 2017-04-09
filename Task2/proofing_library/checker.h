#ifndef CHECKER_H
#define CHECKER_H

#include <string.h>
#include <memory.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include "node.h"
#include "parser.h"
#include "axioms_and_assumptions.h"
#include "line_annotation.h"

class checker {

    using node_ptr = std::shared_ptr<node>;

    std::vector<node_ptr> axioms;
    std::unordered_map<std::string, int> all_we_have; //every expression TO number of line
    std::unordered_multimap<std::string, int> right_impl; //right node's expr in every tree with impl in root TO number of line
    std::unordered_map<int, std::string> left_impl; //number of line TO left node's expr of every tree with impl in root
    int line = 0; //for counting lines
    annotation annotation_st;
    std::vector<std::string> assumptions;
    std::unordered_set<std::string> free_variables_from_last_assumption;

    bool check_axioms(node_ptr &root) noexcept;

    bool check_assumtions(node_ptr &root) noexcept;

    bool check_MP(node_ptr &root) noexcept;

    bool check_FA_rules(node_ptr &root) noexcept;

    bool check_deduction_rules(node_ptr &root) noexcept;

public:

    checker(axioms_and_assumptions &axs) noexcept : axioms(axs.parsed_axioms), assumptions(axs.parsed_assumptions), free_variables_from_last_assumption(axs.free_variables_from_last_assumption) { }

    bool check(node_ptr &root) noexcept;

    bool check(node_ptr &&root) noexcept {
        return check(root);
    }

    annotation get_annotation() noexcept {
        return annotation_st;
    }

    int get_line_number() noexcept {
        return line;
    }    

};

#endif