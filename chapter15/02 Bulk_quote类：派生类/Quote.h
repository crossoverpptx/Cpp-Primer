#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>

using std::string; using std::endl; using std::ostream;

class Quote {
	friend double print_total(ostream&, const Quote&, size_t);
public:
	Quote() = default;
	Quote(const string& book, double sales_price) : bookNo(book), price(sales_price) {}
	string isbn() const { return bookNo; }
	virtual double net_price(size_t n) const { return n * price; }
	virtual ~Quote() = default;
private:
	string bookNo;
protected:
	double price = 0.0;
};

inline
double print_total(ostream& os, const Quote& item, size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

#endif
