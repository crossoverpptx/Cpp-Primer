#pragma once

#include <string>
#include <memory>
#include <vector>
#include <stdexcept>

class StrBlob {
public:
	using size_type = std::vector<std::string>::size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	// add and remove elements
	void push_back(const std::string& t) { data->push_back(t); }
	void pop_back();
	// element access
	std::string& front();
	std::string& back();
	std::string& front() const;
	std::string& back() const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	// throws msg if data[i] isn't valid
	void check(size_type i, const std::string& msg) const;
};

// constructors
StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_t i, const std::string& msg) const
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}

void StrBlob::pop_back()
{
	check(0, "back on empty StrBlob");
	data->pop_back();
}

std::string& StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

std::string& StrBlob::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}

std::string& StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

std::string& StrBlob::back() const
{
	check(0, "back on empty StrBlob");
	return data->back();
}
