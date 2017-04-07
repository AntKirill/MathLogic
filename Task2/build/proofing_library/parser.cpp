#include "parser.h"
#include "node.h"
#include <iostream>
#include <stack>

using namespace std;

shared_ptr<node> parser::expr() noexcept {
    next_token();
    shared_ptr<node> sub_root = disj();
    if (cur_token == IMPL) {
        shared_ptr<node> new_sub_root = make_shared<node>();
        new_sub_root->children[0] = sub_root;
        new_sub_root->children[1] = expr();
        new_sub_root->op = IMPL;
        sub_root = new_sub_root;
    }
    return sub_root;
}

shared_ptr<node> parser::disj() noexcept {
    shared_ptr<node> sub_root = conj();
    while (cur_token == OR) {
        next_token();
        shared_ptr<node> new_sub_root = make_shared<node>();
        new_sub_root->op = OR;
        new_sub_root->children[0] = sub_root;
        new_sub_root->children[1] = conj();
        sub_root = new_sub_root;
    }
    return sub_root;
}

shared_ptr<node> parser::conj() noexcept {
    shared_ptr<node> sub_root = unary();
    while (cur_token == AND) {
        next_token();
        shared_ptr<node> new_sub_root = make_shared<node>();
        new_sub_root->op = AND;
        new_sub_root->children[0] = sub_root;
        new_sub_root->children[1] = unary();
        sub_root = new_sub_root;
    }
    return sub_root;
}

shared_ptr<node> parser::unary() noexcept {
    if (cur_token == EXIST || cur_token == ANY) {
    	shared_ptr<node> sub = make_shared<node>();
    	sub->op = cur_token;
    	next_token();
    	sub->children[0] = var();
    	sub->children[0]->children[0] = unary();
    	return sub;
    } else if (cur_token == NOT) {
        next_token();
        shared_ptr<node> sub = make_shared<node>();
        sub->op = NOT;
        sub->children[0] = unary();
        return sub;
    } else if (cur_token == BRACKET_OPEN_EXPR) {
        shared_ptr<node> sub = expr();
        next_token(); //takes close bracket
        return sub;
    } else { //predicate
    	return predicate(); //teleportes to the world of formal arithmetics from the world of abstract predicates counting
    }
}

std::shared_ptr<node> parser::var() noexcept {
	//here cur_token has to be VARIABLE
	shared_ptr<node> sub = make_shared<node>();
	sub->op = VARIABLE;
	sub->expression = cur_variable;
    next_token();
	return sub;
}

std::shared_ptr<node> parser::predicate() noexcept {
    shared_ptr<node> sub = make_shared<node>();
    if (cur_token == PREDICATE_NAME) {
        sub->op = PREDICATE_NAME;
        sub->expression = cur_variable;
        next_token(); //open bracket
        if (cur_token != BRACKET_OPEN_TERM) return sub;
        next_token(); //takes first tokens of term
        if (cur_token == BRACKET_CLOSE) return sub;
        sub->children[0] = term();
        int cnt = 1;
        while (cur_token == COMMA) {
            next_token();
            if (cnt >= 2) sub->children.push_back(term());
            else sub->children[cnt++] = term();
        }
        next_token();
    } else {
        sub = term();
        if (cur_token == EQUAL) {
            shared_ptr<node> new_sub_root = make_shared<node>();
            new_sub_root->op = EQUAL;
            new_sub_root->children[0] = sub;
            next_token();
            new_sub_root->children[1] = term();
            sub = new_sub_root;
        }
    }
    return sub;
}

std::shared_ptr<node> parser::term() noexcept {
    shared_ptr<node> sub = add();
    while (cur_token == PLUS) {
        next_token();
        shared_ptr<node> new_sub_root = make_shared<node>();
        new_sub_root->op = PLUS;
        new_sub_root->children[0] = sub;
        new_sub_root->children[1] = term();
        sub = new_sub_root;
    }
    return sub;
}

