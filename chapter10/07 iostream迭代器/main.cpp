#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

int main() {
    std::ifstream ifs("book.txt");
    std::istream_iterator<std::string> in(ifs), eof;
    std::vector<std::string> vec;
    std::copy(in, eof, back_inserter(vec));

    // output
    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
