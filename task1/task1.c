#include <stdio.h>
#include <stdlib.h>

int digCount(int number)
{
        int ret = 0;
        while(number)
        {
                ret++;
                number /= 10;
        }
        return ret;
}

void change(int *number)
{
	int start = *number;
	int ret = 0;
	int now = 1;
	while (start)
	{
		int digit = start % 10;
		int flag = 1;
		start /= 10;
		if (digit > 5)
		{
			flag = 0;
		}
		if (flag)
		{
			ret += digit * now;
			now *= 10;
		}
	}
	*number = ret;
}

void printArray(const int* array, int n)
{
	printf("\n");
	for (int i = 0; i < n; i++)
        {
                printf("%d: %d\n", i, array[i]);
        }
}

void fill(int* array, int n)
{
	for (int i = 0; i < n; i++)
        {
                int input = 0;
                scanf("%d", &input);
                if (input < 0)
                {
                        printf("PON((\n");
                        exit(-1);
                }
                array[i] = input;
        }
}

void changeArray(int* array1, int* array, int n)
{
	for (int i = 0; i < n; i++)
        {
                change(&array[i]);
                array1[i * 2] = array[i];
		array1[i * 2 + 1] = digCount(array[i]);
                if (array1[i * 2] > array1[i * 2 + 1])
                {
                        int c = array1[i * 2];
                        array1[i * 2] = array1[i * 2 + 1];
                        array1[i * 2 + 1] = c;
                }
        }
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	if (n <= 0)
	{
		printf("PON(\n");
		return -1;
	}
	int* array = (int*)calloc(n, sizeof(int));
	fill(array, n);
	printArray(array, n);
	n *= 2;
	int* array1 = (int*)calloc(n, sizeof(int));
	changeArray(array1, array, n / 2);
	printArray(array1, n);	
	free(array);
	free(array1);
	return 0;
}
