#include <iostream>
#include <string>
#include <utility>

using std::ostream; using std::string; using std::cout; using std::endl;

class Quote {
	friend double print_total(ostream&, const Quote&, size_t);
public:
	Quote() = default;
	Quote(const Quote& b) : bookNo(b.bookNo), price(b.price)
	{
		cout << "Quote(const Quote &)\n";
	}
	Quote(const string& book, double sales_price) : bookNo(book), price(sales_price) {}
	Quote(Quote&& b) noexcept : bookNo(b.bookNo), price(b.price)
	{
		cout << "Quote(Quote &&b)\n";
	}
	Quote& operator=(const Quote&);
	Quote& operator=(Quote&&) noexcept;
	string isbn() const { return bookNo; }
	virtual double net_price(size_t n) const { return n * price; }
	virtual ~Quote() { cout << "~Quote()\n"; };
private:
	string bookNo;
protected:
	double price = 0.0;
};

Quote&
Quote::operator=(const Quote& rhs)
{
	cout << "Quote& operator=(const Quote &)\n";
	auto newdata = rhs;
	bookNo = rhs.bookNo;
	price = rhs.price;
	return *this;
}

Quote&
Quote::operator=(Quote&& rhs) noexcept
{
	if (this != &rhs) {
		bookNo = rhs.bookNo;
		price = rhs.price;
	}
	cout << "Quote& operator(const Quote &&)\n";
	return *this;
}

double print_total(ostream& os, const Quote& item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

class Disc_quote : public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const Disc_quote& dq) : Quote(dq), quantity(dq.quantity), discount(dq.discount)
	{
		std::cout << "Disc_quote(const Disc_quote &)\n";
	}
	Disc_quote(Disc_quote&& dq) noexcept : Quote(std::move(dq)), quantity(dq.quantity), discount(dq.discount)
	{
		std::cout << "Disc_quote(Disc_quote &&)\n";
	}
	Disc_quote& operator=(const Disc_quote&);
	Disc_quote& operator=(Disc_quote&&) noexcept;
	Disc_quote(const string& book, double price, size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) {}
	~Disc_quote() { cout << "~Disc_quote()\n"; };
	double net_price(size_t) const = 0; // pure virtual function

protected:
	size_t quantity = 0;
	double discount = 0.0;
};

Disc_quote&
Disc_quote::operator=(const Disc_quote& rhs)
{
	Quote::operator=(rhs);
	// There's no need for guarding against self-assignemnt, for
	// direct initialization, including copy-initialization,
	// of Dis_quote objects is not possible.
	quantity = rhs.quantity;
	discount = rhs.discount;
	cout << "Disc_quote& operator=(const Disc_quote &)\n";
	return *this;
}

Disc_quote&
Disc_quote::operator=(Disc_quote&& rhs) noexcept
{
	if (this != &rhs) {    // good practice, but not necessary
		Quote::operator=(std::move(rhs));
		quantity = rhs.quantity;
		discount = rhs.discount;
	}
	cout << "Disc_quote& operator=(const Disc_quote &&)\n";
	return *this;
}

class Bulk_quote : public Disc_quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const Bulk_quote& bq) : Disc_quote(bq)
	{
		cout << "Bulk_quote(const Bulk_quote &)\n";
	}
	Bulk_quote(Bulk_quote&& bq) noexcept : Disc_quote(std::move(bq))
	{
		cout << "Bulk_quote(Bulk_quote &&)\n";
	}
	Bulk_quote& operator=(const Bulk_quote&);
	Bulk_quote& operator=(Bulk_quote&&) noexcept;
	Bulk_quote(const string& book, double price, size_t qty, double disc) : Disc_quote(book, price, qty, disc) {}
	~Bulk_quote() { cout << "~Bulk_quote()\n"; };
	double net_price(size_t) const override;
};

Bulk_quote&
Bulk_quote::operator=(const Bulk_quote& rhs)
{
	Disc_quote::operator=(rhs);
	cout << "Bulk_quote& operator=(const Bulk_quote &)\n";
	return *this;
}

Bulk_quote&
Bulk_quote::operator=(Bulk_quote&& rhs) noexcept
{
	if (this != &rhs)
		Disc_quote::operator=(std::move(rhs));
	cout << "Bulk_quote& operator=(const Bulk_quote &&)\n";
	return *this;
}

double
Bulk_quote::net_price(size_t cnt) const
{
	if (cnt >= quantity)
		return cnt * (1 - discount) * price;
	return cnt * price;
}

int main()
{
	Bulk_quote bulk("9-999-99999-9", 34.99, 10, 0.5);
	Bulk_quote bulk2(bulk);
	Bulk_quote bulk3(std::move(bulk));

	Bulk_quote bulk4("3-333-33333-3", 25.49, 2, 0.5);
	bulk2 = bulk4;
	bulk2 = std::move(bulk4);

	print_total(cout, bulk, 10);
	print_total(cout, bulk2, 10);
	return 0;
}
