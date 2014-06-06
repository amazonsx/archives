#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#define DEBUG_INITG  
//#define DEBUG_FILLDICT
//#define DEBUG_CALANDPRINT 
#define DEBUG_FIND_LADDERS

typedef struct word_vertice_t{
	int index; // index of this node in one dimension of graph
	char *word;
	int *parent_list;
	int parent_count;
	int len; // path length
	int mark;
} word_vertice_t;

typedef struct word_ladder{
	struct word_ladder *next;
	char *word;
} word_ladder;

typedef struct word_ladder_table{
	word_ladder *sentinel;
	struct word_ladder_table *next;
} word_ladder_table;

int** initg(char *start, char *end, char *dict[], int dict_len, int **g, word_vertice_t *v_table);
int** filldict(int dict_len, int **g, word_vertice_t *v_table);
word_ladder_table* calandprint(int dict_len, int **g, word_vertice_t *v_table, word_ladder_table* head);
word_ladder_table* record( word_vertice_t *v_table, int source_index, int current_index, word_ladder_table *ladder_head, word_ladder_table *ladder_tail);
word_ladder_table* findladders(char *start, char *end, char *dict[], int dict_len, word_ladder_table *ladder_head);


int** initg(char *start, char *end, char *dict[], int dict_len, int **g, word_vertice_t *v_table)
{
	int g_v_count = dict_len + 2;
	int i = 0;
	
	char *word;

	for(i=0; i < g_v_count; i ++) {
		*(g+i) = (int *)malloc( sizeof(int) * g_v_count);
		if (i == 0){
			word = start;
		}else if (i == (g_v_count - 1)){
			word = end;
		}else{
			word = *(dict + i - 1);
		}
		v_table[i] = (word_vertice_t){i, word, (int *)malloc( sizeof(int)*(g_v_count-1)), 0, g_v_count, 0};
	}
	v_table[0].len = 0;
#ifdef DEBUG_INITG
	for(i = 0; i < g_v_count; i ++)
		printf("created graph vertice : %s\n", (v_table + i)->word); 
	printf("The G has nodes: %i", i);
#endif
		
	return g;
}

int** filldict(int dict_len, int **g, word_vertice_t *v_table){
	int g_v_count = 2 + dict_len;
	int i, j, k, diff= 0;
	char *s, *d;
	int word_len = strlen(v_table[0].word); 
	for(i = 0; i < g_v_count; i ++) {
		s = v_table[i].word;
		for ( j = i + 1; j < g_v_count; j ++) {
			diff = 0;
			d = v_table[j].word;
			for(k = 0; k < word_len ; k ++) {
				if (*(s+k) != *(d+k))
					diff ++;
			}
			if (diff == 1){
				g[i][j] = 1;
				g[j][i] = 1;
			}
		}
	}
#ifdef DEBUG_FILLDICT
	for( i = 0; i < g_v_count; i ++) {
		for ( j = 0; j < g_v_count; j ++) {
			printf("%i", g[i][j]);
			printf("%s", " ");
		}
		printf("\n");
	}
#endif
	return g;
}

void print_debug( word_vertice_t *v_table, int source_index, int current_index, int depth, int word_len){
	if (source_index == current_index)	
		printf("%s\n", v_table[current_index].word);
	else if( v_table[current_index].parent_count == 0)
		printf("no path\n");
	else{
		printf("%s->", v_table[current_index].word);
		int i = 0, j = 0;
		for(i=0; i < (v_table + current_index)->parent_count; i ++){
			if (i != 0){
				for(j = 0; j < depth*(word_len + 2); j++)
					printf(" ");
			}
			print_debug(v_table, source_index, *((v_table + current_index)->parent_list + i), depth + 1, word_len);
		}
	}
}

