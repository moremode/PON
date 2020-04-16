#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void printOne(char* str, char* end)
{
	size_t len = strlen(str);
	int flag = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ' ' && !flag)
		{
			printf(" ");
			flag = 1;
		}
		if (str[i] != ' ')
		{
			printf("%c", str[i]);
			flag = 0;
		}
	}
	printf("%s", end);
}

void change(char* before)
{
	size_t len = strlen(before);
	int b = 0;
	int now = 0;
	int flag = 0;
	char* c_now;
	if (len == 0)
	{
		return;
	}
	for (size_t i = 0; i < len; i++)
	{
		now++;
		/*if (before[i] == ' ' || before[i] == '\t' || i == len - 1)
		{
			if (before[b] == '(' && before[k] == ')')
			{
				c_now = malloc(now);
				strncpy(c_now, before + b, now);
				printf("%s", c_now);
				free(c_now);
			}
			b = i + 1;
			now = 0;
		}*/
		if (before[i] == '(' && (i == 0 || before[i - 1] != '\\'))
		{
			b = i;
			flag = 1;
			now = 0;
		}
		if (before[i] == ')' && flag == 1 && before[i - 1] != '\\')
		{
			c_now = malloc(now);
                        strncpy(c_now, before + b, now + 1);
                        //printf("%s\x20", c_now);
			printOne(c_now, "\x20");
                        free(c_now);
			flag = 0;
		}
		if (i == len - 1 && flag == 1 && before[i] != '\\')
		{
			c_now = malloc(now);
                        strncpy(c_now, before + b, now + 1);
                        //printf("%s)\x20", c_now);
			printOne(c_now, ")\x20");
                        free(c_now);
                        flag = 0;
		}
		
	}
}

int main()
{
	while (1)
	{
		char* s = get_string();
		if (s == NULL)
		{
			printf("EOkek\n");
			exit(-1);
		}
		change(s);
		printf("\n");
		//printf(s);
	}		
}
