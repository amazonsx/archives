#include <iostream>
#include <string>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    string convertCostsMuchSpace(string s, int row);
    string convert(string s, int row);
};
string Solution::convert(string s, int row) {
    if ( row == 1) return s;
    string res("");
    int jump = row * 2 - 2;
    for ( int i = 0; i < row; i ++) {
        for ( int j = i; j < (signed)s.size(); j += jump) {
            res += s[j];
            if ( (i!=0) && (i!=row-1) && (j+jump-2*i<s.size())) {
                res += s[j+jump-2*i];
            }
        }
    }
    return res;
}

string Solution::convertCostsMuchSpace(string s, int row) {
    vector<vector<char> > zigzagPath(row, vector<char>());
    //0: go down, 1: go up
    int direction = 0;
    int len = s.size(), index = 0; 
    int former = -1;
    while ( index < len) {
        if (direction == 0) {
            if ((former+1) == row)  former --;
            zigzagPath[++former].push_back(s[index++]);
        } else {
            if ((former-1) == 0) former ++;
            zigzagPath[--former].push_back(s[index++]);
        }

        if (former == (row-1)) direction = 1;
        if (former == 0)    direction = 0;
    }
    string res;
    for ( int i = 0; i < row; i ++) {
        for ( int j = 0; j < (signed)zigzagPath[i].size(); j ++) {
            res += zigzagPath[i][j];
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    /*
    string str("PAYPALISHIRING");
    */
    string str("ABC");
    Solution s;
    //string res = s.convert(str, 3);
    //cout << "PAHNAPLSIIGYIR" << endl;
    string res = s.convert(str, 1);
    cout << res << endl;
    cout << "ABC" << endl;
	return 1;
}

