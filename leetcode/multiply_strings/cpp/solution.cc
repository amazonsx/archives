#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <string>
#define DEBUG
using namespace std;

class Solution {
private:
    void reverse( string &str );
public:
    string multiply( string num1, string num2);
};
void Solution::reverse( string &str ){
    int len = str.size();
    for ( int i = 0; i <= ((len-1)>>1); i ++ ) {
        char tmp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = tmp;
    }
}
string Solution::multiply( string num1, string num2) {
    if ( num1.empty() || num2.empty() ) return "";
    int sign = 0;
    if ( num1[0] == '-')    sign ++;
    if ( num2[0] == '-')    sign ++;
    reverse(num1);
    reverse(num2);
    string res("");
    vector<int> tmpres(num1.size() + num2.size(), 0);
    for ( int i = 0; i < (signed)num1.size(); i ++) {
        char current = num1[i];
        int multiplier = atoi(&current);
        for ( int j = 0; j < (signed)num2.size(); j ++) {
            current = num2[j];
            int multiplicand = atoi(&current);
            int product = multiplier * multiplicand;
            tmpres[i+j] += product;
        }
    }
    int carryover = 0;
    for ( int i = 0; i < (signed)tmpres.size(); i ++ ) {
        int current = (tmpres[i] + carryover)%10;
        carryover = (tmpres[i] + carryover )/10; 
        tmpres[i] = current;
        res += (char)('0' + current);
    }
    while ( carryover != 0) {
        int current = carryover%10;
        tmpres.push_back(current);
        carryover /= 10;
        res += (char)('0' + current);
    }
    int count = 0;
    for ( int i = res.size()-1; i >= 0; i --) {
        if (res[i] == '0') count ++;
        else    break;
    }
    res.erase(res.size()-count, count);
    if (res.empty())    res += "0";
    if ( sign == 1) res.append(1, '-');
    reverse(res);
    return res;
}

/*
 * Strange with the case num1=52795315, num2=269
 * that it works well on my machine, but leetcode oj will result another answer
string Solution::multiply( string num1, string num2) {
    if ( num1.empty() || num2.empty() ) return "";
    int sign = 0;
    if ( num1[0] == '-')    sign ++;
    if ( num2[0] == '-')    sign ++;
    reverse(num1);
    reverse(num2);
    string res("");
    for ( int i = 0; i < (signed)num1.size(); i ++ ) {
        char current = num1[i];
        int multiplier = atoi(&current);
        for ( int j = 0; j < (signed)num2.size(); j ++) {
            current = num2[j];
            int multiplicand = atoi(&current);
            int product = multiplier * multiplicand;
            int digitCount = 1;
            while ( product >= pow(10, digitCount) ) {
                digitCount ++;
            }
            string originStr("");
            int carryover = 0;
            if ( (signed)res.size() < (i + j + digitCount)) {
                res.append( (signed)(i+j+digitCount-res.size() ), '0');
            }
            originStr = res.substr(i + j, digitCount);
            for ( int k = 0; k < (signed)originStr.size(); k ++) {
                current = originStr[k];
                int digit = atoi(&current) + (product%10) + carryover;
                carryover = digit/10;
                digit = digit%10;
                product = product/10;
                res[i+j+k] = (char)('0'+digit);
            }
            int index = i + j + digitCount;
            while ( carryover > 0) {
                if ( (signed)res.size() >= (index+1) )   {
                    current = res[index];
                    int digit = atoi(&current) + carryover;
                    res[index++] = (char)('0'+(digit%10));
                    carryover = digit/10;
                } else {
                    res.append(1, (char)('0'+carryover));
                    carryover = 0;
                }
            }
        }
    }
    int count = 0;
    for ( int i = res.size()-1; i >= 0; i --) {
        if (res[i] == '0') count ++;
        else    break;
    }
    res.erase(res.size()-count, count);
    if (res.empty())    res += "0";
    if ( sign == 1) res.append(1, '-');
    reverse(res);
    return res;
}
*/

int main(int argc, char *argv[]) {
    //string num1("123");
    //string num2("75");
    //string num1("4294967296");
    //string num2("-200");
    /*
    string num1("123");
    string num2("456");
    */
    string num1("999");
    string num2("999");
    /*
    string num1("52795315");
    string num2("-269");
    */
    Solution s;
    string res = s.multiply(num1, num2);
    cout << res << endl;
	return 1;
}
