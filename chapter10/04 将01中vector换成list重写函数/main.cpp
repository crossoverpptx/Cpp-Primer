#include <iostream>
#include <string>
#include <list>

int main() {
	std::list<std::string> words{ "the", "quick", "red", "fox", "jumps",
								  "over", "the", "slow", "red", "turtle" };
	words.sort();
	words.unique();
	for (const auto& elem : words)
		std::cout << elem << ' ';
	std::cout << std::endl;
	return 0;
}
