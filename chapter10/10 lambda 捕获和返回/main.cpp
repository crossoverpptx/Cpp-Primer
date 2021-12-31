#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	int x{ 10 };
	auto f = [&x]() -> bool
	{ if (x) { --x; return false; }
	else return true; };
	while (!f())
		std::cout << x << '\n';
	return 0;
}
