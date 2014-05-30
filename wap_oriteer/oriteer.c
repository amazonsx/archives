#include <stdio.h>
#include <stdlib.h>

#define WIDTH_MAX 100
#define HEIGHT_MAX 100
#define HOP_MAX 18

typedef struct vertex{
	int x;
	int y;
	int type; //0:source node; 1: normal node; 2: destination node.
	int index; // index in the graph array.
	struct vertex *left_kid;
	struct vertex *right_sibling;
} vertex;

/*
 * transform the input text to a computable graph
 * in adjcent matrix without vertex S
 */
int input_map_init(int h, int w, int **graph, vertex *ver_arr){
	return 1;
}

/*
 * Generate 
 * adjecent vertices
 */
int prim_tree_modified(int **graph, vertex *ver_arr, vertex *tree_root){
	return 1;
}


int main(){
	return 0;
}

