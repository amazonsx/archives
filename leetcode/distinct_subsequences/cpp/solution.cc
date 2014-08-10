#include <iostream>
#include <map>
#include <queue>
#define DEBUG
using namespace std;

class Solution {
private:
    bool matchSubseq(string S, string T, int posS, int posT);
public:
    int numDistinct( string S, string T);
};

int Solution::numDistinct( string S, string T) {
    if (S.size() < T.size())    return 0;
    if (S.size() == T.size()) {
        if (S == T) return 1;
        else    return 0;
    }
    int diff = S.size() - T.size();
        
}

int main(int argc, char *argv[]) {
	return 1;
}
