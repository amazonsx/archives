#include <iostream>
#define DEBUG
using namespace std;

class Solution {
	public:
        int singleNumber(int A[], int n);
};
int Solution::singleNumber(int A[], int n) {
    int ones = 0, twos = 0, threes = 0;
    for ( int i = 0; i < n; i ++ ) {
        twos |= (ones & A[i]);
        ones ^= A[i];
        threes = ~(ones & twos);
        ones &= threes;
        twos &= threes;
    }
    return ones;
}

int main(int argc, char *argv[]) {
    int A[] = {1, 2, 3, 3, 3, 2, 1, 1, 2, 4};
    Solution s;
    cout << s.singleNumber(A, sizeof(A)/sizeof(int))<< endl;
	return 1;
}
