#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <string.h>
#include <assert.h>
#include <vector>
#include <map>
#include <stdlib.h>
#define DEBUG
using namespace std;

class Solution {
private:
    bool guess(vector<vector<char> > &boards, int index);
    bool isValid(vector<vector<char> > &boards, int row, int column, int target);
public:
    void solveSudoku(vector<vector<char> > &boards);
};

bool Solution::isValid(vector<vector<char> > &boards, int row, int column, int target) {
    char check = (char)('1' + target - 1);
    for ( int i = 0; i < 9; i ++) {
        if ( boards[row][i] == check )    return false;
    }
    for ( int i = 0; i < 9; i ++) {
        if ( boards[i][column] == check )    return false;
    }
    for ( int i = 0; i < 3; i ++) {
        int initR = row/3*3, initC = column/3*3;
        for ( int j = 0; j < 3; j ++) {
            if (boards[initR+i][initC+j] == check)    return false;
        }
    }
    return true;
}

bool Solution::guess( vector<vector<char> > &boards, int index) {
    if (index == 81)    return true;
    int row = index/9;
    int column = index%9;
    if (boards[row][column] != '.') {
        return guess(boards, index + 1);
    }
    /*
    vector<int> numExist(9, 0);
    for ( int i = 0; i < 9; i ++) {
        if (boards[row][i] != '.'){
            char num = boards[row][i];
            numExist[atoi(&num)-1] = 1;
        }
    }
    for ( int i = 0; i < 9; i ++) {
        if (boards[i][column] != '.'){
            char num = boards[i][column];
            numExist[atoi(&num)-1] = 1;
        }
    }
    for ( int i = 0; i < 3; i ++) {
        int initR = row/3, initC = column/3;
        for ( int j = 0; j < 3; j ++) {
            if (boards[initR+i][initC+j] != '.') {
                char num = boards[initR + i][initC + j];
                numExist[atoi(&num)-1] = 1;
            }
        }
    }
    */
    assert(boards[row][column] == '.');
    
    for ( int num = 1; num <= 9; num ++) {
        /*
        if (numExist[num-1] == '1')   continue;
        numExist[num-1] = 1;
        */
        if ( !isValid(boards, row, column, num) )   continue;
        boards[row][column] = '1'+num-1;
        bool flag = guess(boards, index+1);
        if (flag)   return true;
        boards[row][column] = '.';
        //numExist[num-1] = 0;
    }
    return false;
}

void Solution::solveSudoku(vector<vector<char> > &boards) {
    bool res = guess(boards, 0);
    //assert( res == true);
}

int main(int argc, char *argv[]) {
    vector<string> boardstr;
    boardstr.push_back("..9748...");
    boardstr.push_back("7........");
    boardstr.push_back(".2.1.9...");
    boardstr.push_back("..7...24.");
    boardstr.push_back(".64.1.59.");
    boardstr.push_back(".98...3..");
    boardstr.push_back("...8.3.2.");
    boardstr.push_back("........6");
    boardstr.push_back("...2759..");

    vector<vector<char>> boards(9, vector<char>());
    for ( int i = 0; i < 9; i ++) {
        for ( int j = 0; j < 9; j ++) {
            boards[i].push_back(boardstr[i][j]);
        }
    }
    Solution s;
    timeval first, second;
    gettimeofday( &first, NULL);
    s.solveSudoku(boards);
    gettimeofday( &second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec ) + (second.tv_usec - first.tv_usec ) << endl;
    for ( int i = 0; i < 9; i ++) {
        for ( int j = 0; j < 9; j ++) 
            cout << boards[i][j] << "  ";
        cout << endl;
    }
    return 1;
}
