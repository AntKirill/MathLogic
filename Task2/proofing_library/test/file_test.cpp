#include <bits/stdc++.h>


std::ifstream finput;

int main() {
	
	const std::string file_name = "1.txt";
	finput.open(file_name.c_str());
	std::string s;
	getline(finput, s);
	std::cout << s << std::endl;
	finput.close();	

	return 0;
}
