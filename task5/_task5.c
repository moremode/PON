#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

#define SIZE 20
#define FILENAME "pon.txt"

typedef struct tree_table
{
        int key;
        char* info;
	struct tree_table* left;
	struct tree_table* right;
} tree_t;

tree_t* mtree = 0;
struct timespec start, end;

void timer_start()
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
}

void timer_end()
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        u_int64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
        printf("microseconds: %ld\n", delta_us);
}

int add(int key, char* info, int size)
{
	if (!mtree)
	{
		mtree = (tree_t*) malloc(sizeof(tree_t));
                if (!mtree) return 2;
		mtree->key = key;
        	mtree->info = (char*) calloc(size + 1, sizeof(char));
		mtree->right = 0;
		mtree->left = 0;
	        strncpy(mtree->info, info, size);
		return 0;
	}
	tree_t* now = mtree;
	tree_t* last = NULL;
	int right = 0;
	while (now && now->info)
	{
		if (key == now->key) return 1;
		last = now;
		if (key > now->key)
		{
			now = now->right;
			right = 1;
		}
		else
		{
			now = now->left;
			right = 0;
		}
	}
	if (!now)
	{
		now = (tree_t*) malloc(sizeof(tree_t));
		if (!now) return 2;
		now->right = 0;
		now->left = 0;
	}
	if (last)
	{
		if (right) last->right = now;
		else last->left = now;
	}
	now->key = key;
	now->info = (char*) calloc(size + 1, sizeof(char));
	strncpy(now->info, info, size);
	return 0;
}

int rm(int key)
{
	tree_t* now = mtree;
	if (!now) return 1;
	while (key != now->key)
        {
                if (key > now->key) now = now->right;
                else now = now->left;
                if (!now) return 1;
        }
	if (!now->info) return 2;
	free(now->info);
	now->info = NULL;
	return 0;
}

int find(int key)
{
	tree_t* now = mtree;
	if (!now) return 1;
        while (key != now->key)
        {
                if (key > now->key) now = now->right;
                else now = now->left;
		if (!now) return 1;
        }
	if (!now->info) return 2;
        printf("%s\n", now->info);
	return 0;
}

int print_all(tree_t* tree)
{
	if (!tree) return 1;
	if (tree->left) print_all(tree->left);
	if (tree->info) printf("%d: %s\n", tree->key, tree->info);
	if (tree->right) print_all(tree->right);
}

int print_table()
{
        if (!mtree) return 1;
        print_all(mtree);
	return 0;
}

int find_least(int key)
{
	tree_t* now = mtree;
        if (!now) return 1;
	int distance = -1;
	tree_t* least = 0;
        while (key != now->key)
        {
		if (now->info && (abs(now->key - key) < distance || distance == -1))
		{
			least = now;
			distance = abs(now->key - key);
		}
                if (key > now->key) now = now->right;
                else now = now->left;
                if (!now)
		{
			if (!least) return 3;
			printf("%d~%d: %s\n", key, least->key, least->info);
			return 0;
		}
        }
	if (now->info)
	{
		printf("COINCIDENCE %s\n", now->info);
		return 0;
	}
	tree_t* right = now->right;
	tree_t* left = now->left;
        if (!now->info)
	{
		while(left)
		{
			if (left->info && (abs(left->key - key) < distance || distance == -1))
                	{
                	        least = left;
                	        distance = abs(left->key - key);
                	}
                	if (key > left->key) left = left->right;
               		else left = left->left;
		}
		while(right)
                {
                        if (right->info && (abs(right->key - key) < distance || distance == -1))
                        {
                                least = right;
                                distance = abs(right->key - key);
                        }
                        if (key > right->key) right = right->right;
                        else right = right->left;
                }
	}
	if (!least) return 3;
	printf("%d~%d: %s\n", key, least->key, least->info);
        return 0;
}

int print_tree_r(tree_t* now)
{
	if (!now) return 0;
	printf("KEY: %d\n", now->key);
	if (!now->info) printf("REMOVED\n");
	else printf("INFO: %s\n", now->info);
	if (!now->left) printf("::LEFT ::NULL\n");
        else printf("::LEFT ::KEY=%d\n", now->left->key);
	if (!now->right) printf("::RIGHT::NULL\n");
	else printf("::RIGHT::KEY=%d\n", now->right->key);
	if (now->left) print_tree_r(now->left);
	if (now->right) print_tree_r(now->right);
}

int print_tree()
{
        if (!mtree) return 1;
        print_tree_r(mtree);
}

