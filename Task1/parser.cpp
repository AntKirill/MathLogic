#include "parser.h"
#include "node.h"
#include <iostream>

using namespace std;

void parser::next_token() noexcept {
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
        shared_ptr<node> new_sub_root(new node());
        new_sub_root->children[0] = sub_root;
        new_sub_root->children[1] = expr();
        new_sub_root->op = IMPL;
        sub_root = new_sub_root;
    }
    while (cur_token == IMPL) {
        shared_ptr<node> right_children(new node());
        right_children->op = IMPL;
        right_children->children[0] = sub_root->children[1];
        sub_root->children[1] = right_children;
        right_children->children[1] = expr();
    }
    return sub_root;
}


shared_ptr<node> parser::disj() noexcept {
    shared_ptr<node> sub_root = conj();
    while (cur_token == OR) {
        next_token();
        shared_ptr<node> new_sub_root(new node());
        new_sub_root->op = OR;
        new_sub_root->children[0] = sub_root;
        new_sub_root->children[1] = conj();
        sub_root = new_sub_root;
    }
    return sub_root;
}


shared_ptr<node> parser::conj() noexcept {
    shared_ptr<node> sub_root = negetion();
    while (cur_token == AND) {
        next_token();
        shared_ptr<node> new_sub_root(new node());
        new_sub_root->op = AND;
        new_sub_root->children[0] = sub_root;
        new_sub_root->children[1] = negetion();
        sub_root = new_sub_root;
    }
    return sub_root;
}



shared_ptr<node> parser::negetion() noexcept {
    if (cur_token == VARIABLE) {
        shared_ptr<node> sub(new node());
        sub->op = VARIABLE;
        sub->expression = cur_variable;
        next_token();
        return sub;
    } else if (cur_token == NOT) {
        next_token();
        shared_ptr<node> sub(new node());
        sub->op = NOT;
        sub->children[0] = negetion();
        return sub;
    } else if (cur_token == BRACKET) {
        shared_ptr<node> sub = expr();
        next_token();
        return sub;
    }
    return nullptr;
}


string parser::to_string(shared_ptr<node> u) noexcept {
    string ul(""), ur("");
    if (u->children[0] != nullptr) {
        ul = to_string(u->children[0]);
    }
    if (u->children[1] != nullptr) {
        ur = to_string(u->children[1]);
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
