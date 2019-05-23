//Joshua Fernandes 20765616
//Eric-Khang Dao 20774442
#include "lab1_polynomial.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;


Polynomial::Polynomial(int A[], int size) { //Parameterized Constructor
	poly_data.resize(size);

	for(int i=0; i < size; ++i) {
		poly_data[i] = A[i];
	}
}

Polynomial::Polynomial() { //Default Constructor/Random Constructor
	srand(time(NULL));
	int size = rand() % 1001;
	poly_data.resize(size);

	for(int i=0; i < size; ++i) {
		poly_data[i] = rand() % 2001-1000;
	}

}

Polynomial::Polynomial(string fileName) { //File name Constructor
	ifstream fin(fileName.c_str());
	int size = 0;
	fin >> size;
	poly_data.resize(size);

	for(int i=0; i < size; ++i) {
		fin >> poly_data[i];bool test_equals();
	}
}

bool Polynomial::operator==(const Polynomial& target) { //Overload ==
	if(poly_data.size() != target.poly_data.size())
		return false;

	for(int i=0; i < poly_data.size(); ++i) {
		if(poly_data[i] != target.poly_data[i])
			return false;
	}

	return true;
}


void Polynomial::print() { //Print Polynomial
	if((poly_data.size() == 1 && poly_data[0] == 0) ||poly_data.size() == 0) {
		cout << "0";
	}
	else {
		for (int i = poly_data.size() - 1; i >= 0; --i) {
			if (poly_data[i] != 0) {
				if (i == poly_data.size() - 1) {
					cout << poly_data[i] << "x^" << i;
				} else {
					if (poly_data[i] > 0) {
						cout << " + ";
					} else {
						cout << " - ";
					}
					cout << abs(poly_data[i]) << "x^" << i;
				}
			}
		}
	}
	cout << endl;
}


Polynomial Polynomial::operator+(const Polynomial& target) { //Overload +, adds polynomials
	int size = 0;
	if(poly_data.size() > target.poly_data.size())
		size = poly_data.size();
	else
		size = target.poly_data.size();

	int poly_array[size] = {};

	for(int i=0; i < poly_data.size(); ++i) {
		poly_array[i] += poly_data[i];
	}

	for(int i=0; i < target.poly_data.size(); ++i) {
		poly_array[i] += target.poly_data[i];
	}
	return Polynomial(poly_array, size);
}

Polynomial Polynomial::operator-(const Polynomial& target) { //Overload -, subtracts polynomials
	int size = 0;
	if(poly_data.size() > target.poly_data.size())
		size = poly_data.size();
	else
		size = target.poly_data.size();

	int poly_array[size] = {};

	for(int i=0; i < poly_data.size(); ++i) {
		poly_array[i] = poly_data[i];
	}

	for(int i=0; i < target.poly_data.size(); ++i) {
		poly_array[i] -= target.poly_data[i];
	}

	return Polynomial(poly_array, size);
}

Polynomial Polynomial::operator*(const Polynomial& target) { //Overload *, Multiplies polynomials
	int size = poly_data.size() + target.poly_data.size() - 1;
	int poly_array[size] = {};

	for(int i=0; i < poly_data.size(); ++i) {
		for(int j=0; j < target.poly_data.size(); ++j) {
			poly_array[i+j] += poly_data[i] * target.poly_data[j];
		}
	}

	return Polynomial(poly_array, size);
}

Polynomial Polynomial::derivative() { //calculates derivative
	if(poly_data.size() == 0)
		return Polynomial(int{}, 0);
	int size = poly_data.size()-1;
	int poly_array[size] = {};

	for(int i=1; i < size + 1; ++i) {
		poly_array[i-1] = poly_data[i] * i;
	}

	return Polynomial(poly_array, size);
}



bool PolynomialTest::test_parameterized_constructor() {
	int poly_array[] = {3, 0, 6, 7};
	int poly_empty[] = {};
	int poly_neg_coeff[] = {-3. -6, -2, -5};
	Polynomial poly(poly_array, 4);
	Polynomial poly2(poly_empty, 0);
	Polynomial poly3(poly_neg_coeff, 4);

	for(int i=0; i < poly.poly_data.size(); ++i) { //Test correct coefficients
		if(poly.poly_data[i] != poly_array[i])
			return false;
	}

	if(poly2.poly_data.size() != 0) //Test empty polynomial
		return false;

	for(int i=0; i < poly3.poly_data.size(); ++i) { //Test correct coefficients
		if(poly3.poly_data[i] != poly_neg_coeff[i])
			return false;
	}

	return true;
}

