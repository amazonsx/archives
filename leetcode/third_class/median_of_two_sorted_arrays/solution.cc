#include <iostream>
#include <assert.h>
#include <algorithm>
#include <limits>
#include <assert.h>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
private:
    double findKth(int A[], int m, int B[], int n, int k) {
        assert( m > 0 || n > 0);
        if ( m == 0)    return B[k-1];
        if ( n == 0)    return A[k-1];
        if ( k == 1) {
            return min(A[0], B[0]);
        }
        int indexm = (k/2<=m)? k/2-1:m-1;
        int indexn = (k/2<=n)? k/2-1:n-1;
        int a = A[indexm];
        int b = B[indexn];
        if ( a < b) {
            return findKth(A+indexm+1, m-indexm-1, B, n, k-indexm-1);
        } else if (a > b) {
            return findKth(A, m, B+indexn+1, n-indexn-1, k-indexn-1);
        } else {
            if ( k%2 == 0)  return a;
            else return findKth(A+indexm+1, m-indexm-1, B+indexn+1, n-indexn-1, 1);
        }
    }
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n);
    double findMedianSortedArraysBruteForce(int A[], int m, int B[], int n);
    double findMedianSortedArraysMergeAndCount(int A[], int m, int B[], int n);
};
double Solution::findMedianSortedArraysMergeAndCount(int A[], int m, int B[], int n) {
    int i = 0, j = 0;
    int left = ((m+n)>>1) + (((m+n)%2 == 1)?1:0);
    int lastval = 0, count = 0, leftval = 0;
    while ( i < m && j < n) {
        if (A[i] <= B[j]) {
            lastval = A[i];
            i ++;
        } else {
            lastval = B[j];
            j ++;
        }
        count ++;
        if (count == left) {
            if ((m+n)%2 == 1)  return lastval;
            else {
                leftval = lastval;
            }
        } else if (count == left + 1){
            return ((double)leftval + lastval)/2;
        }
    }
    while ( i < m) {
        lastval = A[i];
        i ++;
        count ++;
        if (count == left) {
            if ((m+n)%2 == 1)  return lastval;
            else {
                leftval = lastval;
            }
        } else if (count == left + 1){
            return ((double)leftval + lastval)/2;
        }
    }
    while ( j < n) {
        lastval = B[j];
        j ++;
        count ++;
        if (count == left) {
            if ((m+n)%2 == 1)  return lastval;
            else {
                leftval = lastval;
            }
        } else if (count == left + 1){
            return ((double)leftval + lastval)/2;
        }
    }
    return 0.0;
}

double Solution::findMedianSortedArraysBruteForce(int A[], int m, int B[], int n) {
    vector<int> mergeArray;
    int i = 0, j = 0;
    while ( i < m && j < n) {
        if ( A[i] <= B[j]) {
            mergeArray.push_back(A[i]);
            i ++;
        } else {
            mergeArray.push_back(B[j]);
            j ++;
        }
    }
    while ( i < m ) {
        mergeArray.push_back(A[i]);
        i ++;
    }
    while ( j < n ) {
        mergeArray.push_back(B[j]);
        j ++;
    }
    int left = (m+n)/2;
    int right = left - (((m+n)%2==0)?1:0);
    return ((double)mergeArray[left]+mergeArray[right])/2;
}

double Solution::findMedianSortedArrays(int A[], int m, int B[], int n) {
    assert( m>0 || n > 0);
    if ( (m+n)%2 == 0) {
        return ( findKth(A, m, B, n, (m+n)/2)+
                findKth(A, m, B, n, (m+n)/2+1))/2;
    } else {
        return findKth(A, m, B, n, (m+n)/2+1);
    }
}

int main(int argc, char *argv[]) {
    //int A[] = {1, 2, 9, 18};
    //int B[] = {-91, 2, 10, 20};
    //int A[] = {};
    //int B[] = {1};
    //int A[] = {};
    //int B[] = {1, 2, 3, 4, 5};
    //int A[] = {1, 2};
    //int B[] = {1, 2, 3};
    //int A[] = {1, 1};
    //int B[] = {1, 1};
    //int A[] = {3};
    //int B[] = {1, 2, 4, 5};
    int A[] = {};
    int B[] = {2, 3};
    Solution s;
    cout << s.findMedianSortedArraysBruteForce(A, sizeof(A)/sizeof(int), B, sizeof(B)/sizeof(int)) 
        << "   expected   " <<  5.5 << endl;
    cout << s.findMedianSortedArraysMergeAndCount(A, sizeof(A)/sizeof(int), B, sizeof(B)/sizeof(int)) 
        << "   expected   " <<  5.5 << endl;
    cout << s.findMedianSortedArrays(A, sizeof(A)/sizeof(int), B, sizeof(B)/sizeof(int)) 
        << "   expected   " <<  5.5 << endl;
	return 1;
}
