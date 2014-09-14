#include <iostream>
#include <queue>
#define DEBUG
using namespace std;

class Solution {
public:
    int removeDuplicates(int A[], int n);
};

int Solution::removeDuplicates(int A[], int n) {
    int count = 0;
    int len = 0;
    int i = 0;
    queue<int> loc;
    while ( i < n ) {
        if (count == 0) {
            count = 1;
        } else {
            if (count == 1) {
                if ( A[i] == A[i-1] )    count ++;
            } else {
                if ( A[i] != A[i-1] ) {
                    count = 1;
                } else {
                    loc.push(i);
                    len ++;
                }
            }
        }
        i  ++;
    }
    i = 0;
    int pos = 0;
    while ( i < n ) {
        if ( loc.empty())   break;
        if ( i == loc.front()) {
            loc.pop();
            int j = i + 1;
            int end = n;
            if ( !loc.empty() ) {
                if ( loc.front() < end)  end = loc.front();
            }
            while ( j < end) {
                A[pos++] = A[j++];
            }
            i = loc.front();
            continue;
        }
        i ++;
        pos ++;
    }
    return n - len;
}

int main(int argc, char *argv[]) {
    int arr[] = {1, 1, 1, 2};
    //int arr[] = {1, 1, 1, 1, 3, 3};
    for ( int i = 0; i < (signed)(sizeof(arr)/sizeof(int)); i ++) {
        cout << arr[i] << "  ";
    }
    cout << endl;

    Solution s;
    int n =  s.removeDuplicates(arr, sizeof(arr)/sizeof(int));

    for ( int i = 0; i < n; i ++) {
        cout << arr[i] << "  ";
    }
    cout << endl;
	return 1;
}
