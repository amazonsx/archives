#include <iostream>
#include <string>
#include <map>
#define DEBUG
using namespace std;

class Solution {
    private:
        void init( map<char, int> &roman_char_map);
	public:
        int romanToInt(string s);
};

void Solution::init( map<char, int> &roman_char_map){
    roman_char_map['i'] = 1;
    roman_char_map['v'] = 5;
    roman_char_map['x'] = 10;
    roman_char_map['l'] = 50;
    roman_char_map['c'] = 100;
    roman_char_map['d'] = 500;
    roman_char_map['m'] = 1000;
}

int Solution::romanToInt(string s) {
    int len = s.size();
    if (len == 0) return 0;
    map<char, int> roman_char_map;
    init(roman_char_map);
    char current = '\0', next = '\0';
    int val = 0;
    for ( int i = 0; i < len; i ++ ) {
        current = s[i]; 
        if (current <= 90) current += 32;
        if ( i < (len -1)) {
            next = s[i+1]; 
            if (next <= 90) next += 32;
            int duplicate_count =  1;
            if (current == next) {
                while (current == next) {
                    duplicate_count ++;
                    next = roman_char_map[i+2];
                    if (next <= 90) next += 32;
                }
                val += roman_char_map[current] * duplicate_count;
                i += duplicate_count - 1;
            } else if ( roman_char_map[current] > roman_char_map[next] ) {
                val += roman_char_map[current];         
            } else {
                val += roman_char_map[next] - roman_char_map[current];
                i++;
            }
        } else val += roman_char_map[current];
    }
    return val;
}

int main(int argc, char *argv[]) {
    cout << "original     calculate     expected" << endl;
    Solution s;
    string str1("MMMCCCXXXIII");
    cout << str1 << "    " << s.romanToInt(str1)  << "    " << 3333  << endl;

    string str2("Viii");
    cout << str2 << "    " << s.romanToInt(str2)  << "    " << 8 << endl;

    string str3("xIV");
    cout << str3 << "    " << s.romanToInt(str3)  << "    " << 14 << endl;

    string str4("xViii");
    cout << str4 <<  "    " << s.romanToInt(str4)  << "    " << 18 << endl;

    string str5("CI");
    cout << str5 <<  "    " << s.romanToInt(str5)  << "    " << 101 << endl;

    string str6("MCD");
    cout << str6 <<  "    " << s.romanToInt(str6)  << "    " << 1400 << endl;
	return 1;
}
