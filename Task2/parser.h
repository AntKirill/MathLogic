#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include "node.h"
#include "token.h"

class parser {
	std::string expression;

    size_t pos;

    token cur_token;

    std::string cur_variable;

    void next_token() noexcept;

    std::shared_ptr<node> expr() noexcept;

    std::shared_ptr<node> disj() noexcept;

    std::shared_ptr<node> conj() noexcept;

    std::shared_ptr<node> unary() noexcept;

    std::shared_ptr<node> var() noexcept;

    std::shared_ptr<node> predicate() noexcept;

    std::shared_ptr<node> term() noexcept;

    std::shared_ptr<node> add() noexcept;

    std::shared_ptr<node> mult() noexcept;
    
    std::string to_string(std::shared_ptr<node> u) noexcept;

public:
	std::shared_ptr<node> parse(std::string &expression) noexcept;	
};

#endif