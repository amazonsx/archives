#include <iostream>
#define DEBUG
using namespace std;

class Solution {
	public:
        int maxSubArray(int A[], int n);
};

int Solution::maxSubArray(int A[], int n) {
    int *max_sum = new int[n];
    int max = 0;
    for ( int i = 0; i < n; i ++) {
        max_sum[i] = A[i];
        if (( i >= 1) && (max_sum[i-1] > 0)) {
            max_sum[i] += max_sum[i-1];
        }
        if ( i == 0) max = max_sum[0];
        if (max_sum[i] > max) max = max_sum[i];
    }
    delete[] max_sum;
    return max;
}


int main(int argc, char *argv[]) {
    int arr[] = {-2,1,-3,4,-1,2,1,-5,-4};
    Solution s;
    cout << s.maxSubArray(arr, sizeof(arr)/sizeof(int)) << endl;
	return 1;
}
