#include <iostream>

int main() {
	auto sum = [](const int& a, const int& b) { return a + b; };
	int x{ 5 }, y{ 10 };
	std::cout << sum(x, y) << '\n';
	return 0;
}
