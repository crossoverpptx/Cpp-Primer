#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<char> cvec{ 'I', '\'', 'm', ' ', 'c', 'h', 'a', 'r', ' ',
                            'v', 'e', 'c', 't', 'o', 'r' };
    std::string s1(&cvec[0], cvec.size());
    std::string s2(cvec.begin(), cvec.end());

    std::cout << "s1: ";
    for (const auto& elem : s1) {
        std::cout << elem;
    }
    std::cout << std::endl;    
    
    std::cout << "s2: ";
    for (const auto& elem : s2) {
        std::cout << elem;
    }
    std::cout << std::endl;

    return 0;
}
