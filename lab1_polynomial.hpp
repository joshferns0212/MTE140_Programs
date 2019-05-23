//Joshua Fernandes 20765616
//Eric-Khang Dao 2074442
#ifndef LAB1_POLYNOMIAL_H
#define LAB1_POLYNOMIAL_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Polynomial {
	vector<int> poly_data;
public:
	Polynomial(int A[], int size);
	Polynomial();
	Polynomial(string fileName);
	bool operator==(const Polynomial& target);
	void print();
	Polynomial operator+(const Polynomial& target);
	Polynomial operator-(const Polynomial& target);
	Polynomial operator*(const Polynomial& target);
	Polynomial derivative();
	friend class PolynomialTest;
};

class PolynomialTest {
public:
	bool test_parameterized_constructor();
	bool test_default_constructor();
	bool test_file_constructor();
	bool test_equals();
	bool test_plus();
	bool test_minus();
	bool test_mult();
	bool test_derivative();
	void test_print();
	void run();
};
#endif // LAB1_POLYNOMIAL_H
