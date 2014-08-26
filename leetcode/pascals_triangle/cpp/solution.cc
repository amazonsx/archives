#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    vector<vector<int> > generate(int numRows);
};

vector<vector<int> > Solution::generate(int numRows){
    vector<vector<int> > res;
    vector<int> tmp;
    if (numRows >= 1) {  
        res.push_back(tmp);
        res.back().push_back(1);
    }
    if (numRows >= 2) {
        for ( int i = 0; i < numRows - 1; i ++) {
            res.push_back(tmp);
            res.back().push_back(1);
            for ( int j = 0; j < (signed)res[i].size()-1; j ++) {
                res.back().push_back( res[i][j] + res[i][j+1]);
            }
            res.back().push_back(1);
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    vector<vector<int> > res = s.generate(5);
    for ( int i = 0; i < res.size(); i ++) {
        for ( int j = 0; j < res[i].size(); j ++) {
            cout << res[i][j] << "  ";
        }
        cout << endl;
    }
	return 1;
}
