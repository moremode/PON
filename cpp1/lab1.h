namespace Sage1
{
	int getNum(int& destination);
	int getSizes(int& n, int& m);
	int getMatrix(int**& matrix, int n, int m);
	int printMatrix(int** matrix, int n, int m);
	int createVector(std::vector<int>& vec, int** matrix, int n, int m, bool (*func1)(int), bool (*func2)(int));
	int printVector(std::vector<int> vec);
}
