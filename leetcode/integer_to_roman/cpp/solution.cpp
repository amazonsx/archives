#include <iostream>
#include <string>
#define DEBUG
using namespace std;

class Solution {
public:
    string intToRoman(int num);
};

string Solution::intToRoman(int num) {
    if (num == 0) return "";
    int digitsCount = 1;
    string res;
    while (num != 0) {
        int current = num % 10;
        switch (digitsCount) {
            case 1: {
                if (current <= 3) {
                    while(current != 0) {
                        res += "I";
                        current --;
                }
                } else if (current == 4)
                    res = "IV";
                else if ( current == 9)
                    res = "IX";
                else {
                    res = "V";
                    while(current != 5) {
                        res+= "I";
                        current --;
                    }
                } 
                break;
            }
            case 2: {
                if (current <= 3) {
                    while(current != 0) {
                        res = "X" + res;
                        current --;
                    }
                } else if (current == 4)
                    res = "XL" + res;
                else if ( current == 9)
                    res = "XC" + res;
                else {
                    string tmp = "L";
                    while(current != 5) {
                        tmp+= "X";
                        current --;
                    }
                    res = tmp + res;
                }
                break;
            }
            case 3: { 
                if (current <= 3) {
                    while(current != 0) {
                        res = "C" + res;
                        current --;
                    }
                } else if (current == 4)
                    res = "CD" + res;
                else if ( current == 9)
                    res = "CM" + res;
                else {
                    string tmp = "D";
                    while(current != 5) {
                        tmp+= "C"; 
                        current --;
                    }
                    res = tmp + res;
                }
                break;
            }
            case 4: {
                if (current <= 3) {
                    while(current != 0) {
                        res = "M" + res;
                        current --;
                    }
                }
                break;
            }
            default:{ }
        }

        num /= 10;
        digitsCount ++;
    }
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    int num = 3999;
    cout << s.intToRoman(num) << endl;
	return 1;
}
