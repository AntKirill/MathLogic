#ifndef NODE_H
#define NODE_H

#include "token.h"
#include <iostream>
#include <memory>
#include <vector>

struct node {

    token op;

    std::string expression;

    /*
    // This vector filled from 0 to nodes.size() with actual shared_ptr's on nodes.
    // By default the size is 2, but it can be bigger if this->op == PREDICATE_NAME
    */
    std::vector<std::shared_ptr<node>> children = {nullptr, nullptr}; 
};

#endif