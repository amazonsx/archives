#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#define DEBUG

using namespace std;

class Solution{
	public:
		int ladderLength(string start, string end, unordered_set<string> &dict);
};

int Solution::ladderLength(string start, string end, unordered_set<string> &dict) {
	if (dict.size() == 0) return 0;
	return 0;
}


int main(){
	return 0;
}
