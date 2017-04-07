#ifndef STRING_HANDLER_H
#define STRING_HANDLER_H

#include "tokens.h"
#include <vector>
#include <iostream>

struct string_handler {
	
    void get_token(const std::string &expression) noexcept;

	void make_tokens(const std::string &expression) noexcept;

	void next_token() noexcept;

	string_handler() noexcept : pos(0) {}

private:
	
	struct token_with_name {
	    token type;
	    std::string name;

	    token_with_name(token type) noexcept : type(type) {}

	    token_with_name(token type, const std::string &name) noexcept : type(type), name(name) {}
	};

	struct bracket_t {
	    size_t pos;
	    token type;

	    bracket_t(size_t pos, token type) noexcept : pos(pos), type(type) {}
	};

protected:

	std::vector<token_with_name> tokens;

    size_t pos;

    token cur_token;

    std::string cur_variable;
};

#endif 