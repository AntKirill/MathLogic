#include <iostream>
#include "parser.h"
#include "checker.h"

using namespace std;

std::vector<std::string> string_axioms = {"a->b->a",
                                "(a->b)->(a->b->c)->(a->c)",
                                "a->b->a&b",
                                "a&b->a",
                                "a&b->b",
                                "a->a|b",
                                "b->a|b",
                                "(a->c)->(b->c)->(a|b->c)",
                                "(a->b)->(a->!b)->!a",
                                "!!a->a"};

std::vector<std::string> assumptions;

void assumptions_go(parser &p, std::string &s, std::string &all_fun_is_for) {
    std::string tmp("");
    s += ' ';
    for (size_t i = 0; i < s.length() - 1; i++) {
        if (s[i] == ' ') {
            continue;
        } else if (s[i] != ',' && !(s[i] == '|' && s[i + 1] == '-')) {
            tmp += s[i];
        } else {
            if (tmp != "") {
                assumptions.push_back(p.parse(tmp)->expression);
                tmp = "";
            }
            if ((s[i] == '|' && s[i + 1] == '-')) i++;
        }
    }
    if (tmp != "") {
        all_fun_is_for = p.parse(tmp)->expression;
    }
}

int main() {
	freopen("good6.in", "r", stdin);
    freopen("out.txt", "w", stdout);
    setlocale(LC_ALL, "Russian");
    time(0);
    clock_t t_beg = clock();
    string s;
    getline(cin, s);
    parser p;
    string all_fun_is_for;
    assumptions_go(p, s, all_fun_is_for);

    checker ch(string_axioms, assumptions);

    cout << s << endl;
    while (getline(cin, s)) {
        ch.check(p.parse(s));
        printf("(%d) %s (%s)\n", ch.get_line_number(), s.data(), ch.get_annotation().data());
    }

    clock_t t_end = clock();
    //cout << t_end - t_beg;


    return 0;

    return 0;
}
