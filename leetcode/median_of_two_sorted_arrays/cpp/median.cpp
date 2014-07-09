#include <iostream>
#define DEBUG
using namespace std;

class Solution {
	public:
        double findMedianSortedArrays(int A[], int m, int B[], int n);
};

double Solution::findMedianSortedArrays(int A[], int m, int B[], int n) {
    int extra = 0;
    if ((m+n)%2 == 0) extra = 0;
    else  extra = 1;
    int steps =  ((m+n) >> 1) + 1;
    int i = 0, j = 0;
    int count = 0, flag = -1, last = -1;
    while ( (count < steps) && (count < (m+n))) {
        last = flag;
        if ( (i < m) && (j < n)) {
            if (A[i] <= B[j]) {
                flag = 0; i ++; 
            } else {
                flag = 1; j ++; 
            }
        } else if ( i < m) {
            flag = 0; i ++; 
        } else if ( j < n) {
            flag = 1; j ++;
        }
        count ++;
    }
    int left = 0, right = 0;
    if (extra == 0) {
        if (flag == 0) right = A[i-1];
        else right = B[j-1];
        if (last == -1) left = right;
        else if (last == flag) {
            if (last == 0) left = A[i-2];
            else left = B[j - 2];
        } else if (last == 0) left = A[i-1];
        else if (last == 1) left = B[j-1];
        return ((double)left + right)/2;
    } else {
        if ((flag == 0) && (last == -1)) return A[i-1];
        else if ((flag == 1) && (last == -1)) return B[j-1];
        else if ((flag == 0) && (last == 0)) return A[i-1];
        else if ((flag == 0) && (last == 1)) return A[i-1];
        else if ((flag == 1) && (last == 0)) return B[j-1];
        else if ((flag == 1) && (last == 1)) return B[j-1];
        else return -1;
    }
}

int main(int argc, char *argv[]) {
    //int A[] = {1, 2, 9, 18};
    //int B[] = {-91, 2, 10, 20};
    int A[] = {};
    int B[] = {1};
    //int A[] = {};
    //int B[] = {1, 2, 3, 4, 5};
    //int A[] = {1, 2};
    //int B[] = {1, 2, 3};
    Solution s;
    cout << s.findMedianSortedArrays(A, sizeof(A)/sizeof(int), B, sizeof(B)/sizeof(int)) 
        << "   expected   " <<  5.5 << endl;
	return 1;
}
