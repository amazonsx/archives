#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    bool isValidSudoku( vector<vector<char> > &board);
    bool isValidEle( vector<vector<char> > &board, int index);
};
bool Solution::isValidEle( vector<vector<char> > &board, int index) {
    int row = index/9;
    int col = index%9;
    char target = board[row][col];
    for ( int i = 0; i < 9; i ++) {
        if ( i == col)  continue;
        if ( board[row][i] == target)   return false;
    }
    for ( int i = 0; i < 9; i ++) {
        if ( i == row)  continue;
        if ( board[i][col] == target)   return false;
    }
    int initR = row/3*3, initC = col/3*3;
    for ( int i = 0; i < 3; i ++) {
        for ( int j = 0; j < 3; j ++) {
            if ( ((initR+i) == row) && ((initC+j) == col) ) continue; 
            if (board[initR+i][initC+j] == target)  return false;
        }
    }
    return true;
}
bool Solution::isValidSudoku( vector<vector<char> > &board) {
    for ( int i = 0; i < 81; i ++) {
        if ( board[i/9][i%9] == '.')    continue;
        if (!isValidEle(board, i))  return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
	return 1;
}
