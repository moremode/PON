#include <iostream>
#include <vector>
#include "lab1.h"

namespace Sage1
{
	// 1 - error by entering
	int getNum(int& destination)
	{
		std::cin >> destination;                                                                                                                                                                                                                                                                                          
        if (!std::cin.good()) return 1;
        return 0;
	}

	// 1 - error by entering
	int getSizes(int& n, int& m)
	{
		if (getNum(n) || getNum(m)) return 1;
		return 0;
	}

	// 1 - matrix isnt clear
	// 2 - error by entering
	int getMatrix(int**& matrix, int n, int m)
	{
		if (!matrix) return 1;
		matrix = new int*[m];
		for (int i = 0; i < m; i++)
			matrix[i] = new int[n];
		for (int i1 = 0; i1 < m; i1++)
			for (int i2 = 0; i2 < n; i2++)
				if (getNum(matrix[i1][i2])) return 2;
		return 0;
	}

	int printMatrix(int** matrix, int n, int m)
	{
		for (int i1 = 0; i1 < m; i1++)
		{
			for (int i2 = 0; i2 < n; i2++)
				std::cout << matrix[i1][i2] << " ";
			std::cout << "\n";
		}
		return 0;
	}

	int createVector(std::vector<int>& vec, int** matrix, int n, int m, bool (*func1)(int), bool (*func2)(int))
	{
		vec.clear();
		for (int i1 = 0; i1 < m; i1++)
		{
			int s1 = 0;
			int s2 = 0;
			for (int i2 = 0; i2 < n; i2++)
			{
				if (func1(matrix[i1][i2])) s1++;
				if (func2(matrix[i1][i2])) s2++;
			}
			vec.push_back(s1 - s2);
		}
		return 0;
	}

	int printVector(std::vector<int> vec)
	{
		int size = vec.size();
		for (int i = 0; i < size; i++)
		    std::cout << "Row " << i << ": " << vec[i] << "\n";
		return 0;
	}
}
