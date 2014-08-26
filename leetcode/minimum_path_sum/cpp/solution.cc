#include <iostream>
#include <algorithm>
#include <limits>
#include <assert.h>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    int minPathSum( vector<vector<int> > &grid);
};

int Solution::minPathSum( vector<vector<int> > &grid) {
    assert(grid.size() > 0);
    int m = grid.size(), n = grid.back().size();
    vector<vector<int> > pathSum( m, vector<int>(n, numeric_limits<int>::max()));
    pathSum[m-1][n-1] = grid[m-1][n-1];
    for ( int i = m-2; i >= 0; i --)
        pathSum[i][n-1] = pathSum[i+1][n-1] + grid[i][n-1];
    for ( int i = n-2; i >= 0; i --)
        pathSum[m-1][i] =  pathSum[m-1][i+1] + grid[m-1][i];

    int i = m - 2, j = n - 2;
    while ( i >= 0 && j >= 0) {
        pathSum[i][j] = grid[i][j] + min(pathSum[i+1][j], pathSum[i][j+1]);;
        for ( int k = i - 1; k >= 0; k --)
            pathSum[k][j] = grid[k][j] + min( pathSum[k+1][j], pathSum[k][j+1]);
        for ( int k = j - 1; k >= 0; k --)
            pathSum[i][k] = grid[i][k] + min( pathSum[i+1][k], pathSum[i][k+1]);
        i --; j --;
    }

    return pathSum[0][0];
}

int main(int argc, char *argv[]) {
	return 1;
}
