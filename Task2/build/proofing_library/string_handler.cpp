#include "string_handler.h"
#include <stack>

void string_handler::get_token(const std::string &expression) noexcept {
    while (pos < expression.length()) {
        switch (expression[pos]) {
            case ' ':
                pos++;
                continue;
            case '&' :
                cur_token = AND;
                break;
            case '|':
                cur_token = OR;
                break;
            case '!':
                cur_token = NOT;
                break;
            case '(':
                cur_token = BRACKET_OPEN;
                break;
            case ')':
                cur_token = BRACKET_CLOSE;
                break;
            case '@':
                cur_token = ANY;
                break;
            case '?':
                cur_token = EXIST;
                break;
            case '\'':
                cur_token = HATCH;
                break;
            case '*':
                cur_token = MULTIPLY;
                break;
            case '+':
                cur_token = PLUS;
                break;
            case '=':
                cur_token = EQUAL;
                break;
            case ',':
                cur_token = COMMA;
                break;
            default:
                break;
        }
        if (pos < expression.length() - 1) {
            if (expression[pos] == '-' && expression[pos + 1] == '>') {
                cur_token = IMPL;
                pos += 2;
                return;
            }
        }
        std::string tmp("");
        while ((pos < expression.length()) &&
               (('a' <= expression[pos] && expression[pos] <= 'z') ||
                ('0' <= expression[pos] && expression[pos] <= '9'))) {
            cur_token = VARIABLE;
            tmp += expression[pos];
            pos++;
        }
        if (tmp == "") while ((pos < expression.length()) && (('A' <= expression[pos] && expression[pos] <= 'Z')  || 
            ('0' <= expression[pos] && expression[pos] <= '9'))) {
            cur_token = PREDICATE_NAME;
            tmp += expression[pos];
            pos++;
        }
        if (cur_token != VARIABLE && cur_token != PREDICATE_NAME) pos++;
        else cur_variable = tmp;
        return;
    }
    cur_token = END;
}

void string_handler::make_tokens(const std::string &expression) noexcept {
	pos = 0;
    tokens.clear();
    get_token(expression);
    std::stack<string_handler::bracket_t> br;
    while (cur_token != END) {
        if (cur_token == VARIABLE || cur_token == PREDICATE_NAME) tokens.push_back(token_with_name(cur_token, cur_variable));
        else tokens.push_back(token_with_name(cur_token));
        if (cur_token == BRACKET_OPEN) {
            br.push(bracket_t(tokens.size() - 1, BRACKET_OPEN_TERM));
        } else if (cur_token == BRACKET_CLOSE) {
            bracket_t v = br.top();
            br.pop();
            if (v.type == BRACKET_OPEN_EXPR) {
                if (br.size() > 0) br.top().type = BRACKET_OPEN_EXPR;
                tokens[v.pos] = BRACKET_OPEN_EXPR;
            } else tokens[v.pos] = BRACKET_OPEN_TERM;
        } else if (cur_token == PREDICATE_NAME || cur_token == EQUAL || cur_token == ANY || cur_token == EXIST) {
            if (br.size() > 0) br.top().type = BRACKET_OPEN_EXPR;
        }
        get_token(expression);
    }
    tokens.push_back(token_with_name(END));
    pos = 0;
}

void string_handler::next_token() noexcept {
    if (cur_token != END || pos == 0) {
        cur_token = tokens[pos].type;
        cur_variable = tokens[pos].name;
        ++pos;
    }
}