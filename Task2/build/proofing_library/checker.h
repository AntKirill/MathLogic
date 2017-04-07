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
    std::vector<std::shared_ptr<node>> axioms;
    std::unordered_map<std::string, int> all_we_have; //every expression TO number of line
    std::unordered_multimap<std::string, int> right_impl; //right node's expr in every tree with impl in root TO number of line
    std::unordered_map<int, std::string> left_impl; //number of line TO left node's expr of every tree with impl in root
    int line = 0; //for counting lines
    annotation annotation_st;
    std::vector<std::string> assumptions;

    bool check_axioms(std::shared_ptr<node> &root) noexcept;

    bool check_assumtions(std::shared_ptr<node> &root) noexcept;

    bool check_MP(std::shared_ptr<node> &root) noexcept;

    bool check_FA_rules(std::shared_ptr<node> &root) noexcept;

    bool check_deduction_rules(std::shared_ptr<node> &root) noexcept;

public:

    checker(axioms_and_assumptions &axs) noexcept : axioms(axs.parsed_axioms), assumptions(axs.parsed_assumptions) { }

    bool check(std::shared_ptr<node> &root) noexcept;

    bool check(std::shared_ptr<node> &&root) noexcept {
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