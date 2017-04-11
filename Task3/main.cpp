#include <iostream>
#include <generator.h>

using namespace std;


int main() {
    int a, b;
    ifstream fin("input.txt");
    fin >> a >> b;
    generator gen("proof.in");
    gen.generate(a, b);

    return 0;
}