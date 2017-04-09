#include <iostream>
#include "proofing_library/parser.h"
#include "proofing_library/checker.h"
#include "proofing_library/axioms_and_assumptions.h"
#include "proofing_library/proofer.h"
#include <fstream>

using namespace std;

int main() {
    ifstream fin("proof.in");
    freopen("out.txt", "w", stdout);
    setlocale(LC_ALL, "Russian");
    time(0);
    string s;
    getline(fin, s);

    string all_fun_is_for;
    parser p;

    //cerr << p.parse(s)->expression << endl;
    axioms_and_assumptions axs(s);
    proofer generator(axs.last_assumption);
    checker ch(axs);

    bool ok = true;

    cout << s << endl;
    while (getline(fin, s)) {
        std::shared_ptr<node> root = p.parse(s);
        if (!ch.check(root)) {
            cerr << "ERROR!";
            freopen("out.txt", "w", stdout);
            printf("Вывод некорректен начиная с формулы номер %d\n", ch.get_line_number());
            ok = false;
            break;
        }
        generator.generate(root, ch.get_annotation());
    }

    fin.close();
    fclose(stdout);
    cerr << (clock())/1000000.0 << endl;

    return ok ? 0 : 1;
}