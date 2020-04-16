#include <stdio.h>
#include <stdlib.h>

void fill(int*** array, int* m)
{
	printf("Row count: ");
	scanf("%d", m);
	if (m <= 0)
	{
		printf("PON(");
		exit(-1);
	}
	*array = (int**) calloc(*m, sizeof(int*));
	for (int i = 0; i < *m; i++)
	{
		int n = 0;
		printf("Row %d length: ", i+1);
		scanf("%d", &n);
		if (n <= 0)
		{
			printf("PON((");
			exit(-1);
		}
		(*array)[i] = (int*)calloc(n + 1, sizeof(int));
		(*array)[i][0] = n;
		printf("Print %d elements: ", (*array)[i][0]);
		for (int i1 = 1; i1 < n + 1; i1++)
		{
			int num = 0;
			scanf("%d", &num);
			(*array)[i][i1] = num;
		}
	}
}

void printMatrix(int** matrix, int m)
{
	for (int i = 0; i < m; i++)
	{
		int n = matrix[i][0];
		printf("Row %d: ", i + 1);
		for (int i1 = 1; i1 < n + 1; i1++)
		{
			printf("%d ", matrix[i][i1]);
		}
		printf("\n");
	}
}

int digitSumm(int num)
{
	int ret = 0;
	while (num > 0)
	{
		ret += num % 10;
		num /= 10;
	}
	return ret;
}

void changeMatrix(int** changing, int** matrix, int m)
{
	for (int i1 = 0; i1 < m; i1++)
	{
		int count = 0;
		int length = **(matrix + i1);
		int last = digitSumm(*(*(matrix + i1) + length));
		for (int i2 = 1; i2 < length + 1; i2++)
		{
			if (digitSumm(*(*(matrix + i1) + i2)) == last)
				count++;
		}
		*(changing + i1) = (int*) calloc(count + 1, sizeof(int));
		**(changing + i1) = count;
		count = 0;
		for (int i2 = 1; i2 < length + 1; i2++)
		{
			if (digitSumm(*(*(matrix + i1) + i2)) == last)
			{
				count++;
				*(*(changing + i1) + count) = *(*(matrix + i1) + i2);
			}
		}
	}
}

void freeMatrix(int** matrix, int n)
{
	for (int i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}

int main()
{
	int** matrix;
	int** changed;
	int m = 0;
	fill(&matrix, &m);
	printMatrix(matrix, m);
	changed = (int**) calloc(m, sizeof(int*));
	changeMatrix(changed, matrix, m);
	printf("\n");
	printMatrix(changed, m);
	freeMatrix(matrix, m);
	freeMatrix(changed, m);
}
