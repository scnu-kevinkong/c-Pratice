#pragma once
#include <iostream>
class Stock {
	int value_;
public:
	void printValue() const {
		std::cout << value_ << std::endl;
	};
	Stock();
	Stock(int value);
};
Stock::Stock() {
	value_ = 0;
}
Stock::Stock(int value) {
	value_ = value;
}