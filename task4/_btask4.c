#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define SIZE 20
#define FILENAME "pon.txt"

typedef struct hash_table
{
	int key1;
	int key2;
	int size;
        char* info;
} hash_t;

hash_t*** table;
hash_t* default_element;

void clear_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
}

int generate()
{
	if (SIZE < 0) return 2;
	default_element = (hash_t*) malloc(sizeof(hash_t));
	default_element->key1 = -1;
	default_element->key2 = -1;
	default_element->info = NULL;
	table = (hash_t***) malloc(SIZE * sizeof(hash_t**));
	if (table == NULL) return 1;
	for (int i = 0; i < SIZE; i++)
	{
		table[i] = (hash_t**) malloc((SIZE + 1) * sizeof(hash_t*));
		if (table[i] == NULL) return 1;
		table[i][0] = (hash_t*) malloc(sizeof(hash_t));
		if (table[i][0] == NULL) return 1;
		table[i][0]->key1 = SIZE;
		table[i][0]->key2 = -1;
	}
	return 0;
}

int get_hash(int key)
{
	if (key < 0) return -1;
	return key % SIZE + 1;
}

hash_t** get_by(int key1)
{
	if (table == NULL) return NULL;
        if (key1 < 0) return NULL;
        int clear = -1;
        for (int i = 0; i < SIZE; i++)
        {
                if (table[i] == NULL) return NULL;
                if (table[i][0] == NULL) return NULL;
                if (table[i][0]->key2 == key1) return table[i];
		if (table[i][0]->key2 == -1 && clear == -1) clear = i;
        }
	if (clear == -1) return NULL;
	return table[clear];
}

int get_left(int key1)
{
	if (table == NULL) return -1;
	if (key1 < 0) return -2;
	hash_t** ret = get_by(key1);
	if (ret == NULL) return -1;
	return ret[0]->key1;
}

int add(int key1, int key2, char* info, int len)
{
	if (key2 < 0) return 2;
	int left = get_left(key1);
	if (left < 0) return -left;
	if (left == 0) return 3;
	hash_t** space1 = get_by(key1);
	space1[0]->key2 = key1;
	for (int i = 0; i < SIZE; i++)
	{
		int now_key = get_hash(i + key2);
		if (space1[now_key] == NULL || space1[now_key] == default_element)
		{
			space1[now_key] = (hash_t*) malloc(sizeof(hash_t));
			if (space1[now_key] == NULL) return 1;
			space1[now_key]->key1 = key1;
			space1[now_key]->key2 = key2;
			space1[now_key]->size = len;
			space1[now_key]->info = (char*) malloc(len);
			strcpy(space1[now_key]->info, info);
			space1[0]->key1--;
			return 0;
		}
		else if (space1[now_key]->key2 == key2) return 4;
	}
	return 6;
}

int rm(int key1, int key2)
{
	if (key2 < 0) return 2;
        int left = get_left(key1);
        if (left < 0) return -left;
	if (left == SIZE) return 3;
	hash_t** space1 = get_by(key1);
	if (space1[0]->key2 == -1) return 3;
	for (int i = 0; i < SIZE; i++)
	{
		int now_key = get_hash(i + key2);
		if (space1[now_key] == NULL) return 3;
		if (space1[now_key]->key2 == key2)
		{
			if (space1[now_key]->info) free(space1[now_key]->info);
			free(space1[now_key]);
			space1[now_key] = default_element;
			space1[0]->key1++;
			if (space1[0]->key1 == SIZE) space1[0]->key2 = -1;
			return 0;
		}
	}
	return 3;
}

int print_table()
{
	if (table == NULL) return 1;
	for (int i1 = 0; i1 < SIZE; i1++)
	{
		int key1 = i1;
		if (table[key1] == NULL) return 1;
		for (int i2 = 0; i2 < SIZE; i2++)
		{
			int key2 = get_hash(i2);
			hash_t* el = table[key1][key2];
			printf("TABLE[%d][%d] = ", key1, key2 - 1);
			if (el == NULL) printf("NULL\n");
			else
			{
				if (el->info == NULL) printf("INFO NULL\n");
				else printf("key1=%d :: key2=%d :: %s", el->key1, el->key2, el->info);
			}
		}
		printf("\n");
	}
	return 0;
}

int free_table()
{
        if (table == NULL) return 1;
        for (int i1 = 0; i1 < SIZE; i1++)
        {
                int key1 = i1;
                if (table[key1] != NULL)
                {
			if (table[key1][0] != NULL) free(table[key1][0]);
                        for (int i2 = 0; i2 < SIZE; i2++)
                        {
                                int key2 = get_hash(i2);
                                hash_t* el = table[key1][key2];
                                if (el != NULL && el != default_element)
                                {
                                        if (el->info != NULL) free(el->info);
                                 	free(el);
                                }
                        }
                        free(table[key1]);
                }
        }
        free(table);
	if (default_element) free(default_element);
        return 0;
}


