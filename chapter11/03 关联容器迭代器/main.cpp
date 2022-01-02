#include <iostream>
#include <map>

int main() {
	std::map<std::string, int> rgb{ {"red", 0}, {"green", 0}, {"blue", 0} };
	auto it_map = rgb.begin();
	it_map++->second = 8;     // set red to 8
	it_map++->second = 10;    // set green to 10
	it_map->second = 4;       // set blue tyo 4
	for (it_map = rgb.begin(); it_map != rgb.cend(); ++it_map)
		std::cout << it_map->first << ' ' << it_map->second << '\n'; //输出会发现blue是8，green是10，red是4，原因set是有序容器？
	return 0;
}