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
	int getMatrix(int**& matrix, int n, int m, int& size)
	{
		if (!matrix) return 1;
		int counter = 0;
		matrix = new int*[3];
		for (int i = 0; i < 3; i++)
			matrix[i] = new int[0];
		for (int i1 = 0; i1 < m; i1++)
			for (int i2 = 0; i2 < n; i2++)
			{
				int num = 0;
				if (getNum(num)) return 2;
				if (num)
				{
					counter++;
					matrix[0] = (int*) realloc(matrix[0], counter * sizeof(int));
					matrix[1] = (int*) realloc(matrix[1], counter * sizeof(int));
					matrix[2] = (int*) realloc(matrix[2], counter * sizeof(int));
					matrix[0][counter - 1] = num;
					matrix[1][counter - 1] = i1;
					matrix[2][counter - 1] = i2;
				}
			}
		size = counter;
		return 0;
	}

	int printMatrix(int** matrix, int n, int m, int size)
	{
		int counter = 0;
		for (int i1 = 0; i1 < m; i1++)
		{
			for (int i2 = 0; i2 < n; i2++)
				if (counter == size)
				{
					std::cout << "0 ";
				}
				else
				{
					if (matrix[1][counter] == i1 && matrix[2][counter] == i2)
					{
						std::cout << matrix[0][counter] << " ";
						counter++;
					}
					else
						std::cout << "0 ";
				}
			std::cout << "\n";
		}
		return 0;
	}

	int createVector(std::vector<int>& vec, int** matrix, int n, int m, int size, bool (*func1)(int), bool (*func2)(int))
	{
		int counter = 0;
		vec.clear();
		for (int i1 = 0; i1 < m; i1++)
		{
			int s1 = 0;
			int s2 = 0;
			for (int i2 = 0; i2 < n; i2++)
			{
				int x = 0;
				if (counter != size && matrix[1][counter] == i1 && matrix[2][counter] == i2)
				{
					x = matrix[0][counter];
					counter++;
				}
				if (func1(x)) s1++;
				if (func2(x)) s2++;
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
