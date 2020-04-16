#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 64

typedef struct char_list
{
	char* str;
	struct char_list* next;
} char_list_t;

void print_list(char_list_t* first)
{
	while (first != NULL)
	{
		printf("\n%s", first->str);
		first = first->next;
	}
}

int is_alph(char sim)
{
        int ord = (int)sim;
        return (ord >= 65 && ord <= 90) || (ord >= 97 && ord <= 122);
}

char* change_word(char* str)
{
	int len = (int) strlen(str);
	int counter = 0;
	char* new = (char*) calloc(len * 2 + 1, sizeof(char));
	int now = 0;
	char prev = '(';
	int not_empty = 0;
	int starts_with = 0;
	int ends_with = 0;
	int flag = 0;
	for (int i = 0; i < len; i++)
	{
		flag = 0;
		if (str[i] == '(')
		{
			if ((is_alph(prev) || prev == ')') && !flag)
			{
				flag = 1;
				if (counter < 0)
					counter = -counter;
				ends_with = i;
				if (!not_empty)
					counter = 1;
				for (int i1 = 0; i1 < counter; i1++)
				{
					new[now] = '(';
					now++;
				}
				for (int i1 = starts_with; i1 < ends_with; i1++)
				{
					new[now] = str[i1];
					now++;
				}
				for (int i1 = 0; i1 < counter; i1++)
				{
					new[now] = ')';
					now++;
				}
				not_empty = 1;
				counter = 1;
				starts_with = 0;
                                ends_with = 0;
			}
			else
			{
				not_empty = 1;
				counter++;
			}
		}
		if (str[i] == ')')
		{
			if (is_alph(prev) || str[i] == ')')
			{
				counter--;
			}
			if (is_alph(prev))
				not_empty = 1;
		}
		if (is_alph(str[i]))
		{
			if (prev == ')' && !flag)
			{
				flag = 1;
				if (counter < 0)
                                        counter = -counter;
                                ends_with = i;
                                if (!not_empty)
                                        counter = 1;
                                for (int i1 = 0; i1 < counter; i1++)
                                {
                                        new[now] = '(';
                                        now++;
                                }
                                for (int i1 = starts_with; i1 < ends_with; i1++)
                                {
                                        new[now] = str[i1];
                                        now++;
                                }
                                for (int i1 = 0; i1 < counter; i1++)
                                {
                                        new[now] = ')';
                                        now++;
                                }
				starts_with = 0;
                                ends_with = 0;
                                not_empty = 0;
			}
			if (!is_alph(prev))
				starts_with = i;
			if (prev == '(')
				not_empty = 1;
			ends_with = i;
		}
		if (i == len - 1 && !flag)
		{
			flag = 1;
			printf("%d", starts_with);
			printf("%d", ends_with);
			if (counter < 0)
                                counter = -counter;
                        ends_with = i;
                        if (!not_empty)
                                counter = 1;
                        for (int i1 = 0; i1 < counter; i1++)
                        {
                                new[now] = '(';
                                now++;
                        }
                        for (int i1 = starts_with; i1 < ends_with; i1++)
              	        {
                               	new[now] = str[i1];
                               	now++;
                       	}
		       	for (int i1 = 0; i1 < counter; i1++)
                        {
                                new[now] = ')';
                                now++;
                        }
			starts_with = 0;
                       	ends_with = 0;
                        not_empty = 1;
		}
		prev = str[i];
	}
	return new;
}

int main()
{
	char_list_t* start = (char_list_t*) malloc(sizeof(char_list_t));
	char_list_t* now = start;
	start->str = malloc(LENGTH);
	int flag = 1;
	char* pon = change_word("(AARWTWTW))");
	printf("%s", pon);
	while (flag != -1)
	{
		flag = scanf("%s", now->str);
		if (flag != -1)
		{
			now->next = (char_list_t*) malloc(sizeof(char_list_t));
			now = now->next;
			now->str = malloc(LENGTH);
		}
	}
	print_list(start);
}
