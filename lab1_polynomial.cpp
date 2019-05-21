#include "lab1_polynomial.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>   
#include <time.h>
#include <iomanip>

using namespace std;


Polynomial::Polynomial(int A[], int size) {
    poly_data.resize(size);

    for(int i=0; i < size; ++i) {
            poly_data[i] = A[i];
    }
}

Polynomial::Polynomial() {
    srand(time(NULL));
    int size = rand() % 1001;
    poly_data.resize(size);

    for(int i=0; i < size; ++i) {
        poly_data[i] = rand() % 2001-1000;
    }

}

Polynomial::Polynomial(string fileName) {
    ifstream fin("");
    int size = 0;
    fin >> size;
    poly_data.resize(size);

    for(int i=0; i < size; ++i) {
        fin >> poly_data[i];
    }

}

bool Polynomial::operator==(const Polynomial& target) {
    if(poly_data.size() != target.poly_data.size())
        return false;
    for(int i=0; i < poly_data.size(); ++i) {
        if(poly_data[i] != target.poly_data[i])
            return false;
    }

    return true;
}


    void Polynomial::print() {
        for(int i=0; i < poly_data.size(); ++i) {
            if(poly_data[i] != 0) {
                cout << poly_data[i] << "x^" << i;
                if(i != poly_data.size()-1) { 
                	cout << " + " << endl;
				}
            }
        }
    }
    
    
    Polynomial Polynomial::operator+(const Polynomial& target) { 
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
    
	
	 Polynomial Polynomial::operator-(const Polynomial& target) { 
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
    Polynomial Polynomial::operator*(const Polynomial& target) {
    	int size = poly_data.size() + target.poly_data.size() - 1;
    	int poly_array[size] = {};
    	
    	for(int i=0; i < poly_data.size(); ++i) {
    		for(int j=0; j < target.poly_data.size(); ++j) {
    			poly_array[i+j] += poly_data[i] * target.poly_data[i];
			}
		}
		
		return Polynomial(poly_array, size);
	}
    
	Polynomial Polynomial::derivative() {
		int size = poly_data.size()-1;
		int poly_array[size] = {};
		
		for(int i=1; i < size + 1; ++i) {
			poly_array[i-1] = poly_data[i] * i;
		}
		
		return Polynomial(poly_array, size);
	}
	
int main() {
	return 0;
}
