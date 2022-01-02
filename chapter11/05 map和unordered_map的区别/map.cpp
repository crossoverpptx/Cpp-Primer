#include <iostream>
#include <string>
#include <map>

int main()
{
	std::map<std::string, size_t> word_count;
	std::string word;
	while (std::cin >> word)
		++word_count[word];
	for (const auto &w : word_count)
		std::cout << w.first << " occurs " << w.second
			      << ((w.second > 1) ? " times" : "time") << '\n';
	return 0;
}
