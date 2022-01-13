#include <iostream>
#include <string>

using std::string; using std::ostream; using std::cout; using std::size_t;

class HasPtr {
	friend ostream& print(ostream&, const HasPtr&);
public:
	// string()：构造空的string类对象，既空字符串
	HasPtr(const string& s = string()) : ps(new string(s)), i(0), use(new size_t(1)) { } // constructor
	~HasPtr(); // 析构函数
	HasPtr(const HasPtr& rhs) : ps(rhs.ps), i(rhs.i), use(rhs.use) { ++* use; } // 拷贝构造函数
	HasPtr& operator=(const HasPtr&); // 运算符重载
private:
	string* ps; // ps是一个指针，指向string类型
	int i;
	size_t* use; // use是一个指针，指向size_t类型
};

// 析构函数的定义
HasPtr::~HasPtr()
{
	if (-- * use == 0) {	// 如果引用计数为变0
		delete ps;			// 释放string内存
		delete use;			// 释放计数器内存
	}
}

// 运算符重载的定义
HasPtr&
HasPtr::operator=(const HasPtr& rhs)
{
	++* rhs.use;			// 递增右侧运算对象的引用计数
	if (-- * use == 0) {	// 然后递减本对象的引用计数
		delete ps;			// 如果没有其他用户
		delete use;			// 释放本对象分配的成员
	}
	ps = rhs.ps;			// 将数据从rhs拷贝到本对象
	i = rhs.i;
	use = rhs.use;
	return *this;			// 返回本对象
}

// 友元函数的定义
ostream& print(ostream& os, const HasPtr& p)
{
	os << p.ps << ' ' << *p.ps << ' ' << *p.use;
	return os;
}

void func(const HasPtr& p)
{
	HasPtr temp;
	temp = p;
	cout << "p: ";
	print(cout, p) << '\n';;
	cout << "temp: ";
	print(cout, temp) << '\n';;
}

int main()
{
	cout << "HasPtr str1(\"copy me\"), str2;\n";
	HasPtr str1("copy me"), str2;
	cout << "str1: ";
	print(cout, str1) << '\n';
	cout << "str2: ";
	print(cout, str2) << '\n';

	cout << "\nstr2 = str1;\n";
	str2 = str1;
	cout << "str1: ";
	print(cout, str1) << '\n';
	cout << "str2: ";
	print(cout, str2) << '\n';

	cout << "\nfunc(str1);\n";
	func(str1);

	cout << "\nstr1: ";
	print(cout, str1) << '\n';
	cout << "str2: ";
	print(cout, str2) << '\n';
	return 0;
}
