#include <iostream>
#define DEBUG
using namespace std;

class Solution {
	public:
        int firstMissingPositive(int A[], int n);
};
int Solution::firstMissingPositive(int A[], int n) {
    int missing_positive_sum = 0, positive_sum = 0;
    int positive_count = 0;
    for ( int i = 0; i < n; i ++ ) {
       if (A[i] > 0) {
           missing_positive_sum += A[i]; 
           positive_count ++;
       }
    }
    positive_sum = ((1 + positive_count)*positive_count)>>1;
    int diff = positive_sum - missing_positive_sum;
    if (diff > 0)   return diff;
    else if (diff == 0) return positive_count+1;
    else return diff + positive_count + 1;
}

int main(int argc, char *argv[]) {
    Solution s;
    //int arr[] = {3, 4, -1, 1};
    int arr[] = {1,1,3,4,-1,0};
    cout << s.firstMissingPositive(arr, sizeof(arr)/sizeof(int)) << endl;
	return 1;
}
