#ifndef NODE_H
#define NODE_H

#include "token.h"
#include <iostream>
#include <memory>
#include <vector>

/*
// node contains token of every line in proovement.	Every line represented as a tree with vertexis - object of this class.
// It will be allocated a lot of times.
*/
struct node {

    token op; //TODO make it const

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