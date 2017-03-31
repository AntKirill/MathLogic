#include <bits/stdc++.h>
#include "parser.h"

typedef long long ll;

using namespace std;

const int N = (int)1e6, M = (int)1e6, Inf = (int)2e9;
int n, m, k;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    string s;
	parser p;
	while (getline(cin, s))	{
		cout << p.parse(s)->expression << endl;
	}
    return 0;
}