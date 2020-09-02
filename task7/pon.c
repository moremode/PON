#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element
{
	int some_info;
	struct element* next;
} et;

et* head = NULL;
et* tail = NULL;

int add(int info)
{
	et* new_e = (et*) malloc(sizeof(et));
	if (!new_e) return 1;
	new_e->some_info = info;
	new_e->next = NULL;
	if (!tail)
	{
		head = new_e;
		tail = new_e;
	}
	else
	{
		tail->next = new_e;
		tail = new_e;
	}
	return 0;
}

int get()
{
	if (!head) return 0;
	int result = head->some_info;
	et* data = head;
	if (head->next)
	{
		head = head->next;
	}
	else
	{
		head = NULL;
		tail = NULL;
	}
	free(data);
	return result;
}

et* first = NULL;

int add_c(int info)
{
	et* new_e = (et*) malloc(sizeof(et));
        if (!new_e) return 1;
	new_e->some_info = info;
	new_e->next = NULL;
	if (first)
	{
		new_e->next = first->next;
		first->next = new_e;
		first = new_e;
	}
	else
	{
		new_e->next = new_e;
		first = new_e;
	}
}

int get_c()
{
	if (!first) return 0;
	int result = first->next->some_info;
	et* data = first->next;
	if (first->next == first)
	{
		first = NULL;
	}
	else
	{
		printf("PON");
		first->next = first->next->next;
	}
	free(data);
	return result;
}

int main()
{
	printf("%d\n", get_c());
	add_c(7);
	add_c(76);
	add_c(15);
	add_c(7);
	printf("%d\n", get_c());
	printf("%d\n", get_c());
	add_c(4);
	printf("%d\n", get_c());
	printf("%d\n", get_c());
	printf("%d\n", get_c());
	printf("%d\n", get_c());
	add_c(1);
	printf("%d\n", get_c());
	printf("%d\n", get_c());
}





















