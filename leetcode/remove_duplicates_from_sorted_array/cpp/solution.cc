#include <iostream>
#define DEBUG
using namespace std;

class Solution {
public:
    int removeDuplicates(int A[], int n);
};

int Solution::removeDuplicates(int A[], int n) {
    if (n <= 1) return n;
    int former = A[0];
    int j = 1;
    for ( int i = 1; i < n; i ++) {
        while (A[i] == former) {
            i ++;
        }
        if (i != n){
            A[j] = A[i];
            former = A[j];
            j ++;
        }
    }

    return j;
}

int main(int argc, char *argv[]) {
    //int A[] = { -3, -1, 0, 0 };
    int A[] = { -3, -1, 0, 0, 1, 3, 3, 4, 4, 4, 4 };
    for ( int i = 0; i < (signed)(sizeof(A)/sizeof(int)); i ++)
        cout << A[i] << "  " ;
    cout << endl;

    Solution s;
    int size = s.removeDuplicates(A, sizeof(A)/sizeof(int));
    cout << size << endl;
    for ( int i = 0; i < size; i ++)
        cout << A[i] << "  " ;
    cout << endl;

	return 1;
}
