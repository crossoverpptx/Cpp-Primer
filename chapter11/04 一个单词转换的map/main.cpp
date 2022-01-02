#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <map>

using std::string;
using std::ifstream;

std::map<string, string> buildMap(ifstream& map_file)
{
    std::map<string, string> trans_map; //保存转换规则
    //for (string key, value; map_file >> key && getline(map_file, value); )
    //    if (value.size() > 1) 
    //        trans_map[key] = value.substr(1).substr(0, value.find_last_not_of(' '));
    //return trans_map;
    string key; //要转换的单词
    string value; //替换后的内容
    //读取第一个单词存入key中，行中剩余内容 存入value
    while (map_file >> key && getline(map_file, value))
        if (value.size() > 1)
            trans_map[key] = value.substr(1);
        else
            throw std::runtime_error("no rule for " + key);
    return trans_map;
}

const string& transform(const string& s, const std::map<string, string>& m)
{
    auto map_it = m.find(s);
    return map_it == m.cend() ? s : map_it->second;
}

void word_transform(ifstream& map_file, ifstream& input)
{
    auto trans_map = buildMap(map_file); 
    //for (string text; getline(input, text); ) {
    //    std::istringstream iss(text);
    //    for (string word; iss >> word; )
    //        std::cout << transform(word, trans_map) << " ";
    //    std::cout << std::endl;
    //}
    string text; //保存输入中的每一行
    while (getline(input, text)) { //读取一行输入
        std::istringstream stream(text); //读取每个单词
        string word;
        bool firstword = true; //控制是否打印空格
        while(stream >> word) {
            if (firstword)
                firstword = false;
            else
                std::cout << " "; //在单词间打印一个空格
            std::cout << transform(word, trans_map); //打印输出
        }
        std::cout << "\n";
    }
}

int main()
{
    ifstream ifs_map("word_transformation_bad.txt"), ifs_content("given_to_transform.txt");
    if (ifs_map && ifs_content) 
        word_transform(ifs_map, ifs_content);
    else 
        std::cerr << "can't find the documents." << std::endl;
}
