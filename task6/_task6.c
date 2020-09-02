#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

#define SCALE 50
#define FILENAME "info.txt"

typedef struct node
{
	int x;
	int y;
	int degree;
	int indegree;
	char* info;
	struct edge** next;
	struct edge** in;
} node_t;

typedef struct edge
{
	struct node* start;
	struct node* end;
	double distance;
} edge_t;

node_t** table;
int count = 0;

double distance(node_t* node1, node_t* node2)
{
	if (!node1 || !node2) return -1;
	return sqrt(pow(node1->x - node2->x, 2) + pow(node1->y - node2->y, 2));
}

double distance_e(edge_t* edge)
{
	return distance(edge->start, edge->end);
}

// 0 - not found
// 1 - null table
// 2 - not in borders
node_t* find_coord(int x, int y)
{
	if (!table) return NULL + 1;
        for (int i = 0; i < count; i++)
        {
                if (!table[i]) return NULL + 2;
                if (table[i]->x == x && table[i]->y == y) return table[i];
        }
	return NULL;
}

// 0 - not found
// 1 - null table
// 2 - not in borders
node_t* find_name(char* info)
{
	if (!table) return NULL + 1;
        for (int i = 0; i < count; i++)
        {
                if (!table[i]) return NULL + 2;
                if (!strcmp((table[i])->info, info)) return table[i];
        }
        return NULL;
}

// 1 - null table
// 2 - not in borders
// 3 - invalid size
// 4 - bad alloction
int add_node(int x, int y, char* info, int size)
{
	if (table)
	{
		node_t* ret = find_coord(x, y);
		if (ret) return 2;
		ret = find_name(info);
		if (ret) return 2;
	}
	else
	{
		table = malloc(0);
	}
	if (size <= 0 || strlen(info) < size) return 3;
	count++;
	table = (node_t**) realloc(table, count * sizeof(node_t*));
	if (!table) return 4;
	table[count - 1] = (node_t*) malloc(sizeof(node_t));
	if (!table[count - 1]) return 4;
	node_t* now = table[count - 1];
	now->x = x;
	now->y = y;
	now->degree = 0;
	now->indegree = 0;
	now->in = 0;
	now->next = 0;
	now->info = calloc(sizeof(char), size + 1);
	if (!now->info) return 4;
	strncpy(now->info, info, size);
	return 0;
}

// 1 - null node
// 2 - already exists
// 4 - bad allocation
int add_edge_to_node(node_t* mnode, edge_t* medge)
{
	if (!mnode || !medge) return 1;
	if (!mnode->next)
	{
		mnode->next = (edge_t**) malloc(sizeof(edge_t*));
		if (!mnode->next)
		{
			mnode->degree = 0;
			return 4;
		}
		*(mnode->next) = medge;
		mnode->degree = 1;
	}
	else
	{
		for (int i = 0; i < mnode->degree; i++)
		{
			if (mnode->next[i]->start == medge->start && mnode->next[i]->end == medge->end) return 2;
		}
		mnode->degree++;
		mnode->next = (edge_t**) realloc(mnode->next, mnode->degree * sizeof(edge_t*));
                if (!mnode->next)
                {
                        mnode->degree = 0;
                        return 4;
                }
		mnode->next[mnode->degree - 1] = medge;
	}
	return 0;
}

// 1 - null node
// 4 - bad allocation
int add_in_to_node(node_t* mnode, edge_t* medge)
{
        if (!mnode || !medge) return 1;
        if (!mnode->in)
        {
                mnode->in = (edge_t**) malloc(sizeof(edge_t*));
                if (!mnode->in)
                {
                        mnode->indegree = 0;
                        return 4;
                }
                *(mnode->in) = medge;
                mnode->indegree = 1;
        }
        else
        {
			for (int i = 0; i < mnode->indegree; i++)
			{
                    if (mnode->in[i]->start == medge->start && mnode->in[i]->end == medge->end) return 2;
            }
            mnode->indegree++;
            mnode->in = (edge_t**) realloc(mnode->in, mnode->indegree * sizeof(edge_t*));
			if (!mnode->in)
            {
				mnode->indegree = 0;
				return 4;
            }
            mnode->in[mnode->indegree - 1] = medge;
        }
	return 0;
}

// 1 - null node
// 4 - bad allocation
int add_edge(node_t* st, node_t* end)
{
    if (!st || !end) return 1;
     edge_t* now = (edge_t*) malloc(sizeof(edge_t));
    if (!now) return 4;
    now->start = st;
    now->end = end;
    now->distance = distance(st, end);
    if (add_edge_to_node(st, now) == 2)
	{
		free(now);
		return 2;
	}
	if (add_in_to_node(end, now) == 2)
	{
		free(now);
		return 2;
	}
	return 0;
}

