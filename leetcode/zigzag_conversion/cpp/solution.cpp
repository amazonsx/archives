#include <iostream>
#include <string>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    string convert(string s, int row);
};

string Solution::convert(string s, int row) {
    vector<char> sub;
    vector<vector<char> > zigzagPath(row, sub);
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

