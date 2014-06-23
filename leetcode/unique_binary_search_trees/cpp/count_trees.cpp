#include <iostream>
#define DEBUG
using namespace std;

class Solution {
	private:
		int _numTrees(int n, int *warehouse);
	public:
		int numTrees(int n);
};
int Solution::numTrees(int n) {
	int *warehouse = new int[n+1];	
	// this is important, 
	// not all compilers will init the array for you!!!!
	for (int i = 0; i < n+1; i ++)
		warehouse[i] = 0;
	warehouse[0] = 1;
	if (n>=1)	warehouse[1] = 1;
	int res = _numTrees(n, warehouse);
	delete []warehouse;
	return res;
}
int Solution::_numTrees(int n, int *warehouse) {
	if (warehouse[n])  return warehouse[n];
	int sum = 0;
	int i = 0, j = n - 1;
	for ( i = 0; i <= n - 1; i ++, j-- ) {
		sum += _numTrees(i, warehouse)*_numTrees(j, warehouse);
	}
	warehouse[n] = sum;
	return sum;
}

int main(int argc, char *argv[]) {
	Solution s;
	int n_arr[] = {  2, 3 ,4 ,5, 6, 7, 8, 9, 10, 11, 12, 13, 50, 60};
	for(int i = 0; i < sizeof(n_arr)/sizeof(int); i++) {
		cout << n_arr[i] << " : " << s.numTrees(n_arr[i]) << endl;
	}	

	return (1);
}
