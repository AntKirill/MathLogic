#include "checker.h"
#include <queue>
#include <memory.h>

using namespace std;

using node_ptr = std::shared_ptr<node>;

static inline bool check_nodes_structure(shared_ptr<node> &v, shared_ptr<node> &u) noexcept {
    if (v->children.size() != u->children.size()) return false;
    for (size_t i = 0; i < v->children.size(); i++) {
        if (v->children[i] == nullptr && u->children[i] != nullptr ||
            u->children[i] == nullptr && v->children[i] != nullptr ) {
            return false;
        }
    }
    return true;
}

static inline bool check_mapped_expr(unordered_map<string, string> &m, const string &u, const string &v) noexcept {
    if (m.count(u)) {
        return (m[u] == v);
    }
    m[u] = v;
    return true;
}

static inline bool update_term(string &var_of_phi, const string &term, node_ptr &Q_ptr, node_ptr &condidate) noexcept {
    if (var_of_phi != "" && var_of_phi != term) return false;
    var_of_phi = term;
    Q_ptr = condidate;

    condidate->substituted = true;

    return true;
}

/*
// Put all variables from tree with root in v to unoredred_set variables.
*/
static void get_all_variables(node_ptr &v, unordered_set<string> &variables) noexcept {
    for (size_t i = 0; i < v->children.size() && v->children[i] != nullptr; i++) {
        get_all_variables(v->children[i], variables);
    }
    if (v->op == VARIABLE) variables.insert(v->expression);
}

static bool check_free(node_ptr &v, const unordered_set<string> &variables, unordered_set<string> &busy,
    bool parent_quantifier = false) noexcept {
    if (v->substituted) {
        for (auto var: variables) {
            if (busy.count(var)) return false; //not free for substitution!
        }
    }
    if (v->op == VARIABLE && parent_quantifier) {
        busy.insert(v->expression);
    }
    parent_quantifier = false;
    if (v->op == ANY || v->op == EXIST) parent_quantifier = true;
    for (size_t i = 0; i < v->children.size() && v->children[i] != nullptr; i++) {
        if (!check_free(v->children[i], variables, busy, parent_quantifier)) return false;
    }
    if (v->op == VARIABLE && parent_quantifier) {
        busy.erase(v->expression);
    }
    return true;
}

static bool find_substituted_term(node_ptr &phi, node_ptr &u, node_ptr &Q_ptr) noexcept {
    string var_of_phi;
    string term;    
    queue<node_ptr> q_phi, q;
    q_phi.push(phi);
    q.push(u);
    while (!q_phi.empty()) {
        node_ptr v_phi = q_phi.front();
        q_phi.pop();
        node_ptr v = q.front();
        q.pop();
        /*
         * TODO: if v_phi and v are functions or predicates then check there names
         * if they are predicates and names are different return false, but if names are the same then go further
         * if they are functions and names are different we found term condidate, else go further
         */
        if (check_nodes_structure(v_phi, v)) {
            if (v_phi->op != v->op) return false;
            if (v_phi->op == VARIABLE) {
                if (!update_term(var_of_phi, term, Q_ptr, v)) return false;
            }
            for (size_t i = 0; i < v_phi->children.size() && v_phi->children[i] != nullptr; i++) {
                q_phi.push(v_phi->children[i]);
                q.push(v->children[i]);
            }
        } else {
            if (v_phi->children[0] == nullptr && v_phi->children[1] == nullptr && v->children.size() == 2) 
                if (!update_term(var_of_phi, term, Q_ptr, v)) return false;
            else return false;
        }
    }
    return true;
} 

/*
//Helps to check this: @/? a PHI(a) -> PHI(a:=Q). Determins if term Q is free for substitution to PHI instead of a.
*/
static inline bool check_subtrees(node_ptr &phi, node_ptr &u) noexcept {
    node_ptr Q_ptr;
    if (!find_substituted_term(phi, u, Q_ptr)) return false;
    unordered_set<string> variables;
    get_all_variables(Q_ptr, variables);
    unordered_set<string> busy;
    return check_free(u, variables, busy);
}

/*
// Checks if current line is 11th axiom.
// v - is root of tree for current line.
*/
static inline bool check_11_axiom(std::shared_ptr<node> &v) noexcept {
    if (v->op == IMPL && v->children[0]->op == ANY && v->children[0]->children[0]->op == VARIABLE) {
        return check_subtrees(v->children[0]->children[0]->children[0], v->children[1]);
    }
    return false;
}

static inline bool check_12_axiom(std::shared_ptr<node> &v) noexcept {
    if (v->op == IMPL && v->children[1]->op == EXIST && v->children[1]->children[0]->op == VARIABLE) {
        return check_subtrees(v->children[1]->children[0]->children[0], v->children[0]);
    }
    return false;
}

/*
// Checks if current line is current axiom.
// u - is root of tree for current axiom.
// root - is root of tree for current line.
*/
static bool cur_axiom(shared_ptr<node> &u, shared_ptr<node> &root) noexcept {
    unordered_map<string, string> exprax_to_expr;
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
                if (!check_mapped_expr(exprax_to_expr, vax->expression, v->expression)) return false;
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
                if (!check_mapped_expr(exprax_to_expr, vax->expression, v->expression)) return false;
            } else return false;
        }
    }
    return true;
}

bool checker::check(shared_ptr<node> &&root) noexcept {
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

bool checker::check_MP(shared_ptr<node> &root) noexcept {
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

bool checker::check_assumtions(shared_ptr<node> &root) noexcept {
    string k = root->expression;
    for (size_t i = 0; i < assumptions.size(); i++) {
        if (assumptions[i] == k) {
            annotation_st = "Предп. " + to_string(i + 1);
            return true;
        }
    }
    return false;
}

bool checker::check_axioms(shared_ptr<node> &root) noexcept {
    for (size_t i = 0; i < axioms.size(); i++) {
        if (cur_axiom(axioms[i], root)) {
            if (i + 1 >= 11) i+=2;
            annotation_st = "Сх. акс. " + to_string(i + 1);
            return true;
        }
    }
    if (check_11_axiom(root)) {
        annotation_st = "Сх. акс. 11";
        return true;
    } else if (check_12_axiom(root)) {
        annotation_st = "Сх. акс. 12";
        return true;
    }
    return false;
}