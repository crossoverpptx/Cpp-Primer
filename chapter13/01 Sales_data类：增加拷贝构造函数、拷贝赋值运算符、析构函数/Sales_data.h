#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

class Sales_data {
	//为Sales_data的非成员函数所做的友元声明
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::istream& read(std::istream&, Sales_data&);
	friend std::ostream& print(std::ostream&, const Sales_data&);
public:
	//新增的构造函数
	Sales_data() = default;
	Sales_data(const std::string& s) : bookNo(s) {}
	Sales_data(const std::string& s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}
	Sales_data(std::istream&);
	// 与合成的拷贝构造函数等价的拷贝构造函数的声明
	Sales_data(const Sales_data&);
	//新成员：关于Sales_data对象的操作
	std::string isbn() const { return bookNo; }	//常量成员函数
	Sales_data& combine(const Sales_data&);
	// 等价于合成拷贝赋值运算符
	Sales_data& operator=(const Sales_data&);
	// 成员会被自动销毁，除此之外不需要做其他事情
	~Sales_data() {}
private:
	double avg_price() const;
	//数据成员和2.6.1节（Page64）相比没有改变
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

//构造函数的定义
Sales_data::Sales_data(std::istream& is) {
	read(is, *this);
}

// 与Sales_data的合成的拷贝构造函数等价
Sales_data::Sales_data(const Sales_data& orig) :
	bookNo(orig.bookNo),			// 使用string的拷贝构造函数
	units_sold(orig.units_sold),	// 拷贝orig.units_sold
	revenue(orig.revenue)			// 拷贝orig.revenue
	{}								// 空函数体


//Sales_data接口的的非成员组成部分的声明
Sales_data add(const Sales_data&, const Sales_data&);
std::istream& read(std::istream&, Sales_data&);
std::ostream& print(std::ostream&, const Sales_data&);

//Sales_data接口的的非成员组成部分的定义
Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

std::istream& read(std::istream& is, Sales_data& item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

std::ostream& print(std::ostream& os, const Sales_data& item) {
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}

//Sales_data的成员函数的定义
Sales_data& Sales_data::combine(const Sales_data& rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

double Sales_data::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}

// 等价于合成拷贝赋值运算符
Sales_data& Sales_data::operator=(const Sales_data& rhs) {
	bookNo = rhs.bookNo;			// 调用string::operator=
	units_sold = rhs.units_sold;	// 使用内置的int赋值
	revenue = rhs.revenue;			// 使用内置的double赋值
	return *this;					// 返回一个此对象的引用
}

#endif
