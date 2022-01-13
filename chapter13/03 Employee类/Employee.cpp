#include <iostream>
#include <string>

using std::string; using std::ostream; using std::cout;

class Employee {
	friend ostream& print(ostream&, const Employee&);
public:
	Employee() : id(++number) {}	//default constructor
	Employee(string s) : name(s), id(++number) {}
	Employee& operator=(const Employee&) = delete;
private:
	string name;
	unsigned id = 0;
	static unsigned number;
};

unsigned Employee::number = 0;

ostream& print(ostream& os, const Employee& e)
{
	os << e.name << ' ' << e.id;
	return os;
}

void f(const Employee e)
{
	print(cout, e) << '\n';
}

int main()
{
	Employee a("Ken, Thompson");
	print(cout, a) << '\n';
	Employee b("Torvalds, Linus");
	print(cout, b) << '\n';
	f(a);
	return 0;
}
