#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    vector<int> searchRange( int A[], int n, int target);
    int findLeft( int A[], int left, int right, int target);
    int findRight( int A[], int left, int right, int target);
};

int Solution::findLeft( int A[], int left, int right, int target) {
    if ( left > right)  return -1;
    if ( left == right) {
        if ( A[left] == target) return left;
    }
    int mid = (left + right) >> 1;
    if ( A[mid] < target) {
        return findLeft( A, mid+1, right, target);
    } else {
        int next = findLeft( A, left, mid-1, target);
        if ( next == -1)    return mid;
        else return next;
    }
}

int Solution::findRight( int A[], int left, int right, int target) {
    if ( left > right)  return -1;
    if ( left == right) {
        if ( A[left] == target) return left;
    }
    int mid = (left + right) >> 1;
    if ( A[mid] > target) {
        return findRight( A, left, mid-1, target);
    } else {
        int next = findRight( A, mid+1, right, target);
        if ( next == -1)    return mid;
        else    return next;
    }
}
    
vector<int> Solution::searchRange( int A[], int n, int target) {
    vector<int> res;
    int left = 0, right = n-1;
    int mid = (left + right) >> 1;
    while ( left < right ) {
        mid = (left + right) >> 1;
        if ( A[mid] == target) {
            left = findLeft( A, left, mid, target);
            right = findRight( A, mid, right, target);
            break;
        } else if ( A[mid] > target ) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    if ( left > right) {
        left = -1;
        right = -1;
    } else if ( left == right) {
        if (A[left] != target) {
            left = -1;
            right = -1;
        }
    }
    res.push_back(left);
    res.push_back(right);
    return res;
}

int main(int argc, char *argv[]) {
    //int arr[] = { 5, 7, 7, 8, 8, 10};
    int arr[] = { 1,2,3,3,3,3,4,5,9};
    Solution s;
    int target = 3;
    vector<int> res = s.searchRange( arr, sizeof(arr)/sizeof(int), target);
    cout << res[0] << "  " << res[1] << endl;
	return 1;
}

