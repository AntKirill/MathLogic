#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include "node.h"
#include "token.h"

class parser {
    size_t pos;

    token cur_token;

    std::string cur_variable;

    void get_token(const std::string &expression) noexcept;

	void next_token() noexcept;

    std::shared_ptr<node> expr() noexcept;

    std::shared_ptr<node> disj() noexcept;

    std::shared_ptr<node> conj() noexcept;

    std::shared_ptr<node> unary() noexcept;

    std::shared_ptr<node> var() noexcept;

    std::shared_ptr<node> predicate() noexcept;

    std::shared_ptr<node> term() noexcept; //add | term PLUS add

    std::shared_ptr<node> add() noexcept; //mult | add MULT mult

    std::shared_ptr<node> mult() noexcept; //var term | var | ( term ) | 0 | mult

	std::string to_string(std::shared_ptr<node> &u) noexcept;

	std::vector<token_with_name> tokens;

	void make_tokens(const std::string &expression) noexcept ;

public:
	std::shared_ptr<node> parse(const std::string &expression) noexcept;
};

#endif