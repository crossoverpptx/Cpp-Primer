#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
	std::vector<int> ivec{ 0, 1, 2, 3, 4, 5, 6, 7, 8 , 9 };
	std::ostream_iterator<int> out_iter(std::cout, " ");
	std::copy(ivec.crbegin(), ivec.crend(), out_iter);
	std::cout << std::endl;
	return 0;
}
