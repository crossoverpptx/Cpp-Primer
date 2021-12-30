#include <iostream>
#include "Account.h"

int main() {
	std::cout << "Initial rate: " << Account::rate() << '\n';
	Account house("faisal", 345000);
	house.calculate();
	std::cout << "Amount: " << house.debt() << " interest rate: " << house.rate() << '\n';
	Account::rate(0.025);
	house.calculate();
	std::cout << "Amount: " << house.debt() << " interest rate: " << house.rate() << '\n';
	return 0;
}
