#ifndef NODE_H
#define NODE_H

#include "token.h"
#include <iostream>
#include <memory>
#include <vector>

struct node {

    token op;

    std::string expression;

    std::vector<std::shared_ptr<node>> children = {nullptr, nullptr}; //filled from 0 to nodes.size() with actual shared_ptr's on nodes
};

#endif