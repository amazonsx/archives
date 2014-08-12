#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#define DEBUG
using namespace std;

class Solution {
public:
    string addBinary( string a, string b);
};

string Solution::addBinary( string a, string b) {
    int aCurrent = a.size()-1, bCurrent = b.size()-1;
    int carryFlag = 0;
    string res = "";
    while ( (aCurrent >= 0) && (bCurrent >= 0)) {
        int aInt = stoi( a.substr(aCurrent, 1) ); 
        int bInt = stoi( b.substr(bCurrent, 1) );
        int sum = aInt + bInt + carryFlag;
        carryFlag = sum / 2;
        int current = sum % 2;
        //res = std::to_string(current) + res;
        res = static_cast<ostringstream*>(&(ostringstream() << current))->str() + res;
        aCurrent --;
        bCurrent --;
    }
    while (aCurrent >= 0) {
        int aInt = stoi( a.substr(aCurrent, 1) ) + carryFlag; 
        carryFlag = aInt / 2;
        int current = aInt % 2;
        res = static_cast<ostringstream*>(&(ostringstream() << current))->str() + res;
        aCurrent --;
    }
    while (bCurrent >= 0) {
        int bInt = stoi( b.substr(bCurrent, 1) ) + carryFlag;
        carryFlag = bInt / 2;
        int current = bInt % 2;
        res = static_cast<ostringstream*>(&(ostringstream() << current))->str() + res;
        bCurrent --;
    }
    if (carryFlag == 1)
        res = '1' + res;
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    string a("111"), b("11");
    cout << s.addBinary(a, b) << endl;
	return 1;
}
