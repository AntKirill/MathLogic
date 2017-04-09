#include "checker.h"
#include "string_handler.h"
#include <queue>
#include <memory.h>

using namespace std;

using node_ptr = std::shared_ptr<node>;

static inline bool check_nodes_structure(node_ptr &v, node_ptr &u) noexcept {
    if (v->children.size() != u->children.size()) return false;
    for (size_t i = 0; i < v->children.size(); i++) {
        if (v->children[i] == nullptr && u->children[i] != nullptr ||
            u->children[i] == nullptr && v->children[i] != nullptr) {
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

/**
 * Updates the term that is substituted in phi instead of killed_variable and mark substituted nodes in u.
 * @param var_of_phi - variable for substitute condidate->expression in it
 * @param var_of_phi might be @param killed_variable to update term, if no, it returns false
 */
static inline bool
update_term(string &var_of_phi, string &term, node_ptr &Q_ptr, node_ptr &condidate, string &killed_variable) noexcept {
    if (var_of_phi == killed_variable) {
        if (Q_ptr == nullptr) {
            Q_ptr = condidate;
            condidate->substituted = true;
            return true;
        } else {
            if (Q_ptr->expression == condidate->expression) {
                condidate->substituted = true;
                return true;
            } else return false;
        }
    } else {
        return var_of_phi == condidate->expression;
    }
}

/**
 * Put all variables from tree with root in v to unordered_set variables.
 */
static void get_all_variables(node_ptr &v, unordered_set<string> &variables) noexcept {
    for (size_t i = 0; i < v->children.size() && v->children[i] != nullptr; i++) {
        get_all_variables(v->children[i], variables);
    }
    if (v->op == VARIABLE) variables.insert(string_handler::get_variable_name(v->expression));
}

/**
 * Checks that after substitution of our term to phi there will be no free variable for substituted term that will become busy.
 * @param v - node_ptr on tree with expression for phi with substituted term
 * @param variables - all variables from substituted to phi term
 * @param busy - busy variables in v
 * @param parent_quantifier - flag which is true if and only if parent of current node is quantifier
 */
static bool check_free_for_subst(node_ptr &v, const unordered_set<string> &variables, unordered_set<string> &busy,
                                 bool parent_quantifier = false) noexcept {
    if (v->substituted) {
        for (auto var: variables) {
            if (busy.count(var)) return false; //not free for substitution!
        }
    }
    string name = string_handler::get_variable_name(v->expression);
    bool pq = false;
    if (v->op == VARIABLE && parent_quantifier) {
        busy.insert(name);
        pq = true;
    }
    parent_quantifier = false;
    if (v->op == ANY || v->op == EXIST) parent_quantifier = true;
    for (size_t i = 0; i < v->children.size() && v->children[i] != nullptr; i++) {
        if (!check_free_for_subst(v->children[i], variables, busy, parent_quantifier)) return false;
    }
    if (v->op == VARIABLE && pq) {
        busy.erase(name);
    }
    return true;
}

/**
 * Check if in phi there was busy variable in which we have substituted new term.
 * If there is quantifier for @param old_term and new term is achievable from it the only on case to not return false is when old_term == new_term.
 * In that case function unmarks node in @param v and continuing. Otherwise it returns false.
 */
static bool substituted_for_free_entry(node_ptr v, const string &new_term, const string &old_term,
                                       bool quantifier_for_old_term = false) noexcept {
    if (v->op == ANY || v->op == EXIST) {
        string name = string_handler::get_variable_name(v->children[0]->expression);
        if (name == old_term) quantifier_for_old_term = true;
    }
    if (v->expression == new_term && quantifier_for_old_term) {
        if (old_term != new_term) return false;
        else v->substituted = false;
    }
    for (size_t i = 0; i < v->children.size() && v->children[i] != nullptr; i++) {
        if (!substituted_for_free_entry(v->children[i], new_term, old_term, quantifier_for_old_term)) return false;
    }
    return true;
}

/**
 * Finds such term that after substitution in @param phi instead of free @param killed_variable, will be true that @param phi equals to @param u.
 * If such term exists function returns true and node_ptr on term is in @param Q_ptr.
 * If such term doesn't exist function return false.
 * If function returns true than every substituted node in @param u will be marked us substituted.
 * @param phi is expression with busy variable (@param killed_variable), @param u is expression where @param Q_ptr is probably substituted instead of
 * variable (@param killed_variable).
 */
static bool find_substituted_term(node_ptr &phi, node_ptr &u, node_ptr &Q_ptr, string &killed_variable) noexcept {
    string term;
    queue<node_ptr> q_phi, q;
    q_phi.push(phi);
    q.push(u);
    while (!q_phi.empty()) {
        node_ptr v_phi = q_phi.front();
        q_phi.pop();
        node_ptr v = q.front();
        q.pop();
        if (check_nodes_structure(v_phi, v)) {
            if (v_phi->op != v->op) return false;
            if (v_phi->op == PREDICATE_NAME) {
                string name_v = string_handler::get_predicate_name(v->expression);
                string name_phi = string_handler::get_predicate_name(v_phi->expression);
                if (name_v != name_phi) return false;
            }
            if (v_phi->children[0] == nullptr && v_phi->children[1] == nullptr && v->children.size() == 2) {
                if (!update_term(v_phi->expression, term, Q_ptr, v, killed_variable)) return false;
            }
            for (size_t i = 0; i < v_phi->children.size() && v_phi->children[i] != nullptr; i++) {
                q_phi.push(v_phi->children[i]);
                q.push(v->children[i]);
            }
        } else {
            if (v_phi->children[0] == nullptr && v_phi->children[1] == nullptr && v->children.size() == 2) {
                if (!update_term(v_phi->expression, term, Q_ptr, v, killed_variable)) return false;
            } else return false;
        }
    }

    return Q_ptr == nullptr ? true : substituted_for_free_entry(u, Q_ptr->expression, killed_variable);
}

/**
 * Helps to check this: @/? a PHI(a) -> PHI(a:=Q). Determins if term Q is free for substitution to PHI instead of a.
 */
static inline bool check_subtrees(node_ptr &phi, node_ptr &u, string &&killed_variable) noexcept {
    node_ptr Q_ptr;
    if (!find_substituted_term(phi, u, Q_ptr, killed_variable)) return false;
    if (Q_ptr == nullptr) return true;
    unordered_set<string> variables;
    get_all_variables(Q_ptr, variables);
    unordered_set<string> busy;
    return check_free_for_subst(u, variables, busy);
}

/**
 * Checks if current line is 11th axiom.
 * v - is root of tree for current line.
 */
static inline bool check_11_axiom(node_ptr &v) noexcept {
    if (v->op == IMPL && v->children[0]->op == ANY && v->children[0]->children[0]->op == VARIABLE) {
        return check_subtrees(v->children[0]->children[0]->children[0], v->children[1],
                              string_handler::get_variable_name(v->children[0]->children[0]->expression));
    }
    return false;
}

static inline bool check_12_axiom(node_ptr &v) noexcept {
    if (v->op == IMPL && v->children[1]->op == EXIST && v->children[1]->children[0]->op == VARIABLE) {
        return check_subtrees(v->children[1]->children[0]->children[0], v->children[0],
                              string_handler::get_variable_name(v->children[1]->children[0]->expression));
    }
    return false;
}

/**
 * Checks if current line is current axiom.
 * u - is root of tree for current axiom.
 * root - is root of tree for current line.
 */
static bool cur_axiom(node_ptr &u, node_ptr &root) noexcept {
    unordered_map<string, string> exprax_to_expr;
    queue<node_ptr> qax, q;
    qax.push(u);
    q.push(root);
    while (!qax.empty()) {
        node_ptr vax = qax.front();
        qax.pop();
        node_ptr v = q.front();
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

/**
 * Checks if variable entries free in formula.
 * Retrun true if there is a free entry and false if all enties are busy or no entry at all.
 */
static bool check_free_entry(node_ptr &v, string &x, bool quantifier_for_x = false) noexcept {
    if (v->op == ANY || v->op == EXIST) {
        string name = string_handler::get_variable_name(v->children[0]->expression);
        if (name == x) {
            quantifier_for_x = true;
        }
    }
    if (v->children[0] == nullptr) {
        return x == v->expression && !quantifier_for_x;
    }
    for (size_t i = 0; i < v->children.size() && v->children[i] != nullptr; i++) {
        if (check_free_entry(v->children[i], x, quantifier_for_x)) return true;
    }
    return false;
}

static bool check_induction(node_ptr root) noexcept {
    if (root->op == IMPL &&
        root->children[0]->op == AND &&
        root->children[0]->children[1]->op == ANY &&
        root->children[0]->children[1]->children[0]->children[0]->op == IMPL) {
        node_ptr psi = root->children[1];
        string variable = string_handler::get_variable_name(root->children[0]->children[1]->children[0]->expression);
        if (check_free_entry(psi, variable)) {
            node_ptr Q_ptr;
            if (!find_substituted_term(psi, root->children[0]->children[0], Q_ptr, variable)) return false;
            if (Q_ptr->expression != "0") return false;
            Q_ptr = nullptr;
            if (!find_substituted_term(psi, root->children[0]->children[1]->children[0]->children[0]->children[1],
                                       Q_ptr, variable))
                return false;
            string good_substitution = "(" + variable + ")'";
            return (Q_ptr->expression == good_substitution);
        }
    }
    return false;
}

bool checker::check(node_ptr &root) noexcept {
    line++;
    if (check_axioms(root) || check_assumtions(root) || check_deduction_rules(root)) {
        all_we_have.insert(make_pair(root->expression, line));
        if (root->op == IMPL) {
            left_impl.insert(make_pair(line, root->children[0]->expression));
            right_impl.insert(make_pair(root->children[1]->expression, line));
        }
        return true;
    }
    annotation_st = annotation(NOT_PROOFED);
    return false;
}


bool checker::check_MP(node_ptr &root) noexcept {
    string k = root->expression;
    pair<unordered_multimap<string, int>::iterator, unordered_multimap<string, int>::iterator>
            beg_end = right_impl.equal_range(root->expression);
    for (auto it = beg_end.first; it != beg_end.second; it++) {
        int number_of_line = it->second;
        string left = left_impl.find(number_of_line)->second;
        auto it_number_second_line = all_we_have.find(left);
        if (it_number_second_line != all_we_have.end()) {
            //annotation_st = "M.P. " + to_string(it_number_second_line->second) + " " + to_string(number_of_line);
            annotation_st = annotation(MP, left, left + "->" + root->expression);
            return true;
        }
    }
    return false;
}

bool checker::check_FA_rules(std::shared_ptr<node> &root) noexcept {

    //deduction rule for any
    if (root->op == IMPL && root->children[1]->op == ANY) {
        string name = string_handler::get_variable_name(root->children[1]->children[0]->expression);
        if (!free_variables_from_last_assumption.count(name) &&
            !check_free_entry(root->children[0], name)) {
            string expr = "(" + root->children[0]->expression + "->" +
                          root->children[1]->children[0]->children[0]->expression + ")";
            if (all_we_have.count(expr)) {
                annotation_st = annotation(DEDUCTION_ANY,
                                           expr);//"Правило вывода для любого по строке " + to_string(all_we_have[expr]);
                return true;
            }
        }
    }

    //deduction rule for exist
    if (root->op == IMPL && root->children[0]->op == EXIST) {
        string name = string_handler::get_variable_name(root->children[0]->children[0]->expression);
        if (!free_variables_from_last_assumption.count(name) &&
            !check_free_entry(root->children[1], name)) {
            string expr = "(" + root->children[0]->children[0]->children[0]->expression + "->" +
                          root->children[1]->expression + ")";
            if (all_we_have.count(expr)) {
                annotation_st = annotation(DEDUCTION_EXIST,
                                           expr);//"Правило вывода для некоторого по строке " + to_string(all_we_have[expr]);
                return true;
            }
        }
    }

    return false;
}

bool checker::check_deduction_rules(std::shared_ptr<node> &root) noexcept {
    return check_MP(root) || check_FA_rules(root);
}


bool checker::check_assumtions(node_ptr &root) noexcept {
    string k = root->expression;
    for (size_t i = 0; i < assumptions.size(); i++) {
        if (assumptions[i] == k) {
            annotation_st = annotation(ASSUMP);//"Предп. " + to_string(i + 1);
            return true;
        }
    }
    return false;
}

bool checker::check_axioms(node_ptr &root) noexcept {
    for (size_t i = 0; i < axioms.size(); i++) {
        if (cur_axiom(axioms[i], root)) {
            if (i + 1 >= 11) i += 2;
            annotation_st = annotation(i + 1);// "Сх. акс. " + to_string(i + 1);
            return true;
        }
    }
    if (check_11_axiom(root)) {
        annotation_st = annotation(11);//"Сх. акс. 11";
        return true;
    }
    if (check_12_axiom(root)) {
        annotation_st = annotation(12);//"Сх. акс. 12";
        return true;
    }
    if (check_induction(root)) {
        annotation_st = annotation(AXIOM_INDUCTION);
        return true;
    }
    return false;
}