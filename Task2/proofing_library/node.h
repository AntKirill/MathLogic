#ifndef NODE_H
#define NODE_H

#include "tokens.h"
#include <iostream>
#include <memory>
#include <vector>

/*
 * node contains tokens of every line in proofment and vector of its children.	Every line represented as a tree with vertexis - object of this class.
 * It will be allocated a lot of times.
 */
struct node {

    //TODO make it const
    token op;

    /*
     * Containes subformula with operation op in root
     */
    std::string expression;

    /*
     * May change only in checker
     */
    bool substituted = false;

    /*
     * This vector filled from 0 to nodes.size() with actual shared_ptr's on nodes.
     * By default the size is 2, but it can be bigger if this->op == PREDICATE_NAME
     */
    std::vector<std::shared_ptr<node>> children = {nullptr, nullptr}; 
};

#endif