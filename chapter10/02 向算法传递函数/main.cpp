#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string>& elimDups(std::vector<std::string>& words) {
    //按字典序排序words，以便查找重复单词
    sort(words.begin(), words.end());
    //unique重排输入范围，使得每个单词只出现一次
    //排列在范围的前部，返回指向不重复区域之后一个位置的迭代器
    auto end_unique = unique(words.begin(), words.end());
    //使用向量操作erase删除重复单词
    words.erase(end_unique, words.end());
    return words;
}

bool isShorter(const std::string& s1, const std::string& s2) {
    return s1.size() < s2.size();
}

int main() {
    std::vector<std::string> words{ "the", "quick", "red", "fox", "jumps",
                                    "over", "the", "slow", "red", "turtle" };
    elimDups(words);
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";

    stable_sort(words.begin(), words.end(), isShorter);
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";

    return 0;
}
