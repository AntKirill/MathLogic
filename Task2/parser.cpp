#include "parser.h"
#include "node.h"
#include <iostream>

using namespace std;

void parser::next_token() noexcept { //TODO update grammar
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
                cur_token = BRACKET;
                break;
            case ')':
                cur_token = BRACKET;
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
        string tmp;
        while ((pos < expression.length()) &&
               (('A' <= expression[pos] && expression[pos] <= 'Z') ||
                ('a' <= expression[pos] && expression[pos] <= 'z') ||
                ('0' <= expression[pos] && expression[pos] <= '9'))) {
            cur_token = VARIABLE;
            tmp += expression[pos];
            pos++;
        }
        if (cur_token != VARIABLE) pos++;
        else cur_variable = tmp;
        return;
    }
    cur_token = END;
}


shared_ptr<node> parser::expr() noexcept {
    next_token();
    shared_ptr<node> sub_root = disj();
    if (cur_token == IMPL) {
        shared_ptr<node> new_sub_root = make_shared<node>();
        new_sub_root->left = sub_root;
        new_sub_root->right = expr();
        new_sub_root->op = IMPL;
        sub_root = new_sub_root;
    }
    while (cur_token == IMPL) {
        shared_ptr<node> right_children = make_shared<node>();
        right_children->op = IMPL;
        right_children->left = sub_root->right;
        sub_root->right = right_children;
        right_children->right = expr();
    }
    return sub_root;
}


shared_ptr<node> parser::disj() noexcept {
    shared_ptr<node> sub_root = conj();
    while (cur_token == OR) {
        next_token();
        shared_ptr<node> new_sub_root = make_shared<node>();
        new_sub_root->op = OR;
        new_sub_root->left = sub_root;
        new_sub_root->right = conj();
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
        new_sub_root->left = sub_root;
        new_sub_root->right = unary();
        sub_root = new_sub_root;
    }
    return sub_root;
}



shared_ptr<node> parser::unary() noexcept {
    if (cur_token == EXIST || cur_token == ANY) {
    	shared_ptr<node> sub = make_shared<node>();
    	sub->op = cur_token;
    	next_token();
    	sub->left = var();
    	next_token();
    	sub->left->left = unary();
    	return sub;
    } else if (cur_token == NOT) {
        next_token();
        shared_ptr<node> sub = make_shared<node>();
        sub->op = NOT;
        sub->left = unary();
        return sub;
    } else if (cur_token == BRACKET) {
        shared_ptr<node> sub = expr();
        next_token(); //takes close bracket
        return sub;
    } else if (cur_token == PREDICATE) { //predicate
    	return predicate(); //teleportes to the world of formal arithmetics from the world of predicates counting
    }
    return nullptr;
}

std::shared_ptr<node> parser::var() noexcept {
	//here cur_token = VARIABLE
	shared_ptr<node> sub = make_shared<node>();
	sub->op = VARIABLE;
	sub->expression = cur_variable;
	return sub;
}

std::shared_ptr<node> parser::predicate() noexcept {
	return nullptr;
}


string parser::to_string(shared_ptr<node> u) noexcept {
    string ul(""), ur("");
    if (u->left != nullptr) {
        ul = to_string(u->left);
    }
    if (u->right != nullptr) {
        ur = to_string(u->right);
    }
    string sign;
    switch (u->op) {
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
        default:
            break;
    }
    if (ur != "") {
        u->expression = "(" + ul + sign + ur + ")";
    } else if (ul != "") {
        u->expression = "(!" + ul + ")";
    }
    return u->expression;
}


shared_ptr<node> parser::parse(string &expression) noexcept {
    this->expression = expression;
    pos = 0;
    shared_ptr<node> root = expr();
    to_string(root);
    return root;
}