int find(int key1, int key2)
{
	if (key2 < 0) return 2;
        int left = get_left(key1);
        if (left < 0) return -left;
        if (left == SIZE) return 3;
	hash_t** space1 = get_by(key1);
	if (space1[0]->key2 == -1) return 3;
        for (int i = 0; i < SIZE; i++)
        {
                int now_key = get_hash(i + key2);
                if (space1[now_key] == NULL) return 3;
                if (space1[now_key]->key2 == key2)
                {
                        printf("TABLE[%d][%d]: %s\n", key1, key2, space1[now_key]->info);
			return 0;
                }
        }
        return 3;
}

int send_to_file()
{
	if (table == NULL) return 1;
        FILE *fp;
        fp = fopen(FILENAME, "w+");
        for (int i1 = 0; i1 < SIZE; i1++)
        {
                int key1 = i1;
                if (table[key1] == NULL) { fclose(fp); return 1; }
                for (int i2 = 0; i2 < SIZE; i2++)
                {
                        int key2 = get_hash(i2);
                        hash_t* el = table[key1][key2];
                        if (el != NULL)
                        {
                                if (el->info != NULL)
                                {
                                        fwrite(el, sizeof(hash_t), 1, fp);
					fwrite(el->info, sizeof(char), el->size, fp);
                                }
                        }
                }
        }
        fclose(fp);
        return 0;
}

int load_from_file()
{
	if (access(FILENAME, F_OK) != -1)
        {
                FILE * fp;

                fp = fopen(FILENAME, "r");
                if (fp == NULL)
                        exit(1);
		
		hash_t* element = (hash_t*) malloc(sizeof(hash_t));
		while (!feof(fp))
		{
			int ret = fread(element, sizeof(hash_t), 1, fp);
			if (feof(fp))
			{
				fclose(fp);
				free(element);
				return 1;
			}
			char* info = malloc(element->size);
			fread(info, sizeof(char), element->size, fp);
			add(element->key1, element->key2, info, element->size);
			free(info);
		}

		free(element);

                fclose(fp);
        }
}

int print_menu()
{
	printf("%s\n", "1> ADD PON");
	printf("%s\n", "2> REMOVE KEBAB");
	printf("%s\n", "3> FIND YOURSELF");
	printf("%s\n", "4> PRINT INT");
	printf("%s\n\n", "5> EXIT LIFE");
	printf("%s", "ENTER YOUR TURN> ");
	return 0;
}

int action()
{
	int i;
	scanf("%d", &i);
	if (i == 0) clear_buffer();
	if (i < 1 || i > 5) return 1;
	if (i == 1)
	{
		int key1, key2;
		char* info = (char*) malloc(20 * sizeof(char));
		printf("ENTER KEY1: ");
		scanf("%d", &key1);
		printf("ENTER KEY2: ");
		scanf("%d", &key2);
		printf("ENTER INFO: ");
		getchar();
		fgets(info, 20, stdin);
		printf("\n");
		int ret = add(key1, key2, info, strlen(info) + 1);
		if (ret == 1) printf("ERROR: NULL TABLE\n\n");
		if (ret == 2) printf("ERROR: NOT IN BORDERS\n\n");
		if (ret == 3) printf("ERROR: NO SPACE\n\n");
		if (ret == 4) printf("ERROR: IS CREATED\n\n");
		if (ret == 5) printf("ERROR: \n\n");
		if (ret == 6) printf("ERROR: YA NE POMNU CHO ZA OSHIBKA(\n\n");
		free(info);
	}
	if (i == 2)
	{
		int key1, key2;
		printf("ENTER KEY1: ");
		scanf("%d", &key1);
		printf("ENTER KEY2: ");
                scanf("%d", &key2);
		printf("\n");
		int ret = rm(key1, key2);
		if (ret == 1) printf("ERROR: NULL TABLE\n\n");
                if (ret == 2) printf("ERROR: NOT IN BORDERS\n\n");
                if (ret == 3) printf("ERROR: NOT FIND\n\n");
	}
	if (i == 3)
	{
		int key1, key2;
		printf("ENTER KEY1: ");
                scanf("%d", &key1);
		printf("ENTER KEY2: ");
                scanf("%d", &key2);
		printf("\n");
		int ret = find(key1, key2);
		if (ret == 1) printf("ERROR: NULL TABLE\n\n");
                if (ret == 2) printf("ERROR: NOT IN BORDERS\n\n");
                if (ret == 3) printf("ERROR: NOT FIND\n\n");
	}
	if (i == 4)
	{
		printf("\n");
		print_table();
	}
	if (i == 5)
	{
		send_to_file();
		free_table();
	       	exit(1);
	}
}

int main()
{
	int ret = generate();
	if (ret != 0) exit(2);
	load_from_file();
	while (1)
	{
		print_menu();
		action();
	}
}









