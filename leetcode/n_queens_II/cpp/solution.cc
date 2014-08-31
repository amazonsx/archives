#include <iostream>
#include <stdlib.h>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
private:
    void buildBoard( int &count, int n, vector<int> state, int rowNum);
public:
    int totalNQueens(int n);
};
void Solution::buildBoard( int &count, int n, vector<int> state, int rowNum) {
    if ( rowNum == n) {
        count ++;
        return;
    }
    for ( int i = 0; i < n; i ++) {
        bool valid = true;
        for ( int j = 0; j < rowNum; j ++) {
            if ( (state[j] == i)
                    || (abs(state[j]-i) == (rowNum - j)) ) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        state[rowNum] = i;
        buildBoard(count, n, state, rowNum + 1);
        state[rowNum] = -1;
    }
}

int Solution::totalNQueens(int n) {
    int count = 0;
    vector<int> state(n, -1);
    buildBoard( count, n, state, 0);
    return count;
}

int main(int argc, char *argv[]) {
    Solution s;
    cout << s.totalNQueens(5) << endl;
	return 1;
}
