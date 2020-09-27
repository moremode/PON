#include <iostream>
#include <vector>
#include "lab1.h"

//using namespace Sage1;

bool func1(int num)
{
	return num > 10;
}

bool func2(int num)
{
	return num % 2 == 0;
}

int main()
{
	int n, m;
	int** matrix;
	std::vector<int> b;
	std::cout << "Input sizes: ";
	if (Sage1::getSizes(n, m)) return 1;
	std::cout << "Input matrix " << n << "x" << m << ": ";
	if (Sage1::getMatrix(matrix, n, m)) return 1;
	Sage1::printMatrix(matrix, n, m);
	Sage1::createVector(b, matrix, n, m, func1, func2);
	Sage1::printVector(b);
}
