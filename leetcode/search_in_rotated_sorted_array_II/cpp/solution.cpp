#include <iostream>
#define DEBUG
using namespace std;

class Solution {
    private:
        bool binarySearch(int A[], int n, int target);
	public:
        bool search(int A[], int n, int target);
};

bool Solution::binarySearch(int A[], int n, int target) {
    bool res = false;
    int start = 0, end = n - 1, mid = 0;
    int larger_min = A[start], smaller_max = A[end];     
    while ( start <= end) {
        larger_min = A[start];
        smaller_max = A[end];
        mid = (start + end)/2;
        int flag = larger_min < smaller_max ? 0 : 1;
        if ( (target < larger_min) && (target > smaller_max)) return false;
        int mid_value = A[mid];
        if ( (target == larger_min) 
                || (target == smaller_max) 
                || (target == mid_value)) return true;
        if ( (target > larger_min)) {
            if ( target < mid_value) { 
                end = mid - 1;
            } else {
                if ( !flag || (mid_value > smaller_max)) start = mid + 1;
                else if ( mid_value < smaller_max) end = mid - 1;
                else  {
                    int is_increasing = 1;
                    for ( int i = start; i < mid; i ++) {
                        if (A[i] > mid_value)  {
                            is_increasing = 0;
                            break;
                        }
                    }
                    if (is_increasing)  start = mid + 1;  
                    else    end = mid - 1;
                }
            }
        } else if ( target < smaller_max) {
            if ( target > mid_value) start = start + 1;
            else {
                if ( flag && (mid_value > larger_min)) start = mid + 1;
                else if ( mid_value < larger_min) end = mid - 1;
                else {
                    int is_increasing = 1;
                    for ( int i = mid+1; i <= end; i++ ){
                        if (A[i] < mid_value) {
                            is_increasing = 0;
                            break;
                        }
                    }
                    if (is_increasing)    end = mid - 1;
                    else    start = mid + 1;
                }
            }
        }
    }
    return res;
}

bool Solution::search(int A[], int n, int target) { 
    bool res = binarySearch(A, n, target);
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    int A[] = {1, 8, 8, 12,12, 42, -1, 0, 1, 1};
    //int A[] = {1};
    cout << "expected val-----" << 1;
    cout << s.search(A, sizeof(A)/sizeof(int), 8) << endl;

    cout << "expected val-----" << 7;
    cout << s.search(A, sizeof(A)/sizeof(int), 0) << endl;

    cout << "expected val-----" << 0;
    cout << s.search(A, sizeof(A)/sizeof(int), 3) << endl;

    cout << "expected val-----" << 9;
    cout << s.search(A, sizeof(A)/sizeof(int), 1) << endl;

    cout << "expected val-----" << 6;
    cout << s.search(A, sizeof(A)/sizeof(int), -1) << endl;
    cout << "expected val-----" << -1;
    cout << s.search(A, sizeof(A)/sizeof(int), 23) << endl;

    cout << "expected val-----" << -1;
    cout << s.search(A, sizeof(A)/sizeof(int), 50) << endl;

    cout << "expected val-----" << -1;
    cout << s.search(A, sizeof(A)/sizeof(int), 2) << endl;

    cout << "expected val-----" << -1;
    cout << s.search(A, sizeof(A)/sizeof(int), -8) << endl;
	return 1;
}
