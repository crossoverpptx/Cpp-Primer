#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
public:
	Account() = default;
	Account(std::string name) : owner(name) {}
	Account(std::string name, double amt) : owner(name), amount(amt) {}
	void calculate() { amount += amount * interestRate; }
	double debt() const { return amount; }
	static double rate() { return interestRate; }
	static void rate(double);
private:
	std::string owner;
	double amount;
	static double interestRate;
	static double initRate();
};

double Account::interestRate = initRate();

double Account::initRate()
{
	return 0.03;  // 3 percent
}

void Account::rate(double newRate) {
	interestRate = newRate;
}

#endif
