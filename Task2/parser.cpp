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
        string tmp("");
        while ((pos < expression.length()) &&
               (('a' <= expression[pos] && expression[pos] <= 'z') ||
                ('0' <= expression[pos] && expression[pos] <= '9'))) {
            cur_token = VARIABLE;
            tmp += expression[pos];
            pos++;
        }
        if (tmp == "") while ((pos < expression.length()) && ('A' <= expression[pos] && expression[pos] <= 'Z')) {
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
    if (cur_token == OR) {
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
    if (cur_token == AND) {
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
    } else if (cur_token == BRACKET_OPEN) {
        shared_ptr<node> sub = expr(); //TODO: Might be not an expression!!!
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
        if (cur_token != BRACKET_OPEN) return sub;
        next_token(); //takes first token of term
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
        sub->op = EQUAL;
        sub->children[0] = term();
        //now cur_token == EQUAL
        next_token();
        sub->children[1] = term();
    }
    return sub;
}

std::shared_ptr<node> parser::term() noexcept {
    shared_ptr<node> sub = add();
    if (cur_token == PLUS) {
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
    if (cur_token == MULTIPLY) {
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
        if (cur_token == BRACKET_OPEN) {
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
    } else if (cur_token == BRACKET_OPEN) {
        sub = term();
        next_token();
    } else {
        sub->children[0] = mult();
        sub->op = HATCH;
        next_token(); //takes token after hatch
    }     
    return sub;
}

static string _to_string(shared_ptr<node> u) {
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
        ans = _to_string(u) + "(" + to_string(u->children[0]) + ")";
    } else if (u->op == VARIABLE && u->children[0] == nullptr && u->children[1] == nullptr) {
        ans = _to_string(u);
    } else if (u->op == PREDICATE_NAME) {
        ans = _to_string(u) + "(";
        if (u->children[0] == nullptr) {
            ans += ")";
            return ans;
        }
        ans += to_string(u->children[0]);
        for (size_t i = 1; i != u->children.size(); i++) {
            if (u->children[i] == nullptr) break;
            ans += "," + to_string(u->children[i]);
        }
        ans += ")";
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


shared_ptr<node> parser::parse(string &expression) noexcept {
    this->expression = expression;
    pos = 0;
    shared_ptr<node> root = expr();
    this->to_string(root);
    return root;
}