#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <unordered_set>
#define DEBUG
using namespace std;

class Solution {
private:
    void buildBoard(vector<vector<string> > &res, int rowNum, vector<int> &state, int n);
public:
    vector<vector<string> > solveNQueens(int n);
};

void Solution::buildBoard(vector<vector<string> > &res, 
        int rowNum, vector<int> &state, int n) {
    if (rowNum == n) {
        res.push_back(vector<string>() );
        vector<string> &board = res.back();
        for ( int i = 0; i < n; i ++) {
            string line("");
            for ( int j = 0; j < n; j ++) {
                if ( j == state[i]) line += "Q";
                else line += ".";
            }
            board.push_back(line);
        }
        return;
    }
    for ( int i = 0; i < n; i ++) {
        bool valid = true;
        for ( int j = 0; j < rowNum; j ++) {
            if ( (state[j] == i) || (abs(state[j] - i) == (rowNum - j)) ) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        state[rowNum] = i;
        buildBoard( res, rowNum + 1, state, n);
        state[rowNum] = -1;
    }
}

vector<vector<string> > Solution::solveNQueens(int n) {
    vector<vector<string> > res;
    vector<int> state(n, -1);
    buildBoard( res, 0, state, n);
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    vector<vector<string> > res = s.solveNQueens(5);
    cout << res.size() << endl;
	return 1;
}
