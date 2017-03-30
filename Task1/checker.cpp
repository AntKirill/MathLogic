#include "checker.h"
#include <queue>
#include <memory.h>

using namespace std;

bool checker::check(shared_ptr<node> root) noexcept {
    line++;
    if (check_axioms(root) || check_assumtions(root) || check_MP(root)) {
        all_we_have.insert(make_pair(root->expression, line));
        if (root->op == IMPL) {
            left_impl.insert(make_pair(line, root->children[0]->expression));
            right_impl.insert(make_pair(root->children[1]->expression, line));
        }
        return true;
    }
    annotation_st = "Не доказано";
    return false;
}

string checker::get_annotation() noexcept {
    return annotation_st;
}

int checker::get_line_number() noexcept {
    return line;
}

bool checker::check_MP(shared_ptr<node> root) noexcept {
    string k = root->expression;
    pair<std::unordered_multimap<string, int>::iterator, std::unordered_multimap<string, int>::iterator>
            beg_end = right_impl.equal_range(root->expression);
    for (auto it = beg_end.first; it != beg_end.second; it++) {
        int number_of_line = it->second;
        string left = left_impl.find(number_of_line)->second;
        auto it_number_second_line = all_we_have.find(left);
        if (it_number_second_line != all_we_have.end()) {
            annotation_st = "M.P. " + to_string(it_number_second_line->second) + " " + to_string(number_of_line);
            return true;
        }
    }
    return false;
}

bool checker::check_assumtions(shared_ptr<node> root) noexcept {
    string k = root->expression;
    for (size_t i = 0; i < assumptions.size(); i++) {
        if (assumptions[i] == k) {
            annotation_st = "Предп. " + to_string(i + 1);
            return true;
        }
    }
    return false;
}

bool checker::check_axioms(shared_ptr<node> root) noexcept {
    for (size_t i = 0; i < axioms.size(); i++) {
        if (cur_axiom(axioms[i], root)) {
            annotation_st = "Сх. акс. " + to_string(i + 1);
            return true;
        }
    }
    return false;
}

bool checker::cur_axiom(shared_ptr<node> u, shared_ptr<node> root) noexcept {
    unordered_map<char, string> exprax_to_expr;
    queue<shared_ptr<node>> qax, q;
    qax.push(u);
    q.push(root);
    while (!qax.empty()) {
        shared_ptr<node> vax = qax.front();
        qax.pop();
        shared_ptr<node> v = q.front();
        q.pop();
        if (check_nodes_structure(vax, v)) {
            if (vax->op != v->op) return false;
            if (vax->op == VARIABLE) {
                if (!check_mapped_expr(exprax_to_expr, vax->expression[0], v->expression)) return false;
            }
            if (vax->children[0] != nullptr) {
                qax.push(vax->children[0]);
                q.push(v->children[0]);
            }
            if (vax->children[1] != nullptr) {
                qax.push(vax->children[1]);
                q.push(v->children[1]);
            }
        } else {
            if (vax->children[0] == nullptr && vax->children[1] == nullptr) {
                if (!check_mapped_expr(exprax_to_expr, vax->expression[0], v->expression)) return false;
            } else return false;
        }
    }
    return true;
}

bool checker::check_mapped_expr(unordered_map<char, string> &m, char u, string &v) noexcept {
    if (m.count(u)) {
        return (m[u] == v);
    }
    m[u] = v;
    return true;
}


bool checker::check_nodes_structure(shared_ptr<node> v, shared_ptr<node> u) noexcept {
    if (v->children[0] == nullptr && (v->children[1] == nullptr)) {
        return u->children[0] == nullptr && u->children[1] == nullptr;
    }
    if (v->children[0] == nullptr && v->children[1] != nullptr) {
        return u->children[0] == nullptr && u->children[1] != nullptr;
    }
    if (v->children[0] != nullptr && v->children[1] == nullptr) {
        return u->children[0] != nullptr && u->children[1] == nullptr;
    }
    if (v->children[0] != nullptr && v->children[1] != nullptr) {
        return u->children[0] != nullptr && u->children[1] != nullptr;
    }
    return false;
}
