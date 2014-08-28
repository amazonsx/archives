#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
    public:
        vector<vector<int> > combine( int n, int k);
};

vector<vector<int> > Solution::combine( int n, int k) {
    vector<vector<int> > res;
    if ( k > n) return res;
    vector<vector<vector<vector<int> > > > subsets(
            n, vector<vector<vector<int> > >( k+1, vector<vector<int> >()));
    for ( int i = 1; i <= n; i ++) {
        subsets[i-1][1].push_back(vector<int>(1, i));
        if ( k == 1 )
            res.push_back(subsets[i-1][1].back());
    }
    for ( int i = 2; i <= k; i ++) {
        for ( int j = 0; j < n; j ++) {
            for ( int h = j + 1; h < (signed)n; h ++) {
                for ( int m = 0; m < (signed)subsets[h][i-1].size(); m ++) {
                    subsets[j][i].push_back(vector<int>(1, j+1));
                    subsets[j][i].back().insert(subsets[j][i].back().end(),
                            subsets[h][i-1][m].begin(), subsets[h][i-1][m].end());
                    if ( i == k)
                        res.push_back(subsets[j][i].back());
                }
            }
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    vector<vector<int> > res = s.combine( 2, 2);
    for (int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] << "  ";
        }
        cout << endl;
    }
    return 1;
}