std::shared_ptr<node> parser::add() noexcept {
    shared_ptr<node> sub = mult();
    while (cur_token == MULTIPLY) {
        next_token();
        shared_ptr<node> new_sub_root = make_shared<node>();
        new_sub_root->op = MULTIPLY;
        new_sub_root->children[0] = sub;
        new_sub_root->children[1] = add();
        sub = new_sub_root;        
    }
    return sub;
}

std::shared_ptr<node> parser::mult() noexcept {
    shared_ptr<node> sub = make_shared<node>();
    if (cur_token == VARIABLE) {
        sub = var();
        if (cur_token == BRACKET_OPEN_TERM) {
            next_token();
            sub->children[0] = term();
            int cnt = 1;
            while (cur_token == COMMA) {
                next_token();
                if (cnt >= 2) sub->children.push_back(term());
                else sub->children[cnt++] = term();
            }
            next_token();
        }
    } else if (cur_token == BRACKET_OPEN_TERM) {
        next_token();
        sub = term();
        next_token();
    } else {
        sub->children[0] = mult();
        sub->op = HATCH;
        next_token();

    }
    while (cur_token == HATCH) {
        shared_ptr<node> new_sub = make_shared<node>();
        new_sub->op = HATCH;
        new_sub->children[0] = sub;
        sub = new_sub;
        next_token();
    }
    return sub;
}

static string _to_string(shared_ptr<node> u) noexcept {
    string sign("");
    token t = u->op;
    switch (t) {
        case IMPL:
            sign = "->";
            break;
        case OR:
            sign = "|";
            break;
        case AND:
            sign = "&";
            break;
        case NOT:
            sign = "!";
            break;
        case COMMA:
            sign = ",";
            break;
        case EXIST:
            sign = "?";
            break;
        case ANY:
            sign = "@";
            break;
        case PLUS:
            sign = "+";
            break;
        case MULTIPLY:
            sign = "*";
            break;
        case VARIABLE:
            sign = u->expression;
            break;
        case  PREDICATE_NAME:
            sign = u->expression;
            break;
        case HATCH:
            sign = "'";
            break;
        case EQUAL:
            sign = "=";
            break;
        default:
            break;
    }
    return sign;
}

string parser::to_string(shared_ptr<node> &u) noexcept {
    string ans("");
    if (u->op == ANY || u->op == EXIST) { //must have one child
        ans = _to_string(u) + to_string(u->children[0]);
    } else if (u->op == VARIABLE && u->children[0] != nullptr ) {
        ans = _to_string(u) + "(";
        ans += to_string(u->children[0]);
        for (size_t i = 1; i < u->children.size(); i++) {
            if (u->children[i] == nullptr) break;
            ans += "," + to_string(u->children[i]);
        }
        ans += ")";
    } else if (u->op == VARIABLE && u->children[0] == nullptr && u->children[1] == nullptr) {
        ans = _to_string(u);
    } else if (u->op == PREDICATE_NAME) {
        ans = "(" + _to_string(u) + "(";
        if (u->children[0] == nullptr) {
            ans += "))";
            return ans;
        }
        ans += to_string(u->children[0]);
        for (size_t i = 1; i != u->children.size(); i++) {
            if (u->children[i] == nullptr) break;
            ans += "," + to_string(u->children[i]);
        }
        ans += "))";
    } else if (u->op == NOT) {
        ans = "(!" + to_string(u->children[0]) + ")";
    } else if (u->op == HATCH) {
        ans = "(" + to_string(u->children[0]) + ")'";
    } else {
        ans = "(" + to_string(u->children[0]) + _to_string(u) + to_string(u->children[1]) + ")";
    }
    u->expression = ans;
    return ans;
}


shared_ptr<node> parser::parse(const string &expression) noexcept {
    make_tokens(expression);
    shared_ptr<node> root = expr();
    this->to_string(root);
    return root;
}