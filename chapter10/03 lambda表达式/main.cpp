#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void elimDups(std::vector<std::string>& words) {
	sort(words.begin(), words.end());
	auto end_uniqe = unique(words.begin(), words.end());
	words.erase(end_uniqe, words.end());
}

std::string make_plural(size_t ctr, const std::string& word, const std::string& ending) {
	return (ctr > 1) ? word + ending : word;
}

void biggies(std::vector<std::string>& words, const std::vector<std::string>::size_type sz) {
	elimDups(words); //将words按字典序排序，删除重复单词
	//按长度排序，长度相同的单词维持字典序
	stable_sort(words.begin(), words.end(),
		[](const std::string& s1, const std::string& s2)
		{ return s1.size() < s2.size(); });
	//获取一个迭代器，指向第一个满足size()>=sz的元素
	auto wc = find_if(words.begin(), words.end(),
		[sz](const std::string& s) { return s.size() >= sz; });
	//计算满足size>=sz的元素的数目
	auto count = words.end() - wc;
	std::cout << count << ' ' << make_plural(count, "word", "s")
		<< " of length " << sz << " or longer" << '\n';
	//打印长度大于等于给定值的单词，每个单词后面接一个空格
	for_each(wc, words.end(),
		[](const std::string& s) { std::cout << s << ' '; });
}

int main() {
	std::vector<std::string> words{ "the", "quick", "red", "fox", "jumps",
								    "over", "the", "slow", "red", "turtle" };
	constexpr std::string::size_type size = 5;
	biggies(words, size);
	std::cout << std::endl;
	return 0;
}
