#include <iostream>
#include <string>

using std::string; using std::ostream; using std::cout; using std::endl; using std::cerr;

class Quote {
	friend double print_total(ostream&, const Quote&, size_t);
public:
	Quote() = default;
	Quote(const string& book, double sales_price) : bookNo(book), price(sales_price) { }
	virtual ~Quote() = default;
	string isbn() const { return bookNo; }
	virtual double net_price(size_t n) const { return n * price; }
	virtual ostream& debug(ostream& os = cout, const string& step = ", ") const;
private:
	string bookNo;
protected:
	double price = 0.0;
};

inline
double print_total(ostream& os, const Quote& item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn()
		<< " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

inline
ostream&
Quote::debug(ostream& os, const string& step) const
{
	return os << "{\'bookNo\': \'" << bookNo << "\'" << step << "\'price\': \'" << price << "\'}";
};

class Bulk_quote : public Quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const string&, double, size_t, double);
	double net_price(size_t) const override;
	ostream& debug(ostream& os = cout, const string& step = ", ") const override;
private:
	size_t min_qty = 0;
	double discount = 0.0;
};

inline
Bulk_quote::Bulk_quote(const string& book, double p, size_t qty, double disc) :
	Quote(book, p), min_qty(qty), discount(disc) {}

inline
double
Bulk_quote::net_price(size_t cnt) const
{
	if (cnt >= min_qty)
		return cnt * (1 - discount) * price;
	return cnt * price;
}

inline
ostream&
Bulk_quote::debug(ostream& os, const string& step) const
{
	return Quote::debug(os, step) << '\b' << step << "\'min_qt\': " << min_qty
		<< step << "\'discount\': " << discount << '}';
}

class Limited_discount : public Quote {
public:
	Limited_discount() = default;
	Limited_discount(const string& book, double p, size_t lim, double disc)
		: Quote(book, p), limit(lim), discount(disc) { }
	double net_price(size_t) const override;
	ostream& debug(ostream& os = cout, const string& step = ", ") const override;
private:
	size_t limit = 0;
	double discount = 0.0;
};

inline
double
Limited_discount::net_price(size_t cnt) const
{
	if (cnt > limit) {
		auto discounted = limit * (1 - discount) * price;
		auto regularPrice = (cnt - limit) * price;
		return discounted + regularPrice;
	}
	return cnt * (1 - discount) * price;
}

inline
ostream&
Limited_discount::debug(ostream& os, const string& step) const
{
	return Quote::debug(os, step) << '\b' << step << "\'limit\': " << limit
		<< step << "\'discount\': " << discount << '}';
}

int main()
{
	Quote base("2-222222-2", 25);
	base.debug() << '\n';
	Bulk_quote derived1("3-333333-3", 35, 10, 0.25);
	derived1.debug(cout) << '\n';
	Limited_discount derived2("4-444444-4", 42, 10, 0.5);
	derived2.debug(cerr) << '\n';
	return 0;
}
