#include <iostream>
#include "parser.h"
#include "checker.h"
#include "axioms_and_assumptions.h"

using namespace std;

int main() {
	freopen("good6.in", "r", stdin);
    freopen("out.txt", "w", stdout);
    setlocale(LC_ALL, "Russian");
    time(0);
    string s;
    getline(cin, s);

    string all_fun_is_for;
    parser p;
    axioms_and_assumptions axs(s);

    checker ch(axs);

    cout << s << endl;
    while (getline(cin, s)) {
        ch.check(p.parse(s));
        printf("(%d) %s (%s)\n", ch.get_line_number(), s.data(), ch.get_annotation().data());
    }

    cerr << (clock())/1000000.0 << endl;

    return 0;
}