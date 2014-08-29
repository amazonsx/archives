#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
    public:
        void setZeroes(vector<vector<int> > &matrix);
};

void Solution::setZeroes(vector<vector<int> > &matrix) {
    if (matrix.empty()) return;
    bool rowSetFlag = false, columnSetFlag = false;
    for ( int i = 0; i < (signed)matrix[0].size(); i ++) {
        if ( matrix[0][i] == 0) {
            rowSetFlag = true;
            break;
        }
    }
    for ( int i = 0; i < (signed)matrix.size(); i ++) {
        if ( matrix[i][0] == 0) {
            columnSetFlag = true;
            break;
        }
    }
    for ( int i = 1; i < (signed)matrix.size(); i ++) {
        for ( int j = 1; j < (signed)matrix[i].size(); j ++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    for ( int i = 1; i < (signed)matrix[0].size(); i ++) {
        for ( int j = 1; j < (signed)matrix.size(); j ++) {
            if (matrix[0][i] == 0)
                matrix[j][i] = 0;
        }
    }
    for ( int i = 1; i < (signed)matrix.size(); i ++) {
        for ( int j = 1; j < (signed)matrix[i].size(); j ++) {
            if (matrix[i][0] == 0)
                matrix[i][j] = 0;
        }
    }
    if (rowSetFlag) {
        for ( int i = 0; i < (signed)matrix[0].size(); i ++) {
            matrix[0][i] = 0;
        }
    }
    if (columnSetFlag) {
        for ( int i = 0; i < (signed)matrix.size(); i ++) {
            matrix[i][0] = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    return 1;
}
