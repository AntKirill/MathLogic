#include <proofer.h>
#include "proofing_library/parser.h"
#include "proofing_library/checker.h"

using namespace std;

int main(int argc, char** argv) {
    string filename(*(argv + 2));
    string prefix = "../tests/";
    filename = prefix + filename;
	freopen(filename.c_str(), "r", stdin);
    freopen("out.txt", "w", stdout);
    //freopen("good6.in", "r", stdin);
    time(0);
    string s;
    getline(cin, s);

    string all_fun_is_for;
    parser p;
    axioms_and_assumptions axs(s);
    proofer generator(axs.last_assumption);
    checker ch(axs);

    bool ok = true;
    while (getline(cin, s)) {
        std::shared_ptr<node> root = p.parse(s);
        if (!ch.check(root)) {
            cerr << "ERROR! (" + to_string(ch.get_line_number()) + ") ";
            ok = false;
            freopen("out.txt", "w", stdout);
            printf("Вывод некорректен начиная с формулы номер %d\n", ch.get_line_number());
            break;
        }
        generator.generate(root, ch.get_annotation());
    }

    if (ok) cerr << "OK! ";

    fclose(stdin);
    fclose(stdout);
    cerr << "time for " << filename << " is: " << (clock())/1000000.0 << endl;

}