int send_to_file_r(FILE* fp, tree_t* now)
{
	if (!now) return 1;
	if (!fp) return 2;
	if (now->info) 
	{
		//fwrite(now->key, sizeof(int), 1, fp);
		//fwrite(now->info, sizeof(char), strlen(now->info), fp);
		fprintf(fp, "%d\n", now->key);
		fprintf(fp, "%s\n", now->info);
	}
	if (now->left) send_to_file_r(fp, now->left);
	if (now->right) send_to_file_r(fp, now->right); 
}

int send_to_file()
{
        if (!mtree) return 0;
        FILE *fp;
        fp = fopen(FILENAME, "w+");
        send_to_file_r(fp, mtree);
	fclose(fp);
}

int load_from_file()
{
	if (access(FILENAME, F_OK) != -1)
        {
		FILE* fp;
		char* line = malloc(20);
		size_t len = 20;

		fp = fopen(FILENAME, "r");
                if (fp == NULL)
                        return 1;
		//fclose(fp);
		while (1)
		{
			if (!fgets(line, len, fp))
			{
				if (line) free(line);
				fclose(fp);
				return 0;
			}
			int key = atoi(line);
			if (!fgets(line, len, fp))
			{
				if (line) free(line);
				fclose(fp);
				return 0;
			}
			int stlen = strlen(line);
			if(line[stlen - 1] == '\n') stlen -= 1;
			add(key, line, stlen);
		}
	}
}

int free_tree_r(tree_t* tree)
{
	if (!tree) return 0;
	if (tree->left) free_tree_r(tree->left);
	if (tree->right) free_tree_r(tree->right);
	if (tree->info) free(tree->info);
	free(tree);
}

int free_tree()
{
	if (!mtree) return 0;
	free_tree_r(mtree);
}

int print_menu()
{
	printf("%s\n", "1> ADD PON");
        printf("%s\n", "2> REMOVE KEBAB");
        printf("%s\n", "3> FIND YOURSELF");
	printf("%s\n", "4> SUPER CLOSE");
        printf("%s\n", "5> ALL U NEED");
	printf("%s\n", "6> TREE OR TREAT");
        printf("%s\n\n", "7> EXIT LIFE");
        printf("%s", "ENTER YOUR TURN> ");
        return 0;
}

int clear_fgets(char* str)
{
	char *pos;
	if ((pos=strchr(str, '\n')) != NULL)
    		*pos = '\0';
}

int action()
{
	char* input = malloc(20);
	fgets(input, 20, stdin);
	int action_number = atoi(input);
	if (action_number < 1 || action_number > 7)
	{
		free(input);
		return 1;
	}
	if (action_number == 1)
	{
		printf("INPUT KEY: ");
		fgets(input, 20, stdin);
		int key = atoi(input);
		printf("INPUT INFO: ");
		fgets(input, 20, stdin);
		clear_fgets(input);
		timer_start();
		int ret = add(key, input, strlen(input));
		timer_end();
		if (ret == 1) printf("ALREADY EXISTS\n");
		if (ret == 2) printf("MEMORY LACK\n");
	}
	if (action_number == 2)
	{
		printf("INPUT KEY: ");
		fgets(input, 20, stdin);
                int key = atoi(input);
		timer_start();
		int ret = rm(key);
		timer_end();
		if (ret == 1) printf("NOT CREATED\n");
		if (ret == 2) printf("ALREADY REMOVED\n");
	}
	if (action_number == 3)
	{
		printf("INPUT KEY: ");
                fgets(input, 20, stdin);
                int key = atoi(input);
		timer_start();
                int ret = find(key);
		timer_end();
		if (ret == 1) printf("NOT CREATED\n");
		if (ret == 2) printf("REMOVED\n");
	}
	if (action_number == 4)
	{
		printf("INPUT KEY: ");
                fgets(input, 20, stdin);
                int key = atoi(input);
		timer_start();
                int ret = find_least(key);
		timer_end();
		if (ret == 1) printf("NOTHING CREATED\n");
		if (ret == 3) printf("ALL REMOVED\n");
	}
	if (action_number == 5)
	{
		timer_start();
		int ret = print_table();
		timer_end();
		if (ret == 1) printf("TABLE CLEAR\n");
	}
	if (action_number == 6)
	{
		timer_start();
		int ret = print_tree();
		timer_end();
		if (ret == 1) printf("TABLE CLEAR\n");
	}
	if (action_number == 7)
	{
		free(input);
		send_to_file();
		free_tree();
		exit(0);
	}
	free(input);
	printf("\n");
}

int main()
{
	load_from_file();
	while(1)
	{
		print_menu();
		action();
	}
}
