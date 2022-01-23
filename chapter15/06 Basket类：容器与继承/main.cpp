#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <utility>

using std::ostream; using std::string; using std::endl; using std::cout; using std::shared_ptr; using std::multiset;

class Quote {
	friend double print_total(ostream&, const Quote&, size_t);
public:
	Quote() = default;
	Quote(const string& book, double sales_price) : bookNo(book), price(sales_price) {}
	string isbn() const { return bookNo; }
	virtual Quote* clone() const& { return new Quote(*this); }
	virtual Quote* clone() const&& { return new Quote(std::move(*this)); }
	virtual double net_price(size_t n) const { return n * price; }
	virtual ~Quote() {};
private:
	string bookNo;
protected:
	double price = 0.0;
};

double print_total(ostream& os, const Quote& item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn()
		<< " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

class Disc_quote : public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const string& book, double price, size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) {}
	double net_price(size_t) const = 0; // pure virtual function
protected:
	size_t quantity = 0;
	double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
	// default constructor is synthesized
	using Disc_quote::Disc_quote; // inherit constructors
	double net_price(size_t) const override;
	Bulk_quote* clone() const& override { return new Bulk_quote(*this); }
	Bulk_quote* clone() const&& override
	{
		return new Bulk_quote(std::move(*this));
	}
};

double
Bulk_quote::net_price(size_t cnt) const
{
	if (cnt >= quantity)
		return cnt * (1 - discount) * price;
	return cnt * price;
}

class Basket {
public:
	void add_item(const Quote& sale)
	{
		items.insert(shared_ptr<Quote>(sale.clone()));
	}
	void add_item(const Quote&& sale)
	{
		items.insert(shared_ptr<Quote>(std::move(sale).clone()));
	}
	double total_receipt(ostream&) const;
private:
	static bool compare(const shared_ptr<Quote>& lhs, const shared_ptr<Quote>& rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
};

double
Basket::total_receipt(ostream& os) const
{
	double sum = 0;
	for (auto iter = items.begin(); iter != items.end(); iter = items.upper_bound(*iter))
		sum += print_total(os, **iter, items.count(*iter));
	os << "Total Sale: " << sum << '\n';
	return sum;
}

int main()
{
	Basket bsk;
	bsk.add_item({ "1-111-11111-1", 25 });
	bsk.add_item(Bulk_quote("2-222-22222-2", 25, 2, .5));
	bsk.add_item(Bulk_quote("2-222-22222-2", 25, 2, .5));
	bsk.total_receipt(cout);
	return 0;
}
