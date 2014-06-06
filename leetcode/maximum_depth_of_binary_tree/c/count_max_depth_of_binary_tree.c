#include <stdio.h>
#include <stdlib.h>

struct TreeNode{
   struct TreeNode *left, *right;
    int flag;
};
typedef struct Stack{
    struct TreeNode *current; 
    struct Stack *former;
}Stack;

void build_a_tree(struct TreeNode treeList[], int n);
void non_stdio_test();
int depth_first_traverse_norecuresion(struct TreeNode *head );
int depth_first_traverse_recursion(struct TreeNode *head, int depth);
static int get_max(int a, int b);

int main(){
    non_stdio_test(); 
    return 0; 
}

int depth_first_traverse_norecursion(struct TreeNode *head) {
    int depth = 0;
    if (head) {
        struct Stack *top = (Stack *) malloc(sizeof (Stack));
        top -> current = head;
        top -> former = NULL;
        depth +=1;
        head->flag = 1;
        int tmp_depth = depth; 
        int i = 0;
        while (top) {
            if(top->current->left && (top->current->left->flag==0)){
                struct Stack *left = (struct Stack *) malloc (sizeof (Stack));
                //*left = {top->current->left, top};
                left->current = top->current->left;
                left->former = top;
                top = left;
                top->current->flag = 1;
                tmp_depth += 1;
            } else if(top->current->right && (top->current->right->flag==0)){
                struct Stack *right = (struct Stack *) malloc (sizeof (Stack));
                //*right = {top->current->right, top};
                right->current = top->current->right;
                right->former = top;
                top = right;
                top->current->flag = 1;
                tmp_depth += 1;
            } else {
                depth = get_max(depth, tmp_depth);
                Stack * tmp = top -> former; 
                free(top);
                top = tmp;
                tmp_depth -= 1;
            }
        }       
    }
    return depth;
}
int depth_first_traverse_recursion(struct TreeNode *head, int depth){
    depth += 1;
    if (!(head->left || head->right)) {
        return depth;
    }
    int left_depth = 0, right_depth = 0;
    if (head->left){
        left_depth = depth_first_traverse_recursion(head -> left, left_depth);
    }
    if (head->right ){
        right_depth = depth_first_traverse_recursion(head -> right, right_depth);
    }
    int max_sub_depth = 0;
    max_sub_depth = get_max( left_depth, right_depth);
    return depth + max_sub_depth;
}

void non_stdio_test(){
    int depth = 0;
    struct TreeNode n0 = {NULL, NULL, 0};
    struct TreeNode n1 = {NULL, NULL, 0};
    struct TreeNode n2 = {NULL, NULL, 0};
    struct TreeNode n3 = {NULL, NULL, 0};
    struct TreeNode n4 = {NULL, NULL, 0};
    struct TreeNode treeList[] = {n0, n1, n2, n3, n4};
    build_a_tree(treeList, 5);
    int result = depth_first_traverse_recursion(treeList, depth);
    //int result = depth_first_traverse_norecursion(treeList);
    printf("the max depth is --- %i\n", result);
}

void build_a_tree(struct TreeNode treeList[], int n){
    (*treeList).left = treeList + 2;
    (*treeList).right = treeList + 3;
    (*(treeList + 2)).left = treeList + 1;
    (*(treeList + 1)).right = treeList + 4;
}
static int get_max(int a, int b){
    return a >= b?a:b;
}
