#include <iostream>
#include <unordered_map>
#include "generator.h"


using namespace std;


static string pe(const int a) noexcept {
    string ret = "0";
    for (int i = 0; i < a; i++) {
        ret += "'";
    }
    return ret;
}

static void gen_base(ifstream &input, ofstream &output) {
    std::string s;
    while (std::getline(input, s)) {
        output << s << std::endl;
    }
}

namespace loe {
    static void increase(ofstream &output, const int inta, const int i) {
        string pi = pe(i);
        string a = pe(inta);
        string api = "(" + a + "+" + pi + ")'";
        string pai1 = pe(inta + i + 1);
        string pai = pe(inta + i);
        string x = a + "+" + pe(i + 1);

        output << "@a@b(a=b->a'=b')->@b(" + a + "+" + pi + "=b->" + api + "=b')" << endl;
        output << "@b(" + a + "+" + pi + "=b->" + api + "=b')" << endl;
        output << "@b(" + a + "+" + pi + "=b->" + api + "=b')->(" + a + "+" + pi + "=" + pai + "->" + api + "=" + pai1 + ")" << endl;
        output << a + "+" + pi + "=" + pai + "->" + api + "=" + pai1 << endl;
        output << api + "=" + pai1 << endl;
        output << "@a@b(a+b'=(a+b)')->@b(" + a + "+b'=(" + a + "+b)'" + ")" << endl;
        output << "@b(" + a + "+b'=(" + a + "+b)'" + ")" << endl;
        output << "@b(" + a + "+b'=(" + a + "+b)'" + ")->" + x + "=" + api << endl;
        output << x + "=" + api << endl;
        output << "@a@b(b=a->a=b)->@b(b=(" + api + ")->(" + api + ")=b)" << endl;
        output << "@b(b=(" + api + ")->(" + api + ")=b)" << endl;
        output << "@b(b=(" + api + ")->(" + api + ")=b)->((" + x + ")=(" + api + ")->(" + api + ")=(" + x + "))" << endl;
        output << "((" + x + ")=(" + api + ")->(" + api + ")=(" + x + "))" << endl;
        output << "(" + api + ")=(" + x + ")" << endl;
        output << "@a@b@c(a=b->a=c->b=c)->@b@c(" + api + "=b->" + api + "=c->b=c)" << endl;
        output << "@b@c(" + api + "=b->" + api + "=c->b=c)" << endl;
        output << "@b@c(" + api + "=b->" + api + "=c->b=c)->@c(" + api + "=" + pai1 + "->" + api + "=c->" + pai1 + "=c)" << endl;
        output << "@c(" + api + "=" + pai1 + "->" + api + "=c->" + pai1 + "=c)" << endl;
        output << "@c(" + api + "=" + pai1 + "->" + api + "=c->" + pai1 + "=c)->" + api + "=" + pai1 + "->" + api + "=" + x + "->" + pai1 + "=" + x << endl;
        output << api + "=" + pai1 + "->" + api + "=" + x + "->" + pai1 + "=" + x << endl;
        output << api + "=" + x + "->" + pai1 + "=" + x << endl;
        output << pai1 + "=" + x << endl;
        output << "@a@b(b=a->a=b)->@b(b=(" + x + ")->(" + x + ")=b)" << endl;
        output << "@b(b=(" + x + ")->(" + x + ")=b)" << endl;
        output << "@b(b=(" + x + ")->(" + x + ")=b)->((" + pai1 + ")=(" + x + ")->(" + x + ")=(" + pai1 + "))" << endl;
        output << "((" + pai1 + ")=(" + x + ")->(" + x + ")=(" + pai1 + "))" << endl;
        output << "(" + x + ")=(" + pai1 + ")" << endl;
    }
}

namespace mo {
    static void pre_increase(ofstream &output, const std::string &k, const std::string &b) {
        output << "@a@b(!(a=b)->!(a'=b'))->@b(!(" + k + "=b)->!(" + k + "'=b'))" << endl;
        output << "@b(!(" + k + "=b)->!(" + k + "'=b'))" << endl;
        output << "@b(!(" + k + "=b)->!(" + k + "'=b'))->(!(" + k + "=" + b + ")->!(" + k + "'=" + b + "'))" << endl;
        output << "(!(" + k + "=" + b + ")->!(" + k + "'=" + b + "'))" << endl;
        output << "!(" + k + "'=" + b + "')" << endl;
    }

