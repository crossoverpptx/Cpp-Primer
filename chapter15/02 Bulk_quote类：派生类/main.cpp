#include "Bulk_quote.h"

using std::cout;

int main() {
	Quote item1("1-111-11111-1", 25);
	Bulk_quote item2("2-222-22222-2", 25, 5, 0.25);
	print_total(cout, item1, 10); // full price
	print_total(cout, item2, 10); // discounted

	return 0;
}
