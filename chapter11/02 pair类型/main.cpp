#include <iostream>
#include <string>
#include <vector>
#include <utility>

int main()
{
	std::vector<std::pair<std::string, int>> strInt;
	std::string word;
	int number;

	while (std::cin >> word && std::cin >> number)
		strInt.push_back({ word, number });  // push list initialized pairs

	for (const auto& pair : strInt)
		std::cout << pair.first << ' ' << pair.second << '\n';
	return 0;
}