// 2 - not in borders
// 3 - info clear
int graph_to_file_r(FILE* fp)
{
	if (!table) return 1;
	for (int i = 0; i < count; i++)
	{
		node_t* now = table[i];
		if (!now) return 2;
		if (!now->info) return 3;
		fprintf(fp, "%s [\n label = \"%s\\n[%d, %d]\"\n pos = \"%d, %d!\"\n]\n", now->info, now->info, now->x, now->y, now->x * SCALE, now->y * SCALE);
	}
	for (int i = 0; i < count; i++)
	{
		node_t* now = table[i];
		for (int i1 = 0; i1 < now->degree; i1++)
		{
			edge_t* edge = now->next[i1];
			if (edge)
			{
				if (edge->start && edge->end && edge->start->info && edge->end->info)
					fprintf(fp, "%s -> %s [label = %f];\n", edge->start->info, edge->end->info, edge->distance);
			}
		}
	}
	return 0;
}

int graph_to_file()
{
        if (!table) return 1;
        FILE *fp;
        fp = fopen("pon.dot", "w+");
        fprintf(fp, "digraph G {\n");
        int ret = graph_to_file_r(fp);
	if (ret)
	{
		fclose(fp);
		system("rm pon.dot");
		return ret;
	}
        fprintf(fp, "}");
        fclose(fp);
        system("neato pon.dot -n -Tpng -o pon.png");
        //system("rm pon.dot");
	return 0;
}

