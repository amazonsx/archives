#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#define DEBUG
using namespace std;

class Solution {
public:
    int minimumTotal( vector<vector<int> > &triangle);
};
    
int Solution::minimumTotal( vector<vector<int> > &triangle) {
    assert(triangle.size() >= 1);
    vector<vector<int> > pathSum;
    pathSum.push_back(vector<int>(1, triangle[0][0]));

    for ( int i = 1; i < (signed)triangle.size(); i ++) {
        vector<int> tmp;
        tmp.push_back(triangle[i][0] + pathSum[i-1][0]);
        for ( int j = 1; j < (signed) triangle[i].size()-1; j ++) {
            tmp.push_back(triangle[i][j] + min(pathSum[i-1][j-1], pathSum[i-1][j]));
        }
        tmp.push_back(triangle[i].back() + pathSum[i-1].back());
        pathSum.push_back(tmp);
    }

    int min = pathSum.back()[0];

    for ( int i = 1; i < (signed)pathSum.back().size(); i ++){
        if (pathSum.back()[i] < min)
            min = pathSum.back()[i];
    }
    return min;
}

int main(int argc, char *argv[]) {
    vector<int> v1;
    v1.push_back(-1);

    vector<int> v2;
    v2.push_back(2);
    v2.push_back(3);

    vector<int> v3;
    v3.push_back(1);
    v3.push_back(-1);
    v3.push_back(-3);
    vector<vector<int> > triangle;
    triangle.push_back(v1);
    triangle.push_back(v2);
    triangle.push_back(v3);

    Solution s;
    cout << s.minimumTotal(triangle) << endl;
	return 1;
}
