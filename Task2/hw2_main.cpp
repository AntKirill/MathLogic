#include <iostream>
#include "proofing_library/parser.h"
#include "proofing_library/checker.h"
#include "proofing_library/axioms_and_assumptions.h"

using namespace std;

int main() {
    freopen("proof.in", "r", stdin);
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
        std::shared_ptr<node> root = p.parse(s);
        if (!ch.check(root)) {
            cerr << "ERROR!";
            break;
        }
    }

    fclose(stdin);
    fclose(stdout);
    cerr << (clock())/1000000.0 << endl;

    return 0;
}