int rm_edge(node_t* node1, node_t* node2, int mode)
{
	if (mode)
	{
		for (int i = 0; i < node1->degree; i++)
		{
			edge_t* now = node1->next[i];
			if (now && now->end == node2)
			{
				node1->next[i] = node1->next[node1->degree - 1];
				node1->next[node1->degree - 1] = 0;
				free(now);
				node1->degree--;
				if (!node1->degree)
				{
                    free(node1->next);
					node1->next = NULL;
                }
                else
				{
					//node1->next = (edge_t**) realloc(node1->next, node1->degree * sizeof(edge_t*));
					if (!node1->next)
					{
						//free
						printf("MEMORY CONCHILOS1(");
						exit(1);
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < node1->indegree; i++)
        {
            edge_t* now = node1->in[i];
            if (now && now->start == node2)
            {
                node1->in[i] = node1->in[node1->indegree - 1];
                node1->in[node1->indegree - 1] = 0;
				free(now);
                node1->indegree--;
				if (!node1->indegree)
				{
					free(node1->in);
					node1->in = NULL;
				}
				else
				{
                   	//node1->in = (edge_t**) realloc(node1->in, node1->indegree * sizeof(edge_t*));
	            	if (!node1->in)
                 	{
                     	//free
						printf("MEMORY CONCHILOS2(");
                      	exit(1);
                	}
				}
            }
        }
	}
	return 0;
}

int rm(char* info)
{
        if (!table) return 1;
        for (int i = 0; i < count; i++)
        {
			//write(1, "SOME\n", 5);
			node_t* now = table[i];
            if (!now) return 2;
            if (!strcmp(now->info, info))
            {
                //table[i] = table[count - 1];
				//table[count - 1] = 0;
                while (now->degree)
                {
					edge_t* nowe = now->next[0];
                    if (nowe && nowe->end) rm_edge(nowe->end, nowe->start, 0);
					now->degree--;
					now->next[0] = now->next[now->degree];
                }
				while (now->indegree)
                {
					edge_t* nowe = now->in[0];
                    if (nowe && nowe->start) rm_edge(nowe->start, nowe->end, 1);
					now->indegree--;
                    now->in[0] = now->in[now->indegree];
                }
				free(now->next);
				free(now->in);
				if (now->info) free(now->info);
		        free(now);
				table[i] = table[count - 1];
                table[count - 1] = 0; 
                count--;
				if (count)
				{
                	table = (node_t**) realloc(table, count * sizeof(node_t*));
                	if (!table)
					{
                    	//free
						printf("MEMORY CONCHILOS3(");
                    	exit(1);
                	}
				}
				else
				{
					free(table);
					table = 0;
				}
                return 0;
            }
        }
		return 3;
}

int random_graph()
{
	srand(time(NULL));
	int nodec = 50;
	int descps = 50;
	int start_for = count;
	int end_for = count + nodec;
	for (int i = start_for; i < end_for; i++)
	{
		int randx = ((rand() * rand() % descps) + descps) % descps + 1;
		int randy = ((rand() * rand() % descps) + descps) % descps + 1;
		char x[5];
		sprintf(x, "%d", i);
		add_node(randx, randy, x, strlen(x));
	}
	for (int i = start_for; i < end_for + 100; i++)
	{
		int rs = ((rand() * rand() % (count)) + (count)) % (count);
		int re = ((rand() * rand() % (count)) + (count)) % (count);
		char s[5];
		char e[5];
		sprintf(s, "%d", rs);
		sprintf(e, "%d", re);
		add_edge(find_name(s), find_name(e));
	}
}

int free_graph()
{
    if (!table) return 0;
    while (count)
    {
		rm(table[0]->info);
    }
    free(table);
    return 0;
}


int get_index(node_t* node)
{
	for (int i = 0; i < count; i++)
	{
		if (table[i] == node)
			return i;
	}
	return -1;
}

int print_matrix(double** matrix)
{
	for (int i1 = 0; i1 < count; i1++)
	{
		for (int i2 = 0; i2 < count; i2++)
			if (matrix[i1][i2] != 1000000) printf("%f ", matrix[i1][i2]);
			else printf("-1 ");
		printf("\n");
	}
	printf("\n");
}

int print_matrixi(int** matrix)
{
    for (int i1 = 0; i1 < count; i1++)
    {
        for (int i2 = 0; i2 < count; i2++)
            if (matrix[i1][i2] != 1000000) printf("%d ", matrix[i1][i2]);
            else printf("-1 ");
        printf("\n");
    }
    printf("\n");
}


double** build_matrix()
{
	double** v2 = (double**) malloc(count * sizeof(double*));
	for (int i = 0; i < count; i++)
		v2[i] = (double*) malloc(count * sizeof(double));
	for (int i1 = 0; i1 < count; i1++)
	{
		node_t* now = table[i1];
		for (int i2 = 0; i2 < count; i2++)
			v2[i1][i2] = 1000000;
		int degree = now->degree;
		for (int i2 = 0; i2 < degree; i2++)
		{
			edge_t* edge = now->next[i2];
			int to = get_index(edge->end);
			if (to != -1) v2[i1][to] = edge->distance;
		}
	}
	//print_matrix(v2);
	return v2;
}

int** p_matrix()
{
	int** v2 = (int**) malloc(count * sizeof(int*));
	for (int i1 = 0; i1 < count; i1++)
	{
		v2[i1] = (int*) malloc(count * sizeof(int));
	}
	for (int i1 = 0; i1 < count; i1++)
    {
		node_t* now = table[i1];
        for (int i2 = 0; i2 < count; i2++)
            v2[i1][i2] = -1;
        int degree = now->degree;
        for (int i2 = 0; i2 < degree; i2++)
        {
            edge_t* edge = now->next[i2];
            int to = get_index(edge->end);
            if (to != -1) v2[i1][to] = to;
        }
	}
	return v2;
}

double min(double n1, double n2)
{
	return n1 > n2 ? n2 : n1;
}

double** floyd(int*** spd_mtrx)
{
	double** matrix = build_matrix();
	int** matrix1 = p_matrix();
	//print_matrixi(matrix1);
	for (int k = 0; k < count; k++)
  		for (int i = 0; i < count; i++)
    			for (int j = 0; j < count; j++)
      			{
					if (matrix[i][k] + matrix[k][j] < matrix[i][j])
					{
						matrix[i][j] = matrix[i][k] + matrix[k][j];
						matrix1[i][j] = matrix1[i][k];
					}
				}
	//print_matrix(matrix);
	*spd_mtrx = matrix1;
	return matrix;
}

int find_min(node_t* n1, node_t* n2, int flag)
{
	if (!n1 || !n2) return 1;
	int** ret3[1];
	double** m = floyd(ret3);
	int** ret = *(ret3);
	int index1 = get_index(n1);
	int index2 = get_index(n2);
	if (flag) printf("MIN: %f\n", m[index1][index2]);
	if (m[index1][index2] != 1000000)
	{
		while (index1 != index2)
		{
			if (flag) printf("%s -> ", table[index1]->info);
			index1 = ret[index1][index2];
		}
		if (flag) printf("%s\n", table[index2]->info);
	}
	for (int i = 0; i < count; i++)
	{
		free(m[i]);
		free(ret[i]);
	}
	free(m);
	free(ret);
	return 0;
}

int timing(int cnt)
{
	srand(time(NULL));
	int lim = 10000;
	int c = 10;
	int n = c;
	int x, y;
	size_t summ = 0;
	clock_t first, last;
	while (n-- > 0)
	{
		table = 0;
		for (int i = 0; i < cnt; )
		{
			//printf("PONG");
			x = (rand() * rand()) % lim;
			y = (rand() * rand()) % lim;
			char* xc = calloc(12, sizeof(char));
			sprintf(xc, "%d", i);
			//printf("%s\n", xc);
			if (!add_node(x, y, xc, strlen(xc))) i++;
			free(xc);
		}
		for (int i = 0; i < cnt / 2; )
		{
			//printf("PON");
			x = (rand() * rand()) % cnt;
			//printf("%d", cnt);
			y = (rand() * rand()) % cnt;
			char* xc = calloc(12, sizeof(char));
			char* yc = calloc(12, sizeof(char));
			sprintf(xc, "%d", x);
			sprintf(yc, "%d", y);
			if (add_edge(find_name(xc), find_name(yc))) i++;
			free(xc);
			free(yc);
		}
		first = clock();
		for (int i = 0; i < 1000; i++)
		{
			//printf("%d", cnt);
			x = (rand() * rand()) % cnt;
			//printf("%d", x);
			y = (rand() * rand()) % cnt;
			char* xc = calloc(12, sizeof(char));
			char* yc = calloc(12, sizeof(char));
			sprintf(xc, "%d", x);
            sprintf(yc, "%d", y);
			//printf("%s %s\n", xc, yc);
			find_min(find_name(xc), find_name(yc), 0);
			free(xc);
			free(yc);
		}
		last = clock();
		printf("%ld\n", last - first);
		summ += last - first;
		free_graph();
		table = 0;
	}
	printf("Mid: %d: %ld\n", cnt, (summ / c));
	return 0;
}

int send_to_file()
{
	if (!table) return 1;
	FILE* fp = fopen(FILENAME, "w+");
	if (!count) return 1;
	fwrite(&count, sizeof(int), 1, fp);
	for (int i = 0; i < count; i++)
	{
		node_t* node = table[i];
		if (!node) 
		{
			fclose(fp);
			remove(FILENAME);
			return 2;
		}
		fwrite(&(node->x), sizeof(int), 1, fp);
		fwrite(&(node->y), sizeof(int), 1, fp);
		int len = strlen(node->info);
		fwrite(&len, sizeof(int), 1, fp);
		fwrite(node->info, sizeof(char), len, fp);
	}
	for (int i = 0; i < count; i++)
    {
        node_t* now = table[i];
        for (int i1 = 0; i1 < now->degree; i1++)
        {
            edge_t* edge = now->next[i1];
            if (edge)
            {
                if (edge->start && edge->end && edge->start->info && edge->end->info)
                {
					int len1 = strlen(edge->start->info);
					int len2 = strlen(edge->end->info);
					fwrite(&len1, sizeof(int), 1, fp);
					fwrite(edge->start->info, sizeof(char), len1, fp);
					fwrite(&len2, sizeof(int), 1, fp);
					fwrite(edge->end->info, sizeof(char), len2, fp);
				}
            }
        }
    }
	fclose(fp);
}

int load_from_file()
{
	if (access(FILENAME, F_OK) == -1) return 2;
	FILE* fp = fopen(FILENAME, "r");
	if (fp == NULL) return 2;
	int c;
	fread(&c, sizeof(int), 1, fp);
	for (int i = 0; i < c; i++)
	{
		int x;
		int y;
		int len;
		fread(&x, sizeof(int), 1, fp);
		fread(&y, sizeof(int), 1, fp);
		fread(&len, sizeof(int), 1, fp);
		char info[len];
		fread(info, sizeof(char), len, fp);
		add_node(x, y, info, len);
	}
	while (!feof(fp))
	{
		int len1;
		int len2;
		fread(&len1, sizeof(int), 1, fp);
		char info_start[len1];
		fread(info_start, sizeof(char), len1, fp);
		fread(&len2, sizeof(int), 1, fp);
		char info_end[len2];
		fread(info_end, sizeof(char), len2, fp);
		add_edge(find_name(info_start), find_name(info_end));
	}
	fclose(fp);
	return 0;
}

int print_menu()
{
	printf("%s\n", "1> ADD EPON|NODE");
	printf("%s\n", "2> ADD MICROSOFT");
	printf("%s\n", "3> REMOVE KEBAB");
	printf("%s\n", "4> PORISOVAT\'");
	printf("%s\n", "5> RANDOM.ORG");
	printf("%s\n", "6> LEAST FILE PATH");
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

int is_digit(char* input)
{
        int length = strlen(input) - 1;
        if (length == 0) return 0;
	for (int i = 0; i < length; i++)
                if (!isdigit(input[i]))
                {
                        return 0;
                }
        return 1;
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
		printf("INPUT X: ");
        fgets(input, 20, stdin);
        int x = atoi(input);
		if (!is_digit(input))
        {
            printf("INCORRECT INPUT\n\n");
            free(input);
            return 1;
        }
		printf("INPUT Y: ");
        fgets(input, 20, stdin);
        int y = atoi(input);
        if (!is_digit(input))
        {
            printf("INCORRECT INPUT\n\n");
            free(input);
            return 1;
        }
		printf("INPUT INFO: ");
		fgets(input, 20, stdin);
        clear_fgets(input);
		int ret = add_node(x, y, input, strlen(input));
		if (ret == 2) printf("ALREADY EXISTS\n");
		if (ret == 3) printf("INVALID SIZE\n");
		if (ret == 4) printf("ALLOCATION PROBLEM\n");
	}
	if (action_number == 2)
	{
		if (!table)
		{
			free(input);
			printf("TABLE CLEAR\n\n");
			return 1;
		}
		printf("INPUT START INFO: ");
        fgets(input, 20, stdin);
        clear_fgets(input);
		node_t* n1 = find_name(input);
		if (n1 == NULL + 2)
		{
			free(input);
			printf("MEM NEPON\n\n");
			return 1;
		}
		if (!n1)
		{
			free(input);
			printf("NOT FOUND\n");
			return 1;
		}
		printf("INPUT END INFO: ");
        fgets(input, 20, stdin);
        clear_fgets(input);
        node_t* n2 = find_name(input);
		if (n2 == NULL + 2)
		{
			free(input);
			printf("MEM NEPON\n\n");
            return 1;
		}
		if (!n2)
        {
			free(input);
            printf("NOT FOUND\n\n");
            return 1;
        }
		int ret = add_edge(n1, n2);
		if (ret == 1) printf("TABLE CLEAR\n");
		if (ret == 2) printf("ALREADY EXISTS\n");
		if (ret == 4) printf("ALLOCATION PROBLEM\n");
	}
	if (action_number == 3)
	{
		if (!table)
        {
			free(input);
            printf("TABLE CLEAR\n");
            return 1;
        }
        printf("INPUT START INFO: ");
        fgets(input, 20, stdin);
        clear_fgets(input);
		int ret = rm(input);
		if (ret == 1) printf("TABLE CLEAR\n");
		if (ret == 2) printf("INDEX OUT OF RANGE\n");
	}
	if (action_number == 4)
	{
		int ret = graph_to_file();
		if (ret == 1) printf("TABLE CLEAR\n");
		if (ret == 2) printf("INDEX OUT OF RANGE\n");
		if (ret == 3) printf("NULL INFO\n");
	}
	if (action_number == 5)
	{
		random_graph();
	}
	if (action_number == 6)
	{
		if (!table)
        {
			free(input);
            printf("TABLE CLEAR\n\n");
            return 1;
        }
        printf("INPUT START INFO: ");
        fgets(input, 20, stdin);
        clear_fgets(input);
        node_t* n1 = find_name(input);
        if (n1 == NULL + 2)
        {
			free(input);
            printf("MEM NEPON\n\n");
            return 1;
        }
        if (!n1)
        {
			free(input);
            printf("NOT FOUND\n");
            return 1;
        }
		printf("INPUT END INFO: ");
        fgets(input, 20, stdin);
        clear_fgets(input);
        node_t* n2 = find_name(input);
        if (n2 == NULL + 2)
        {
			free(input);
            printf("MEM NEPON\n\n");
            return 1;
        }
        if (!n2)
        {
			free(input);
			printf("NOT FOUND\n\n");
            return 1;
        }
        int ret = find_min(n1, n2, 1);
	}
	if (action_number == 7)
	{
		send_to_file();
		free(input);
		free_graph();
		exit(0);
	}
	free(input);
    printf("\n");
	return 0;
}

int main()
{
	/*add_node(12, 12, "1", 1);
	add_node(12, 20, "2", 1);
	add_node(20, 40, "3", 1);
	add_node(20, 12, "4", 1);
	add_node(30, 12, "5", 1);
	add_edge(find_name("1"), find_name("2"));
	add_edge(find_name("2"), find_name("3"));
	add_edge(find_name("1"), find_name("4"));
	add_edge(find_name("4"), find_name("5"));
	add_edge(find_name("5"), find_name("3"));*/
	
	/*for (int i = 1; i < 10; i++)
		timing(i * 30);
	*/
	load_from_file();
	while(1)
    {
		print_menu();
        action();
    }
}







