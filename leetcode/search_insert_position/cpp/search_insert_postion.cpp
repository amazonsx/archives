#include <iostream>
#define DEBUG
using namespace std;

class Solution {
	public:
		int searchInsert(int A[], int n, int target);
};

int Solution::searchInsert(int A[], int n, int target) {
	if ( n == 0 ) return 0;
	for ( int i = 0; i < n; i ++) {
		if (target <= A[i]) return i;
	}
	return n;
}

int main(int argc, char *argv[]) {
	return 1;
}