    static void increase(ofstream &output, const std::string &k, const std::string &b) {
        output << "@a@b(a=b->b=a)->@b((" + k + "=b)->(b=" + k + "))" << endl;
        output << "@b((" + k + "=b)->(b=" + k + "))" << endl;
        output << "@b((" + k + "=b)->(b=" + k + "))->((" + k + "=" + b + ")->(" + b + "=" + k + "))" << endl;
        output << "((" + k + "=" + b + ")->(" + b + "=" + k + "))" << endl;
        output << "(" + b + "=" + k + ")" << endl;
        output << "@a@b((a=b)->(a'=b'))->@b((" + b + "=b)->((" + b + ")'=b'))" << endl;
        output << "@b((" + b + "=b)->((" + b + ")'=b'))" << endl;
        output << "@b((" + b + "=b)->((" + b + ")'=b'))->((" + b + "=" + k + ")->((" + b + ")'=" + k + "'))" << endl;
        output << "((" + b + "=" + k + ")->((" + b + ")'=" + k + "'))" << endl;
        output << "((" + b + ")'=" + k + "')" << endl;
        output << "@a@b((a+b)'=(a+b'))->@b((p+b)'=(p+b'))" << endl;
        output << "@b((p+b)'=(p+b'))" << endl;
        output << "@b((p+b)'=(p+b'))->((" + b + ")'=" + b + "')" << endl;
        output << "((" + b + ")'=" + b + "')" << endl;
        output << "@a@b@c((a=b)->(a=c)->(b=c))->@b@c(((" + b + ")'=b)->((" + b + ")'=c)->(b=c))" << endl;
        output << "@b@c(((" + b + ")'=b)->((" + b + ")'=c)->(b=c))" << endl;
        output << "@b@c(((" + b + ")'=b)->((" + b + ")'=c)->(b=c))->@c(((" + b + ")'=" + k + "')->((" + b + ")'=c)->(" + k + "'=c))" << endl;
        output << "@c(((" + b + ")'=" + k + "')->((" + b + ")'=c)->(" + k + "'=c))" << endl;
        output << "@c(((" + b + ")'=" + k + "')->((" + b + ")'=c)->(" + k + "'=c))->(((" + b + ")'=" + k + "')->((" + b + ")'=" + b + "')->(" + k + "'=" + b + "'))" << endl;
        output << "(((" + b + ")'=" + k + "')->((" + b + ")'=" + b + "')->(" + k + "'=" + b + "'))" << endl;
        output << "((" + b + ")'=" + b + "')->(" + k + "'=" + b + "')" << endl;
        output << "(" + k + "'=" + b + "')" << endl;
    }
}

void generator::less_or_equal(const int inta, const int intb) noexcept {
    string a = pe(inta);
    output << "|-?p(" + a + "+p=" + pe(intb) + ")" << endl;
    gen_base(input, output);
    output << "@a(a+0=a)->(" + a + "+0=" + a + ")" << endl;
    output << a + "+0=" + a << endl;

    for (int i = 0; i < intb - inta; i++) {
        loe::increase(output, inta, i);
    }

    string b = pe(intb);
    output << a + "+" + pe(intb - inta) + "=" + b + "->?p(" + a + "+p=" + b + ")" << endl;
    output << "?p(" + a + "+p=" + b + ")" << endl;
}


void generator::more(const int inta, const int intb) noexcept {
    output << "|-@p(!(p+" + pe(inta) + "=" + pe(intb) + "))" << endl;

    gen_base(input, output);
    string k = "(p+" + pe(inta - intb - 1) + ")'";
    output << "@a(!(a'=0))->(!(" + k + "=0))" << endl;
    output << "(!(" + k + "=0))" << endl;

    string z = "0";
    for (int i = 0; i < intb; i++) {
        mo::pre_increase(output, k, z);
        z += "'";
        k += "'";
    }

    k = "(p+" + pe(inta - intb - 1) + ")'";
    string t = "p+" + pe(inta - intb - 1) + "'";

    output << "@a@b((a+b)'=(a+b'))->@b((p+b)'=(p+b'))" << endl;
    output << "@b((p+b)'=(p+b'))" << endl;
    output << "@b((p+b)'=(p+b'))->(" + k + "=" + t + ")" << endl;
    output << "(" + k + "=" + t + ")" << endl;

    for (size_t i = 0; i < intb; i++) {
        mo::increase(output, k, t);
        k += "'";
        t += "'";
    }

    k = "(p+" + pe(inta - intb - 1) + ")";
    for (int i = 0; i < intb + 1; i++) k += "'";
    t = "p+" + pe(inta);
    string b = pe(intb);
    output << "@a@b@c((a=b)->(!(a=c))->(!(b=c)))->@b@c((" + k + "=b)->(!(" + k + "=c))->(!(b=c)))" << endl;
    output << "@b@c((" + k + "=b)->(!(" + k + "=c))->(!(b=c)))" << endl;
    output << "@b@c((" + k + "=b)->(!(" + k + "=c))->(!(b=c)))->@c((" + k + "=" + t + ")->(!(" + k + "=c))->(!(" + t + "=c)))" << endl;
    output << "@c((" + k + "=" + t + ")->(!(" + k + "=c))->(!(" + t + "=c)))" << endl;
    output << "@c((" + k + "=" + t + ")->(!(" + k + "=c))->(!(" + t + "=c)))->((" + k + "=" + t + ")->(!(" + k + "=" + b + "))->(!(" + t + "=" + b + ")))" << endl;
    output << "((" + k + "=" + t + ")->(!(" + k + "=" + b + "))->(!(" + t + "=" + b + ")))" << endl;
    output << "(!(" + k + "=" + b + "))->(!(" + t + "=" + b + "))" << endl;
    output << "!(" + t + "=" + b + ")" << endl;
    output << "!(" + t + "=" + b + ")" << "->((0=0)->(0=0)->(0=0))->" << "!(" + t + "=" + b + ")" << endl;
    output << "((0=0)->(0=0)->(0=0))->" << "!(" + t + "=" + b + ")" << endl;
    output << "((0=0)->(0=0)->(0=0))->@p(" << "!(" + t + "=" + b + "))" << endl;
    output << "@p(" << "!(" + t + "=" + b + "))" << endl;
}