#include <stdio.h>
#include <stdlib.h>

void non_stdio_test();
void non_stdio_test_with_optimization();
int stdio_test(int A[], int n);

int main(){
    //non_stdio_test_with_optimization();
    int A[] = {1, 2, -1, -1, 2, 3, 3, };
    int result = stdio_test(A, sizeof A/sizeof(int));
    printf("The number appears only once is --- %i\n", result);

    return 0;
}
int stdio_test(int A[], int n){
    if ( n <= 0){
        printf("Invalid array length\n");
        return -1;
    }
    int result = 0;
    while( n-- ){ 
        result ^= A[n];
    }
    return result; 
}
void non_stdio_test(){
    int count = 0;
    int *array = (int *)malloc(count * sizeof(int));
    printf("Please input the number count of the array: "); 
    scanf("%i", &count);
    int i = 0;
    int result = 0;
    while( i++ != count){ 
        printf("Input a value in sequence : ");
        scanf("%i", array + i - 1);
        printf("Please show me the i value --- %i\n", i);
        result ^= array[i - 1];
    }
    printf("Please show me the result --- %i\n", result);
}

void non_stdio_test_with_optimization(){
    int count = 0;
    printf("Please input the length of the array: "); 
    scanf("%i", &count);
    if (count <= 0){
        printf("Invalid array length\n");
        return;
    }
    int tmp = 0;
    int result = 0;
    while( count-- ){ 
        printf("Input a value of the array in sequence : ");
        scanf("%i", &tmp);
        result ^= tmp;
    }
    printf("The number appears only once is --- %i\n", result);
}
