#include <iostream>

struct Numbered {
	Numbered() { ++mysn; }
	Numbered(Numbered& rhs) { mysn = rhs.mysn + 1; }
	unsigned mysn = 0;
};

void f(Numbered s) {
	std::cout << s.mysn << '\n'; 
}

int main()
{
	Numbered a, b = a, c = b;
	f(a);
	f(b);
	f(c);
	return 0;
}

// output
// 2
// 3
// 4