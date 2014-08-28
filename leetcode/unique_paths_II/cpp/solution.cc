#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid);
};

int Solution::uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
    if (obstacleGrid.empty())   return 0;
    int h = obstacleGrid.size(), w = obstacleGrid[0].size();
    vector<vector<int> > path(h, vector<int>(w, 0));
    if ( obstacleGrid[h-1][w-1] == 0) path[h-1][w-1] = 1;
    else return 0;
    if ( obstacleGrid[0][0] == 1) return 0;
    for ( int i = h-2; i >= 0; i -- ) {
        if (obstacleGrid[i][w-1] == 0)  path[i][w-1] += path[i+1][w-1];
    }
    for ( int i = w-2; i >= 0; i --) {
        if (obstacleGrid[h-1][i] == 0)  path[h-1][i] += path[h-1][i+1];
    }
    int m = h -2, n = w - 2;
    while ( m >= 0 && n >= 0) {
        if (obstacleGrid[m][n] == 0)
            path[m][n] = path[m+1][n] + path[m][n+1];
        for ( int i = m-1; i >=0; i --) {
            if (obstacleGrid[i][n] == 0) path[i][n] += path[i][n+1] + path[i+1][n];
        }
        for ( int i = n-1; i >=0; i --) {
            if (obstacleGrid[m][i] == 0) path[m][i] += path[m][i+1] + path[m+1][i];
        }
        m --;
        n --;
    }

    return path[0][0];
}

int main(int argc, char *argv[]) {
    vector<vector<int> > obstacleGrid(2, vector<int>(2, 0));
    Solution s;
    cout << s.uniquePathsWithObstacles(obstacleGrid) << endl;

	return 1;
}
