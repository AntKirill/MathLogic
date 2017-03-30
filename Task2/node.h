#ifndef NODE_H
#define NODE_H

#include "token.h"
#include <iostream>
#include <memory>

struct node {

    token op;
    std::string expression;

    std::shared_ptr<node> left, right;

    node() noexcept : left(nullptr), right(nullptr) { }
};

#endif