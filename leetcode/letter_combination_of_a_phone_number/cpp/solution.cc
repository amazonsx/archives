#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#define DEBUG
using namespace std;

class Solution {
private:
    void mapDigits( string &digits, int start, string &conversion, vector<string> &res);
public:
    vector<string> letterCombinations(string digits);
};

void Solution::mapDigits( string &digits, int start, string &conversion, vector<string> &res) {
    if (start == (signed)digits.size()) {
        res.push_back(conversion);
        return;
    }
    assert( digits[start] != '1');
    switch (stoi(digits.substr(start, 1))) {
        case 0: {
            conversion += ' ';
            //conversion.pop_back();
            conversion = conversion.substr(0, conversion.size()-1);
            break;
        }
        case 7: {
            for ( int i = 0; i < 4; i ++) {
                conversion += 'p' + i;
                mapDigits(digits, start+1, conversion, res);
                //conversion.pop_back();
                conversion = conversion.substr(0, conversion.size()-1);
            }
            break;
        }
        case 8: {
            for ( int i = 0; i < 3; i ++) {
                conversion += 't' + i;
                mapDigits(digits, start+1, conversion, res);
                //conversion.pop_back();
                conversion = conversion.substr(0, conversion.size()-1);
            }
            break;
        }
        case 9: {
            for ( int i = 0; i < 4; i ++) {
                conversion += 'w' + i;
                mapDigits(digits, start+1, conversion, res);
                //conversion.pop_back();
                conversion = conversion.substr(0, conversion.size()-1);
            }
            break;
        }
        default : {
            for ( int i = 0; i < 3; i ++) {
                conversion += 'a' + (stoi(digits.substr(start,1)) - 2)*3 + i;
                mapDigits(digits, start+1, conversion, res);
                //conversion.pop_back();
                conversion = conversion.substr(0, conversion.size()-1);
            }
        }
    }
}

vector<string> Solution::letterCombinations(string digits) {
    vector<string> res;
    string conversion("");
    if (digits.size() == 0)
        res.push_back( conversion);
    mapDigits( digits, 0, conversion,  res);
    return res;
}

int main(int argc, char *argv[]) {
    //string digits("23");
    string digits("7");
    Solution s;
    vector<string> res = s.letterCombinations(digits);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        cout << res[i] << endl;
    }
	return 1;
}
