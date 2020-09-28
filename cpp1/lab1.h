namespace Sage1
{
	int getNum(int& destination);
	int getSizes(int& n, int& m);
	int getMatrix(int**& matrix, int n, int m, int& max_size, int& size);
	int printMatrix(int** matrix, int n, int m, int size);
	int createVector(std::vector<int>& vec, int** matrix, int n, int m, int size, bool (*func1)(int), bool (*func2)(int));
	int printVector(std::vector<int>& vec);
	int deleteMatrix(int**& matrix);
}
