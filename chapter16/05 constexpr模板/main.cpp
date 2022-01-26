#include <iostream>
#include <string>

template <typename T, unsigned N>
constexpr unsigned array_size(T(&arr)[N])
{
	return N;
}

int main()
{
	int a[10];
	double d[7];
	char e[] = "Hello, World!";
	std::cout << array_size(a) << '\n';
	std::cout << array_size(d) << '\n';
	std::cout << array_size(e) << '\n';
	return 0;
}
