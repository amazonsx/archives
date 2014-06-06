#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode{
    struct ListNode * next;
    //index of the node in the path
    int index; 
}ListNode;

typedef struct CmpInfo{
    //this will be the length of path; 
    //not all path will be fullfilled
    int diff_count;
}CmpInfo;

typedef struct DestAccessable{
    
}DestAcc;

void transform_stepwise_recursion( char **dict, int s_pos, int d_pos, int n, CmpInfo *info);
static CmpInfo *word_cmp(char *source, char *obj, CmpInfo *info);
void backstrap(CmpInfo *info);

int main(){
    int n = 7;
    char *dict[] = {"hit", "hot", "dot", "dog", "lot", "log", "cog"};
    char *source = dict[0];
    char *dest = *(dict + 6);
    

    CmpInfo *res = (CmpInfo *)malloc( n * n * sizeof(CmpInfo)); 
    int i = 0;
    CmpResult tmp = {0, 0, NULL, 0, 0};
    for(i= 0; i < n*n; i++ ){
        *(res + i) = tmp;
    }
    int *path = (int *)malloc(n * n * sizeof(int));
    int j = 0;
    for(j = 0; j < n*n; j ++) {
        *(path + j) = -1;
    }
    transform_stepwise_recursion(0, source, dict, dest, n, res);
    backstrap(res, path, n, 0);
    int k = 0;
    for (j = 0; j < n; j ++){
        for (k; k < n; k ++){
                
        }
    }
    return 0;
}

void transform_stepwise_recursion( int pos, char *source, char **dict, char *dest, int n, CmpResult *res){
    int i = 0;
    int j = 0;
    int index = 0;
    //printf("show me the pos --- %i\n", pos);
 
    for(i = 0; i < n; i ++ ){
        if( *((res + pos*n + i) -> former + i) == 1 ) {
            continue;
        }
        char *obj = *(dict + i); 
        int cmpres = word_cmp(source, obj, &index);
        int *former = NULL;
        switch (cmpres){
            case -2: break;
            case -1: break;
            case 1:
                former = (int *)malloc(n * sizeof(int));
                int tmp = 0;
                for (tmp; tmp < n; tmp ++){
                *(former + i) = 1;
                (res + n*i + pos)->index = index;
                (res + n*i + pos)->cmpres = cmpres;
                (res + n*i + pos)->former = former;
                (res + n*i + pos)->valid = 1;
                (res + n*i + pos)->used = 0;
                *(res + n*pos + i) = *(res + n*i + pos);
                (res + n*pos + i)->former 
                break;
            default:
                break;
        }
    }
    for(i = 0 ; i <n; i ++) {
        if (i == pos) 
            continue;
        if (((res + i + pos*n )->valid == 1) && ((res + i + pos*n)->used ==0)){
            (res + i + pos*n )->used = 1;
            (res + i*n + pos )->used = 1;
            transform_stepwise_recursion(i, *(dict + i), dict, dest, n, res);       
        } 
    }
}
void backstrap(CmpResult *res, int *path, int n, int current_dest, int step, int count){
    int i = 0;
    int j = 0;
    for (i; i < n; i ++){
        CmpResult *c = res + n -1 + i*n;
        if(c->valid == 1) {
            for(j = 0; j < n; j ++) {
                if( *(c->former + j) >= 0) {
                    *(path + i*n + j)= step;
                    backstrap(res, path, j, step -1);
                } 
            }
        }
    } 
}

static int word_cmp(char *source, char *obj, int *index){
    int result = 0;
    int len1 = strlen(source);
    int len2 = strlen(obj);
    if (len1 == len2){
        int i = 0;
        for(i; i< len1; i ++) {
            if (source[i] == obj[i])
                continue;
            result ++;
            *index = i;
        }
    }else {
        result = -1;
    }
    if (result > len1) {
        printf("Something went error with the comparision");
        result =  -2;
    }
    //result means the count of different aphlbet in words
    // -1 means not transformable
    // -2 error
    return result;
}
