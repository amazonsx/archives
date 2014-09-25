#include <iostream>
#include <assert.h>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
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
    int right = left + (((m+n)%2==0)?1:0);
    return (mergeArray[left]+mergeArray[right])/2;
}

double Solution::findMedianSortedArrays(int A[], int m, int B[], int n) {
    cout << m << "   " << n << endl;
    assert( (m > 0) || (n > 0));
    if ( m == 0 || n == 0) {
        int *C = (m == 0)?B:A;
        if ( n%2 == 0) {
            return ((double)C[n/2-1] + C[n/2])/2;
        } else return C[n/2];
    } else if ( m == 1 && n == 1) {
        return ((double)A[0] + B[0])/2;
    } else if ( m == 1 ) {

    } else if ( n == 1 ) {
    }
    int mid1 = m/2 - ((m%2 == 0)?1:0);
    int mid2 = n/2 - ((n%2 == 0)?1:0);
    if (A[mid1] <= B[mid2]) {
        int disposeLen = min( mid1+1, n-mid2-1);
        return findMedianSortedArrays( A+disposeLen, m-disposeLen, B, n-disposeLen);
    } else {
        int disposeLen = min( m-mid1-1, mid2+1);
        return findMedianSortedArrays( A, m-disposeLen, B+disposeLen, n-disposeLen);
    }
    return 0.0;
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
    int A[] = {3};
    int B[] = {1, 2, 4, 5};
    Solution s;
    cout << s.findMedianSortedArraysBruteForce(A, sizeof(A)/sizeof(int), B, sizeof(B)/sizeof(int)) 
        << "   expected   " <<  5.5 << endl;
    cout << s.findMedianSortedArraysMergeAndCount(A, sizeof(A)/sizeof(int), B, sizeof(B)/sizeof(int)) 
        << "   expected   " <<  5.5 << endl;
    cout << s.findMedianSortedArrays(A, sizeof(A)/sizeof(int), B, sizeof(B)/sizeof(int)) 
        << "   expected   " <<  5.5 << endl;
	return 1;
}
