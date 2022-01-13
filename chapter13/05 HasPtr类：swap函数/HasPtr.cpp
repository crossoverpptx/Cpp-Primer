#include <iostream>
#include <string>

using std::string; using std::ostream; using std::cout;

class HasPtr {
	friend void swap(HasPtr&, HasPtr&);
	friend ostream& print(ostream&, const HasPtr&);
public:
	HasPtr(const string& s = string()) : ps(new string(s)), i(0) {}
	~HasPtr() { delete ps; }
	HasPtr(const HasPtr& rhs) : ps(new string(*rhs.ps)), i(rhs.i) {}
	HasPtr& operator=(HasPtr&);
private:
	string* ps;
	int i;
};

HasPtr&
HasPtr::operator=(HasPtr& rhs)
{
	auto newp = new string(*rhs.ps);
	delete ps;
	ps = newp;
	i = rhs.i;
	return *this;
}

inline void swap(HasPtr& lhs, HasPtr& rhs)
{
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
	std::cout << "swap(HasPtr &lhs, HasPtr &rhs)\n";
}

ostream& print(ostream& os, const HasPtr& p)
{
	os << p.ps << ' ' << *p.ps << ' ' << p.i;
	return os;
}

int main()
{
	HasPtr str1("lhs string");
	HasPtr str2("rhs string");

	cout << "str1: ";
	print(cout, str1) << '\n';
	cout << "str2: ";
	print(cout, str2) << '\n';

	swap(str1, str2);

	cout << "str1: ";
	print(cout, str1) << '\n';
	cout << "str2: ";
	print(cout, str2) << '\n';
	return 0;
}
