#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct char_list
{
	char str;
	struct char_list* next;
} char_list_t;

void print_list(char_list_t* first)
{
	while (first != NULL)
	{
		printf("%c", first->str);
		first = first->next;
	}
	printf("\n");
}

void list_free(char_list_t* first)
{
	if (first->next != NULL)
		list_free(first->next);
	free(first);
}

char* get_string()
{
	char * ptr = (char *) malloc(sizeof(char));

	char buf[81];
	size_t len = 1;
	* ptr = '\0';
	for (int n = 1; n > 0;)
	{
		memset(buf, 0, 81);
		n = scanf("%80[^\n]", buf);
		if (n == 0)
		{
			ptr[len] = '\0';
			scanf("%*c");
			break;
		}
	    	else if (n < 0)
		{
			free(ptr);
			ptr = NULL;
			break;
		}
		else
		{
			len += strlen(buf);
			ptr = (char *)realloc(ptr, len + 1);
			strcat(ptr, buf);
		}
	}
	return ptr;
}

int listlen(char_list_t* list)
{
	int count = 0;
	while (list != NULL)
	{
		count++;
		list = list->next;
	}
	return count;
}

char_list_t* get_list(char* points)
{
	int len = strlen(points);
	char_list_t* start = (char_list_t*) malloc(sizeof(char_list_t));
        char_list_t* now = start;
	char last = 0;
	for (int i = 0; i < len; i++)
	{
		if (last != ' ' || points[i] != ' ')
		{
			now->str = points[i];
			now->next = (char_list_t*) malloc(sizeof(char_list_t));
			now = now->next;
			last = points[i];
		}
	}
	if (last != ' ')
		now->str = ' ';
	else
		now = NULL;
	return start;
}

int* count_spaces(char_list_t* start)
{
	int* ret = malloc(2 * sizeof(int));
	int spaces = 0;
	int not_spaces = 0;
	while (start != NULL)
	{
		if (start->str == ' ')
			spaces++;
		else
			not_spaces++;
		start = start->next;
	}
	ret[0] = spaces;
	ret[1] = not_spaces;
	return ret;
}

char listindex(char_list_t* start, int index)
{
	for (int i = 0; i < index; i++)
	{
		start = start->next;
		if (start == NULL)
			return -1;
	}
	return start->str;
}

void modify(char_list_t* start)
{
	int len = listlen(start);
	char_list_t* now = start;
	char_list_t* space = NULL;
	char_list_t* temp = NULL;
	char_list_t* kek = start;
	int count_now = 0;
	int c_pon = 0;
	int last = 0;
	int before = 0;
	for (int i = 0; i < len; i++)
	{
		c_pon++;
		//printf("%c\n", now->str);
		if (now->str == ' ')
		{
			space = now;
			last = i;
		}
		if ((c_pon - before) == 80 || i == len - 1)
		{
			if (i == len - 1 && space == NULL)
				return;
			if (i == len - 1)
                        {
                                space = now;
                                last = i;
                        }
			else if (space == NULL)
			{
				i++;
				char_list_t* temp1 = now->next;
				char_list_t* created = (char_list_t*) malloc(sizeof(char_list_t));
				created->str = ' ';
				now->next = created;
				created->next = temp1;
				now = now->next;
				space = now;
				last = i;
			}
			count_now++;
			//if (now->next->str == ' ')
			//{
			//	space = now->next;
			//	last = i;
			//}
			if (i != len - 1)
			{
				temp = space->next;
				space->next = NULL;
			}
			int* pon = count_spaces(kek);
			int c_spaces = pon[0] - 1;
			int havent = 80 - pon[0] - pon[1] + 1;
			if (i == len - 1)
				havent++;
			int need = 0;
			int addition = 0;
			if (c_spaces != 0)
				need = havent / c_spaces;
			if (c_spaces != 0)
				addition = havent % c_spaces;
			//printf("count: %p\n", &kek);
			//printf("havent: %d\n", havent);
			//printf("need: %d\n", need);
			//printf("addition: %d\n", addition);
			char_list_t* now_1 = kek;
			for (int i1 = 0; now_1 != NULL && i1 < last - before; i1++)
			{
				char_list_t* temp2 = now_1->next;
				if (now_1->str == ' ')
				{
					if (addition > 0)
					{
						char_list_t* temp1 = now_1->next;
                                                char_list_t* created = (char_list_t*) malloc(sizeof(char_list_t));
                                                created->str = ' ';
                                                created->next = temp1;
                                                now_1->next = created; 
                                                havent--;
						addition--;
					}
					for (int i2 = 0; i2 < need && havent > 0; i2++)
					{
						char_list_t* temp1 = now_1->next;
						char_list_t* created = (char_list_t*) malloc(sizeof(char_list_t));
						created->str = ' ';
						created->next = temp1;
						now_1->next = created;
						//printf("pon: %d\n", havent);
						havent--;
					}
				}
				now_1 = temp2;
			}
			if (i != len - 1)
			{
				before = count_now * 80;
				c_pon = before;
				space->next = temp;
				space->str = '\n';
				now = space;
				kek = space->next;
				space = NULL;
			}
		}
		now = now->next;
	}
}

int main()
{
	char_list_t* start;
	while (1)
	{
		char* kek = get_string();
		if (kek == NULL)
			exit(-1);
		start = get_list(kek);
		modify(start);
		print_list(start);
		list_free(start);
	}
}
