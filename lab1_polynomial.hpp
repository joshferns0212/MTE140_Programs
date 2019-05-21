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
};
