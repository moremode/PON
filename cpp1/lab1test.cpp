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
	int n = 0, m = 0, size = 0, max_size = 0;
	int** matrix = nullptr;
	std::vector<int> b;
	std::cout << "Input sizes: ";
	if (Sage1::getSizes(n, m)) return 1;
	std::cout << "Input matrix " << n << "x" << m << ": ";
	if (Sage1::getMatrix(matrix, n, m, max_size, size)) return 1;
	Sage1::printMatrix(matrix, n, m, size);
	Sage1::createVector(b, matrix, n, m, size, func1, func2);
	Sage1::printVector(b);
	Sage1::deleteMatrix(matrix);
}
