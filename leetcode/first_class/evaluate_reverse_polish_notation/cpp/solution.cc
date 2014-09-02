#include <iostream>
#include <stdexcept>
#include <assert.h>
#include <stack>
#include <string>
#include <vector>
#include <exception>
#define MULTIPLE_SOLUTION
using namespace std;

class Solution {	
private:
    int evalRPES1(vector<string> &tokens);
    int evalRPES2(vector<string> &tokens);
public:
    int evalRPE(vector<string> &tokens);
};

int Solution::evalRPES1( vector<string> &tokens) {
    if (tokens.empty() )    return 0;
    stack<int> eles;
    for( int i = 0; i < (signed)tokens.size(); i ++) {
        string ele = tokens[i];
        int operand_l = 0, operand_r = 0;
        try { 
            operand_l = stoi(ele);
            eles.push(operand_l);
        } catch( invalid_argument& ia) {
            assert(eles.size() >= 2);
            assert(ele.size() == 1);
            operand_r = eles.top();
            eles.pop();
            operand_l = eles.top();
            eles.pop();
            int res = 0;
            switch (ele[0]) {
                case '+': {
                    res = operand_l + operand_r;
                    break;
                }
                case '-': {
                    res = operand_l - operand_r;
                    break;
                }
                case '*': {
                    res = operand_l * operand_r;
                    break;
                }
                case '/': {
                    res = operand_l / operand_r;
                    break;
                }
                default : {
                    assert(false);
                }
            }
            eles.push(res);
        }
    }
    return eles.top();
}

int Solution::evalRPES2(vector<string> &tokens){
	if ( tokens.empty() ) return 0;

	int size = tokens.size();
	int value = 0;
	stack<int> s_tokens;
	string token;
	int operand_l = 0;
	int operand_r = 0;
    for (int i = 0; i < size; i ++) {
		token = tokens[i];
		//what if token.size() = 0
		if (token.size() == 1) {
			if ( token == "+" ){
			   	operand_r = s_tokens.top();
				s_tokens.pop();
				operand_l = s_tokens.top();
				s_tokens.pop();
				value = operand_l + operand_r;
			} else if ( token == "-" ) {
				operand_r = s_tokens.top();
				s_tokens.pop();
				operand_l = s_tokens.top();
				s_tokens.pop();
				value = operand_l - operand_r;
			} else if (token == "*") {
				operand_r = s_tokens.top();
				s_tokens.pop();
				operand_l = s_tokens.top();
				s_tokens.pop();
				value = operand_l * operand_r;
			} else if (token == "/") {
				operand_r = s_tokens.top();
				s_tokens.pop();
				operand_l = s_tokens.top();
				s_tokens.pop();
				value = operand_l / operand_r;
			} else {
				value = stoi(token, NULL, 10);
			}
		} else {
			value = stoi(token, NULL, 10);
		}
		s_tokens.push(value);
	}
	//is it neccessary to check if s_tokens has more than 1 values
	//is it neccessary to check if s_tokens has been empty
	if ( s_tokens.empty()){
	} else if (s_tokens.size() > 1 ) {
	} else {
		value = s_tokens.top();
		s_tokens.pop();
	}
	return value;
}
int Solution::evalRPE(vector<string> &tokens) {
    int res = evalRPES1( tokens);
#ifdef MULTIPLE_SOLUTION
    int res1 = evalRPES2(tokens);
    assert(res == res1);
#endif
    return res;
}

int main(int argc, char *argv[]){
	Solution s;
	string tmp[] = {"-8","23","8","-","9","23","-","-","*","33","-8","/","+","38","-14","-","-","-7","32","-19","-","11","+","+","+","14","22","-","-","27","-9","-","+","31","+","-12","-11","-","-","14","+","30","+","37","30","-","+","-9","+","7","-","37","+","-5","13","/","-","19","-2","-19","12","+","-","23","+","-","-19","-","+","6","+","-17","+","17","+","5","36","+","-10","+","+","23","-8","-","-","18","-","31","-16","-","+","34","+","-6","+","24","-","22","-","-8","-","28","+","-12","+","39","28","-7","+","+","-14","5","+","5","+","10","+","+","+","-18","*","10","+","-5","11","-","6","+","-","-12","31","+","+","30","29","-","-","39","+","13","-8","-5","+","-","26","19","-","*","-","10","-","-20","5","+","+","0","-","28","-","19","/","28","+","-18","-","28","20","+","-5","-19","+","+","-","-12","-","3","-","6","-15","+","4","-","-","38","+","-9","-","38","-","12","-20","-","10","5","-15","-","-","-","+","-11","+","5","+","2","-","28","+","-9","-11","-","+","37","-","-17","31","-","2","+","+","-16","-12","-","-","12","+","34","-","15","+","8","+","17","-","2","-","33","+","-5","+","14","+","29","-","33","23","+","26","30","-","+","+","39","+","9","24","-","-","20","15","+","-","24","+","37","-","30","-1","-","+","34","+","-13","-","23","15","-","-","-5","-8","8","30","35","-9","22","+","-","-","36","-1","+","5","-","-","+","25","-","+","27","-","16","+","+","+","39","-","15","-","-3","+","5","-6","-","+","-6","-15","-7","-","+","/","13","-","18","+","4","+","29","+","-17","0","-6","-20","-17","+","12","-","+","-","+","+","-10","22","+","+","-11","-","-2","38","-","-","-6","+","0","-","-10","+","-4","-10","+","-","0","-","31","30","-","37","5","+","+","+","-15","+","38","4","-","-16","-17","+","+","+","38","-","27","-19","/","12","+","/"};
	vector<string> str;
	cout << sizeof(tmp)/sizeof(string) << endl;
	for(int i = 0; i <(signed)(sizeof(tmp)/sizeof(string) ); i ++)
		str.insert(str.end(), tmp[i]);
	vector<string> &v = str;

	int res = s.evalRPE(v);
	cout << "-------" << endl;
	cout << res << endl;
	cout << "-------" << endl;

	exit(0);
}
