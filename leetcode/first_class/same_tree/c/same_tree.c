#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DEBUG

//DataStructrue for Binary Tree Node with left-children,right-sibling
//DataStructrue for Binary Tree Node with two children
typedef struct bi_tree_node_t {
	int value;
	struct bi_tree_node_t *left;
	struct bi_tree_node_t *right;
}bi_tree_node_t;

//tree node queue
typedef struct tn_queue_t{
	bi_tree_node_t *first;
	bi_tree_node_t *second;
	struct tn_queue_t *next;
}tn_queue_t;

/*
 * p: first tree
 * q: second tree
 */
bool is_same_tree(bi_tree_node_t *p, bi_tree_node_t *q);

bool is_same_tree(bi_tree_node_t *p, bi_tree_node_t *q){
	
	if( p == q){
#ifdef DEBUG
		printf("p = q\n");
#endif
		return true;
	}else if (!p || !q){
#ifdef DEBUG
		printf("one of q and p is NULL\n");
#endif
		return false;
	}
#ifdef DEBUG
		printf("neither p or q is NULL\n");
#endif
	tn_queue_t *head = NULL, *tail = NULL;

	if(p->value == q->value){
		tn_queue_t *first = (tn_queue_t*)malloc(sizeof(tn_queue_t));
		*first = (tn_queue_t){p, q, NULL};
		head = first;
		tail = first;
	}else {
		free(head);
		return false;
	}	
	bi_tree_node_t *p_cur =NULL, *q_cur= NULL;
	tn_queue_t *tmp = NULL;
	tn_queue_t *current = NULL;

	while(head != NULL){
		current = head;
		p_cur = current->first;
		q_cur = current->second;

		if((p_cur->left != NULL) & (q_cur->left!= NULL)){
			if( p_cur->left->value != q_cur->left->value){
#ifdef DEBUG
				printf("The values are %i vs %i", p_cur->left->value, q_cur->left->value);
#endif
				break;
			}
			tmp = (tn_queue_t*)malloc(sizeof(tn_queue_t));
			*tmp = (tn_queue_t){p_cur->left, q_cur->left, NULL};
			tail->next = tmp;
			tail = tmp;	
		}else if ((p_cur->left == NULL) &(q_cur->left == NULL)){
		}else {
			break;
		}
		if((p_cur->right != NULL) & (q_cur->right!= NULL)){
			if( p_cur->right->value != q_cur->right->value){
#ifdef DEBUG
				printf("The values are %i vs %i", p_cur->right->value, q_cur->right->value);
#endif
				break;
			}
			tmp = (tn_queue_t*)malloc(sizeof(tn_queue_t));
			*tmp = (tn_queue_t){p_cur->right, q_cur->right, NULL};
			tail->next = tmp;
			tail = tmp;	
		}else if ((p_cur->right == NULL) &(q_cur->right == NULL)){
		}else {
			break;
		}
		head = current->next;
		free(current);
	}
	if( head != NULL){
		current = head;
		while(current != NULL){
			tmp = current->next;
			free(current);
			current = tmp;
		}
		head = NULL;
		tail = NULL;
		return false;
	}

	return true;	
}


int main(int argc, char *argv[]){
	bi_tree_node_t p1 = {3, NULL, NULL};
	bi_tree_node_t p2 = {3, NULL, NULL};
	
	bi_tree_node_t q1 = {2, &p1, NULL};
	bi_tree_node_t q2 = {2, NULL, &p2};

	bi_tree_node_t r1 = {1, NULL, &q1};
	bi_tree_node_t r2 = {1, NULL, &q2};
	printf("result ---- %i\n", is_same_tree(&r1, &r2));
	/*
	printf(" NULL vs NULL = : %i\n", is_same_tree(NULL, NULL));

	bi_tree_node_t *p = (bi_tree_node_t*)malloc(sizeof(bi_tree_node_t));
	bi_tree_node_t *q = (bi_tree_node_t*)malloc(sizeof(bi_tree_node_t));
	*p = (bi_tree_node_t){0, NULL, NULL};
	*q = (bi_tree_node_t){0, NULL, NULL};
	printf(" p vs p = : %i\n", is_same_tree(p, p));
	printf(" p vs NULL= : %i\n", is_same_tree(p, NULL));
	printf(" p vs q= : %i\n", is_same_tree(p, q));

	
	*q = (bi_tree_node_t){8, NULL, NULL};
	printf(" p vs q= : %i\n", is_same_tree(p, q));
	
	q->value = 10;

	bi_tree_node_t *tmp_l = p;
	bi_tree_node_t *tmp_r = q;

	int i  = 0;
	for (i = 0; i < 4; i ++){
		int j  = rand();		
		int k = rand()%5;
		if(k == 0)
			break;
		else if (k == 1 || k == 2){
			bi_tree_node_t *a_l = (bi_tree_node_t*)malloc(sizeof(bi_tree_node_t));
			bi_tree_node_t *b_l = (bi_tree_node_t*)malloc(sizeof(bi_tree_node_t));
			*a_l = (bi_tree_node_t){j, NULL, NULL};
			*b_l = (bi_tree_node_t){j, NULL, NULL};
			tmp_l->left = a_l;
			tmp_r->left = b_l;
			tmp_l = a_l;
			tmp_r = b_l;
		}else {
			bi_tree_node_t *a_r = (bi_tree_node_t*)malloc(sizeof(bi_tree_node_t));
			bi_tree_node_t *b_r = (bi_tree_node_t*)malloc(sizeof(bi_tree_node_t));
			*a_r = (bi_tree_node_t){j, NULL, NULL};
			*b_r = (bi_tree_node_t){j, NULL, NULL};
			tmp_l->right = a_r;
			tmp_r->right = b_r;
			tmp_l = a_r;
			tmp_r = b_r;
		}
	}
	printf(" p vs q= : %i\n", is_same_tree(p, q));
	*/
	return 1;
}
