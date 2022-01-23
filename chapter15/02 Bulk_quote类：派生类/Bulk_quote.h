#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H

#include "Quote.h"

class Bulk_quote : public Quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const string&, double, size_t, double);
	double net_price(size_t) const override;	// 派生类中的虚函数
private:
	size_t min_qty = 0;
	double discount = 0.0;
};

inline
Bulk_quote::Bulk_quote(const string& book, double p, size_t qty, double disc) :
	Quote(book, p), min_qty(qty), discount(disc) {}

inline
double
Bulk_quote::net_price(size_t cnt) const {
	if (cnt >= min_qty)
		return cnt * (1 - discount) * price;
	return cnt * price;
}

#endif
