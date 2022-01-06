#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>

using std::vector; using std::string; using std::map; using std::set;
using std::shared_ptr; using std::make_shared;
using std::ifstream; using std::ostream; using std::istringstream;
using std::endl;

class QueryResult; // 为了定义函数query的返回类型，这个定义是必需的

class TextQuery {
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream&);
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> text; // 输入文件
	map<string, shared_ptr<set<line_no>>> words_map; // 每个单词到它所在的行号的集合的映射
};

class QueryResult {
	friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult(shared_ptr<vector<string>> p, shared_ptr<set<TextQuery::line_no>> ln, string w, unsigned n) : text(p), lines(ln), sought(w), count(n) {}
private:
	shared_ptr<vector<string>> text; // 输入文件
	shared_ptr<set<TextQuery::line_no>> lines; // 出现的行号
	string sought; // 查询单词
	unsigned count = 0;
};

// constructors
TextQuery::TextQuery(ifstream& infile) : text(make_shared<vector<string>>()) {
	string line, word;
	for (size_t lineNumber = 1; getline(infile, line); ++lineNumber) { // 对文件中每一行
		text->push_back(line); // 保存此行文本
		istringstream iss(line); // 将行文本分解成单词
		while (iss >> word) { // 对行中每个单词
			auto& lines = words_map[word]; // 如果单词不在words_map中，以之为下标在words_map中添加一项
			if (!lines) // 当我们第一次遇到这个单词时，此指针为空
				lines = make_shared<set<line_no>>(); // 分配一个新的set
			lines->insert(lineNumber); // 将此行号插入set中
		}
	}
}

// members
QueryResult TextQuery::query(const string& s) const {
	static auto notFound = make_shared<set<line_no>>();
	auto pos = words_map.find(s);
	if (pos == words_map.end())
		return { text, notFound, s, 0 };
	unsigned count = 0;
	string word;
	for (auto const& line : *text) {
		istringstream iss(line);
		while (iss >> word)
			if (word == s)
				++count;
	}
	return { text, pos->second, s, count };
}

// non-members
ostream& print(ostream& os, const QueryResult& result) {
	os << result.sought << " occurs " << result.count << ((result.count > 1) ? " times" : " time") << endl;
	for (auto const& n : *result.lines)
		os << "\t(line " << n << ") " << result.text->at(n - 1) << '\n';
	return os;
}

#endif
