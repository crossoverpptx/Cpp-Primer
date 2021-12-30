#include <iostream>
#include <string>

class Debug {
public:
	constexpr Debug(bool b = true) : hw(b), io(b), other(b) {}
	constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}
	constexpr bool any() { return hw || io || other; }
	void set_io(bool b) { io = b; }
	void set_hw(bool b) { hw = b; }
	void set_other(bool b) { hw = b; }
private:
	bool hw; //硬件错误，而非IO错误
	bool io; //IO错误
	bool other; //其他错误
};

int main() {
	constexpr Debug io_sub(false, true, false);
	if (io_sub.any())
		std::cerr << "print appropriate message\n";
	constexpr Debug prod(false);
	if (prod.any())
		std::cerr << "print an error message\n";
	return 0;
}
