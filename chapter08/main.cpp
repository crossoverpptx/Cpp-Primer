#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ifstream; //从文件读取数据
using std::istringstream; //从string读取数据
using std::ostringstream; //向string写入数据
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::isdigit; //判断一个字符是否是十进制数字

struct PersonInfo {
    string name;
    vector<string> phones;
};

bool valid(const string& str) {
    return isdigit(str[0]);
}

string format(const string& str) {
    return str.substr(0, 3) + "-" + str.substr(3, 3) + "-" + str.substr(6);
}

int main() {
    ifstream ifs("phonenumbers.txt");
    if (!ifs) {
        cerr << "no phone numbers?" << endl;
        return -1;
    }

    string line, word; //分别保存来自输入的一行和单词
    vector<PersonInfo> people; //保存来自输入的所有记录
    istringstream record; //读取的数据的记录
    while (getline(ifs, line)) { //从终端接收一行字符串，并放入字符串line中   
        PersonInfo info;
        record.clear(); //清空record
        record.str(line);
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }

    for (const auto& entry : people) {
        ostringstream formatted, badNums;
        for (const auto& nums : entry.phones) //验证号码
            if (!valid(nums)) 
                badNums << " " << nums;
            else 
                formatted << " " << format(nums);
        if (badNums.str().empty())
            cout << entry.name << " " << formatted.str() << endl;
        else
            cerr << "input error: " << entry.name << " invalid number(s) " << badNums.str() << endl;
    }

    return 0;
}
