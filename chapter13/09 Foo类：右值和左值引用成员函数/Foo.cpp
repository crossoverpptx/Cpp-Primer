#include <algorithm>
#include <iostream>
#include <vector>

using std::vector; using std::ostream; using std::cout;

class Foo {
public:
	Foo() = default;
	Foo(const vector<int>& v) : data(v) { }		// 构造函数
	Foo(const Foo& rhs) : data(rhs.data) { }	// 拷贝构造函数
	Foo& operator=(const Foo&)&;	// 只能向可修改的左值赋值
	Foo sorted()&&;					// 可用于可改变的右值
	Foo sorted() const&;			// 可用于任何类型的Foo
	vector<int>::iterator begin() { return data.begin(); }
	vector<int>::iterator end() { return data.end(); }
	vector<int>::const_iterator begin() const { return data.cbegin(); }
	vector<int>::const_iterator end() const { return data.cend(); }
public:
	vector<int> data;
};

Foo&
Foo::operator=(const Foo& rhs)&
{
	auto newdata = rhs.data;
	data = newdata;
	return *this;
}

// 本对象是const或是一个左值，哪种情况我们都不能对其进行原址排序
Foo
Foo::sorted() const&
{
	cout << "sorted() const &\n";
	return Foo(*this).sorted(); // ret is rvalue
}

// 本对象为右值，因此可以原址排序
Foo
Foo::sorted()&&
{
	cout << "sorted() &&\n";
	sort(data.begin(), data.end());
	return *this;
}

Foo retVal()
{
	Foo ret({ 453, 345, 3, 123, 56, 73 });
	return ret;
}

Foo& retFoo()
{
	static Foo ret({ 453, 345, 3, 123, 56, 73 });
	return ret;
}

ostream& print(ostream& os, const Foo& someFoo)
{
	for (const auto& elem : someFoo)
		os << elem << ' ';
	return os;
}

int main()
{
	print(cout, retVal().sorted()) << '\n';
	print(cout, retFoo().sorted()) << '\n';
	return 0;
}
