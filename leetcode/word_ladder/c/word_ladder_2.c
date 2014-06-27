#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Path {
    int similarity;
    int visited;
}Path ;

void cal_similarity(char *dict[], Path **similar_arr, int n);
int find_conversion_path(char *dict[], Path **similar_arr, int n, int src, int path_count);
void backstrap(char *dict[], Path **similar_arr, int n, int cur);

int main(int argc, char *argv[]){
    int n = 7;
    char *dict[] = {"hit", "hot", "dot", "dog", "lot", "log", "cog"};
    //how to initialize a array with two-dimension
    Path **similar_arr = (Path **) malloc(n * sizeof(Path));
    int i = 0, j = 0;
    
    Path temp = {0, 0};
    for (i = 0; i < n; i ++){
        similar_arr[i] = (Path *) malloc(n * sizeof(Path));
        for (j = 0; j < n; j ++){
            similar_arr[i][j] = temp;
        }
    }
    cal_similarity(dict, similar_arr, n);
    int path_count = 0;
    path_count = find_conversion_path(dict, similar_arr, n, 0, path_count);
    printf("The total path num from %s to %s is %i\n", *dict, *(dict + n - 1), path_count);
    if (path_count != 0) {
        backstrap(dict, similar_arr, n, n - 1);
    }

    free(similar_arr);
    return 0;
}

void backstrap(char *dict[], Path **similar_arr, int n, int cur){
    if (cur == n - 1){
        printf("The path is :\n%s ", dict[n - 1]);
    }    
    if (cur == 0){
        printf("\n");
        return;
    }
    int i = 0;
    for(; i < cur; i ++) {
        if (similar_arr[cur][i].visited == 1) {
            printf("%s ", *(dict + i));
            backstrap(dict, similar_arr, n, i);
        }
    }
}

int find_conversion_path(char *dict[], Path **similar_arr, int n, int src, int path_count){
    if (src == (n - 1)){
        return 1;
    }else {
        int i = 0;
        int len = strlen(dict[src]);
        int unsimilar_count = 0;
        for (; i < n; i ++) {
            if (i == src) {
                continue;
            }
            if((similar_arr[src][i].similarity == len - 1)  
                && (similar_arr[i][n - 1].similarity >= similar_arr[src][n - 1].similarity)
                && (similar_arr[src][i].visited == 0) && (similar_arr[i][src].visited == 0)){
                similar_arr[i][src].visited = 1;
                similar_arr[src][i].visited = 1;
                path_count += find_conversion_path(dict, similar_arr, n, i, path_count);
            }else{
                unsimilar_count ++;
            }
        }
        if(unsimilar_count == n ) {
            return 0;
        }
    } 
     
    return path_count;      
}

void cal_similarity(char *dict[], Path ** similar_arr, int n){
    int i = 0, j = 0, k = 0, similarity = 0;
    for(i = 0; i < n; i ++){
        char *src = dict[i]; 
        int len = strlen(src);
        for(j = i; j < n; j ++){
            similarity = 0;
            if(i == j) {
                similarity = 3; 
            }else {
                char *cmp_char = dict[j];
                int cmp_len = strlen(cmp_char);
                if(len != cmp_len){
                    similarity = 0;
                }else {
                    for(k = 0; k < len; k ++){
                        if (src[k] == cmp_char[k]){
                            similarity ++;
                        }
                    }
                }
            }
            similar_arr[i][j].similarity = similarity;
            similar_arr[j][i].similarity = similarity;
        }
    } 
}
