#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

enum token {
    IMPL, OR, AND, NOT, BRACKET_OPEN,  BRACKET_CLOSE, BRACKET_OPEN_EXPR, BRACKET_OPEN_TERM,
    VARIABLE, END, EXIST, ANY, PLUS, MULTIPLY, PREDICATE_NAME, COMMA, EQUAL, HATCH
};

struct token_with_name {
    token type;
    std::string name;

    token_with_name(token type) : type(type) {}

    token_with_name(token type, const std::string &name) : type(type), name(name) {}
};

struct bracket_t {
    size_t pos;
    token type;

    bracket_t(size_t pos, token type) : pos(pos), type(type) {}
};


#endif