word_ladder_table* record( word_vertice_t *v_table, int source_index, int current_index, word_ladder_table *ladder_head, word_ladder_table *ladder_tail){
	if (source_index == current_index){
		word_ladder *source = (word_ladder *)malloc(sizeof(word_ladder));
		*source = (word_ladder){ ladder_head->sentinel, v_table[current_index].word};
		ladder_head->sentinel = source;
		//printf("%s\n", v_table[current_index].word);
	}else if( v_table[current_index].parent_count == 0){
		//printf("no path\n");
	}else{
		//printf("%s->", v_table[current_index].word);
		word_ladder *current = (word_ladder *)malloc(sizeof(word_ladder));
		*current = (word_ladder){ ladder_head->sentinel, v_table[current_index].word};
		ladder_head->sentinel = current;
		int i = 0;
		for(i=0; i < (v_table + current_index)->parent_count; i ++){
			word_ladder_table *cpy_ladder_head = NULL;
			if (i != 0){
				cpy_ladder_head = (word_ladder_table*)malloc(sizeof(word_ladder_table));
				*cpy_ladder_head = (word_ladder_table){ current, NULL};
				ladder_tail->next = cpy_ladder_head;
				ladder_tail = cpy_ladder_head;
			}else{
				cpy_ladder_head = ladder_head;
			}
			ladder_tail = record(v_table, source_index, *((v_table + current_index)->parent_list + i), cpy_ladder_head, ladder_tail);
		}
	}
	return ladder_tail;
}

word_ladder_table* calandprint(int dict_len, int **g, word_vertice_t *v_table, word_ladder_table* ladder_head){
	int i = 0;
	int g_v_count = dict_len + 2;
	int current_sp_len = g_v_count;
	int current_min_index = g_v_count;
	int fin_flag = 0;
	int seg_len = 0;

	while (fin_flag != g_v_count){
		current_sp_len = g_v_count;
		for(i = 0; i < g_v_count; i ++){
			if(v_table[i].mark)
				continue;
			if(v_table[i].len < current_sp_len){
				current_sp_len = v_table[i].len;
				current_min_index = i;
			}
		}
		v_table[current_min_index].mark = 1;
		for(i=0; i < g_v_count; i ++) {
			seg_len = g[current_min_index][i];
			if(seg_len == 1){
				if((v_table[current_min_index].len + seg_len) < v_table[i].len) {
					v_table[i].parent_count = 1;
					v_table[i].parent_list[0] = current_min_index;
					v_table[i].len = v_table[current_min_index].len + 1;
				}else if( (v_table[current_min_index].len + seg_len) ==  v_table[i].len) {
					v_table[i].parent_count ++;
					v_table[i].parent_list[v_table[i].parent_count - 1] = current_min_index;
				}else
					continue;
			}
		}
		fin_flag ++;
	}
#ifdef DEBUG_CALANDPRINT
	int word_len = strlen(v_table[0].word);
	for(i = 0; i < g_v_count; i ++){
		print_debug(v_table, 0, i, 1, word_len);
	}
#endif /* DEBUG_CALANDPRINT */
	record(v_table, 0, g_v_count - 1, ladder_head, ladder_head);
	
	return ladder_head;
}

word_ladder_table* findladders(char *start, char *end, char *dict[], int dict_len, word_ladder_table *ladder_head){
	int **g = NULL;
	word_vertice_t *v_table = NULL;

	g = (int **)malloc(sizeof(int*) * (dict_len + 5));
	v_table = (word_vertice_t *)malloc( sizeof(word_vertice_t) * (dict_len + 2));
	g = initg(start, end, dict, dict_len, g, v_table);
	g = filldict(dict_len, g, v_table);
	ladder_head = calandprint(dict_len, g, v_table, ladder_head);

	word_ladder_table *cursor = ladder_head;
	word_ladder *path_node;
	while (cursor != NULL){
		path_node = cursor->sentinel;
		while(path_node != NULL){
			printf("%s ", path_node->word);
			path_node = path_node->next;
		}
		printf("\n");
		cursor = cursor->next;

	}
	
	return ladder_head;
}

int main(int argc, char *argv[])
{
	char *start= "hit";
	char *end="cog";
	char *dict[] = {"hot", "dot", "dog", "lot", "log"};
	int dict_len = 5;
	word_ladder_table ladder = (word_ladder_table){NULL,NULL};
	word_ladder_table *ladder_head = NULL;
	ladder_head = &ladder;
	findladders(start, end, dict, dict_len, ladder_head);
	return 0;
}