bool PolynomialTest::test_default_constructor() {
	Polynomial poly;
	if(poly.poly_data.size() > 1000 || poly.poly_data.size() < 0)
		return false;

	for(int i=0; i < poly.poly_data.size(); ++i) {
		if(poly.poly_data[i] > 1000 || poly.poly_data[i] < -1000)
			return false;
	}

	return true;
}

bool PolynomialTest::test_file_constructor() {
	Polynomial poly_file("file.txt");
	int poly_array[] = {3, 5, 4};

	if(poly_file.poly_data.size() != 3)
		return false;

	Polynomial poly1(poly_array, 3);
	Polynomial poly2(poly_array, 3);

	return (poly1 == poly2 ? true : false); //change

	for(int i=0; i < poly_file.poly_data.size(); ++i) { //Test correct coefficients
		if(poly_file.poly_data[i] != poly_array[i])
			return false;
	}

	return true;
}

bool PolynomialTest::test_equals() {
	int poly_array[] = {1, 2, 3};
	Polynomial poly1(poly_array, 3);
	Polynomial poly2(poly_array, 3);

	return (poly1 == poly2 ? true : false);
}

bool PolynomialTest::test_plus() {
	int poly_array[] = {1, 2, 3};
	int poly_array2[] = {2, 4, 6};
	Polynomial poly1(poly_array, 3);
	Polynomial poly2(poly_array, 3);

	Polynomial poly3 = poly1 + poly2;

	for(int i=0; i < poly3.poly_data.size(); ++i) {
		if(poly3.poly_data[i] != poly_array2[i])
			return false;
	}

	return true;
}

bool PolynomialTest::test_minus() {
	int poly_array[] = {2, 4, 6};
	int poly_array2[] = {1, 2, 3};
	Polynomial poly1(poly_array, 3);
	Polynomial poly2(poly_array2, 3);

	Polynomial poly3 = poly1 - poly2;

	for(int i=0; i < poly3.poly_data.size(); ++i) {
		if(poly3.poly_data[i] != poly_array2[i])
			return false;
	}

	return true;
}

bool PolynomialTest::test_mult() {
	int poly_array[] = {1, 1};
	int poly_array2[] = {-1, 1};
	int poly_array3[] = {-1, 0, 1};
	Polynomial poly1(poly_array, 2);
	Polynomial poly2(poly_array2, 2);

	Polynomial poly3 = poly1 * poly2;

	for(int i=0; i < poly3.poly_data.size(); ++i) {
		if(poly3.poly_data[i] != poly_array3[i])
			return false;
	}

	return true;
}

bool PolynomialTest::test_derivative() {
	int poly_array[] = {2, 3, 4};
	int poly_array2[] = {3, 8};
	int poly_array3[] = {};
	Polynomial poly1(poly_array, 3);
	Polynomial poly3(poly_array3, 0);
	Polynomial poly2;

	poly2 = poly1.derivative();

	for(int i=0; i < poly2.poly_data.size(); ++i) {
		if(poly2.poly_data[i] != poly_array2[i])
			return false;
	}

	Polynomial poly4 = poly3.derivative();

	if(poly4.poly_data.size() != 0)
		return false;

	return true;
}

void PolynomialTest::test_print() {
	int poly_array[] = {2, 3, 4};
	Polynomial poly(poly_array, 3);

	poly.print();
}

void PolynomialTest::run() {
	if(test_default_constructor())
		cout << "Test default constructor Passed" << endl;
	else
		cout << "Test default constructor Failed" << endl;

	if(test_parameterized_constructor())
		cout << "Test parameterized constructor Passed" << endl;
	else
		cout << "Test parameterized constructor Failed" << endl;

	if(test_file_constructor())
		cout << "Test file constructor Passed" << endl;
	else
		cout << "Test file constructor Failed" << endl;

	if(test_equals())
		cout << "Test equals Passed" << endl;
	else
		cout << "Test equals Failed" << endl;

	if(test_plus())
		cout << "Test plus Passed" << endl;
	else
		cout << "Test plus Failed" << endl;

	if(test_minus())
		cout << "Test minus Passed" << endl;
	else
		cout << "Test minus Failed" << endl;

	if(test_mult())
		cout << "Test mult Passed" << endl;
	else
		cout << "Test mult Failed" << endl;

	if(test_derivative())
		cout << "Test derivative Passed" << endl;
	else
		cout << "Test derivative Failed" << endl;

	test_print();
}


int main() {
	PolynomialTest test;
	test.run();

	return 0;
}
