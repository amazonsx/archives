#include <iostream>
#define DEBUG
using namespace std;

class Solution {
public:
    void merge( int A[], int m, int B[], int n);
};

void Solution::merge( int A[], int m, int B[], int n) {
    if (n == 0)     return;
    int current = m + n - 1;
    int i = m - 1, j = n -1;
    while ( (i >= 0) && (j >= 0)) {
        if (A[i] >= B[j]) {
            A[current] = A[i];
            i --;
        } else {
            A[current] = B[j];
            j --;
        }
        current --;
    }
    while ( i >= 0) {
        A[current] = A[i];
        i --;
        current --;
    }
    while ( j >= 0) {
        A[current] = B[j];
        j --;
        current --;
    }
}

int main(int argc, char *argv[]) {
    int arr1[] = {1, 2, 5, 7, 8, 12, 25, 0, 0, 0, 0, 0};
    int arr2[] = {4, 5, 6, 7, 28};
    Solution s;
    s.merge(arr1, sizeof(arr1)/sizeof(int) - sizeof(arr2)/sizeof(int), arr2, sizeof(arr2)/sizeof(int));
    for ( int i = 0; i < (signed)(sizeof(arr1)/sizeof(int)); i ++)
        cout << arr1[i] << "   ";
    cout << endl;

    
	return 1;
}
