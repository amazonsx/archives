#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    int uniquePaths( int m, int n);
};

int Solution::uniquePaths( int m, int n) {
    vector<vector<int> > paths(m, vector<int>(n, 0));
    for ( int i = 0; i < m; i ++) {
        paths[i][n-1] = 1; //m - 1 - i;
    }
    for ( int i = 0; i < n; i ++) {
        paths[m-1][i] = 1; //n - 1 - i;
    }
    int i = m - 2, j = n - 2;
    while ( i >= 0 && j >= 0) {
        paths[i][j] = paths[i+1][j] + paths[i][j+1];
        for ( int k = j - 1; k >= 0; k --) {
            paths[i][k] = paths[i][k+1] + paths[i+1][k];
        }
        for ( int k = i - 1; k >= 0; k --) {
            paths[k][j] = paths[k][j + 1] + paths[k + 1][j];
        }
        i --; j --;
    }
    return paths[0][0];
}

int main(int argc, char *argv[]) {
    Solution s;
    cout << s.uniquePaths(2, 1) << endl;
	return 1;
}
