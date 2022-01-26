#include <iostream>

template <typename T, unsigned N>
T* begin(T(&arr)[N])
{
	return arr;
}

template <typename T, unsigned N>
T* end(T(&arr)[N])
{
	return &arr[N];
}

int main()
{
	int a[5] = { 1, 2, 3, 4 , 5 };
	double d[] = { 9.3, 2.4, 36.90, 4.22 , 22.7 };

	auto a_first = begin(a);
	auto a_last = end(a);
	std::cout << *a_first << ' ';
	std::cout << *(a_last - 1) << '\n';

	auto d_first = begin(d);
	auto d_last = end(d);
	std::cout << *d_first << ' ';
	std::cout << *(d_last - 1) << '\n';
	return 0;
}
