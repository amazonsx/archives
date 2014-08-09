#include <iostream>
#define DEBUG
using namespace std;

class Solution {
    private:
        void quicksort(int *A, int start, int end);
	public:
        int firstMissingPositive(int A[], int n);
};

void Solution::quicksort(int *A, int start, int end) {
    if (start >= end)   return;
    int i = start - 1;
    int j = start;
    int pivot = A[end];
    while (j <= (end - 1)) {
        if (A[j] < pivot) {
            i ++;
            int tmp = A[j];
            A[j] = A[i];
            A[i] = tmp;
        }
        j ++;
    }
    int tmp = pivot;
    A[end] = A[++i];
    A[i] = tmp;
    quicksort(A, start, i-1);
    quicksort(A, i+1, end);
}

int Solution::firstMissingPositive(int A[], int n) {
    if (n == 0) return 1;
    quicksort( A, 0, n-1);
    int firstPositive = 0;
    for (int i = 0; i < n; i ++) {
        if (A[i] > 0) {
            if (firstPositive == 0) {
                firstPositive = A[i];
                if (firstPositive != 1)
                    return 1;
            }
            if ((i+1) < n) {
                if ((A[i+1] - A[i]) > 1)
                    return A[i] + 1;
            }
        }
    }
    return A[n-1] + 1;
}

int main(int argc, char *argv[]) {
    Solution s;
    //int arr[] = {3, 4, -1, 1};
    //int arr[] = {1,1,3,4,-1,0};
    int arr[] = {1, 1000};
    cout << s.firstMissingPositive(arr, sizeof(arr)/sizeof(int)) << endl;
	return 1;
}
