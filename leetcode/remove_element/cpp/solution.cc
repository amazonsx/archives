#include <iostream>
#define DEBUG
using namespace std;

class Solution {
public:
    int removeElement( int A[], int n, int elem);
};

int Solution::removeElement( int A[], int n, int elem) {
    int end = n - 1;
    int i = 0;
    while (i <= end) {
        if (A[i] == elem) {
            while (A[end] == elem)  end --;
            if (end < i)    break;
            A[i] = A[end--];
        }
        i ++;
    }
    return end + 1;
}

int main(int argc, char *argv[]) {
    int A[] = {1, 2, 3, 5, 8, 7 , 2, 3, 5, 2, 12, 89};
    for ( int i = 0; i < (signed)(sizeof(A)/sizeof(int)); i ++)
        cout << A[i] << "  ";
    cout << endl;
    Solution s;
    int len = s.removeElement(A, sizeof(A)/sizeof(int),3);
    cout << len << endl;
    for ( int i = 0; i < len; i ++)
        cout << A[i] << "  ";
    cout << endl;
	return 1;
}
