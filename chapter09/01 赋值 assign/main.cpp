#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

int main() {
    std::list<const char*> cslist({ "C-style", "char", "string" });
    std::vector<std::string> svec;
    svec.assign(cslist.cbegin(), cslist.cend());
    for (const auto& elem : svec)
        std::cout << elem << std::endl;

    return 0;
}
