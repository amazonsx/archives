#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#define DEBUG
using namespace std;

class Solution {
    public:
        int trap( int A[], int n);
};

int Solution::trap( int A[], int n) {
    if ( n < 3)    return 0;
    int left = -1, right = -1;
    vector<int> trap;
    for ( int i = 1; i < n; i ++ ) {
        if ( A[i] < A[i-1] ) {
            if ( right != -1) {
                if ( trap.empty()) {
                    trap.push_back(left);
                }
                assert(A[left] == A[trap.back()]);
                trap.push_back(right);
                left = -1;
                right = -1;
            }
            if ( left == -1)    left = i-1;
        } else if ( A[i] > A[i-1] ) {
            if ( left != -1) {
                right = i;
            }
        }
    }
    if ( (left != -1) &&  (right != -1) ) {
        if ( trap.empty()) {
            trap.push_back(left);
        }
        assert(A[left] == A[trap.back()]);
        trap.push_back(right);
    } 
    if ( trap.empty() ) return 0;
    while (true) {
        vector<int>::iterator iter = trap.begin()+1;
        bool flag = true;
        while (iter != trap.end() ) {
            if ( (iter + 1) != trap.end() ) {
                if ( (A[*iter] <= A[*(iter+1)] ) && (A[*iter] <= A[*(iter-1)] )) {
                    iter = trap.erase(iter);
                    flag = false;
                } else iter ++;
            } else iter ++;
        }
        if ( flag)  break;
    }
    int volume = 0;
    for ( int i = 0; i < (signed)trap.size()-1; i ++ ) {
        int minHeight = min(A[trap[i]], A[trap[i+1]] );    
        for ( int j = trap[i]; j <= (signed)trap[i+1]; j ++) {
            if (A[j] >= minHeight)    continue;
            volume += minHeight - A[j];
        }
    }
    return volume;
}

int main(int argc, char *argv[]) {
    //int arr[] = {8,8,1,5,6,2,5,3,3,9};  //31
    //int arr[] = {0,1,0,2,1,0,1,3,2,1,2,1}; //6
    //int arr[] = {2, 0, 2}; // 2
    //int arr[] = {5,2,1,2,1,5};    //14
    //int arr[] = {6,4,2,0,3,2,0,3,1,4,5,3,2,7,5,3,0,1,2,1,3,4,6,8,1,3};    //83
    //int arr[] = {0, 2, 0};    //0
    //int arr[] = {9,6,8,8,5,6,3};
    Solution s;
    cout << s.trap(arr, sizeof(arr)/sizeof(int) )  << endl;
    return 1;
}
