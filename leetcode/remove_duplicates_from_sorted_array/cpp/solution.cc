#include <iostream>
#define DEBUG
using namespace std;

class Solution {
public:
    int removeDuplicates(int A[], int n);
};

int Solution::removeDuplicates(int A[], int n) {
    if (n <= 1) return n;
    int j = 0;
    for ( int i = 1; i < n; i ++) {
        if (A[i] != A[j]) {
            A[++j] = A[i];
        }
    }
    return j+1;
}

int main(int argc, char *argv[]) {
    //int A[] = { -3, -1, 0, 0, 1, 3, 3, 4, 4, 4, 4 };
    int A[] = { -3, -1, 0, 0};
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

