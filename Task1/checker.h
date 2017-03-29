#ifndef CHECKER_H
#define CHECKER_H

#include <string.h>
#include <memory.h>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "node.h"
#include "parser.h"

class checker {
    std::vector<std::shared_ptr<node>> axioms;

    bool check_nodes_structure(std::shared_ptr<node> v, std::shared_ptr<node> u) noexcept;
    bool check_mapped_expr(std::unordered_map<char, std::string> &m, char u, std::string &v) noexcept;
    bool cur_axiom(std::shared_ptr<node> u, std::shared_ptr<node> root) noexcept;

    std::unordered_map<std::string, int> all_we_have; //every expression TO number of line
    std::unordered_multimap<std::string, int> right_impl; //right node's expr in every tree with impl in root TO number of line
    std::unordered_map<int, std::string> left_impl; //number of line TO left node's expr of every tree with impl in root
    int line; //for counting lines
    std::string annotation_st;
    std::vector<std::string> assumptions;

public:

    checker(std::vector<std::string> &string_axioms, std::vector<std::string> &assumptions) noexcept : line(0), assumptions(assumptions) {
        parser p;
        for (auto u: string_axioms) {
            axioms.push_back(p.parse(u));
        }
    }

    bool check_axioms(std::shared_ptr<node> root) noexcept;

    bool check_assumtions(std::shared_ptr<node> root) noexcept;

    bool check_MP(std::shared_ptr<node> root) noexcept;

    bool check(std::shared_ptr<node> root) noexcept;

    std::string get_annotation() noexcept;

    int get_line_number() noexcept;

};

#endif