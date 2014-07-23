#include <iostream>
#include <string>
#include <map>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
private:
    //FIXME(shixiao): this is the brute force solution
    bool charMatchRecursive(string &s1, string &s2, string &s3, 
            int first, int second, int thrid, map<int, vector<int>> &resRepo);
public:
    bool isInterleave(string s1, string s2, string s3);
};

bool Solution::charMatchRecursive(string &s1, string &s2, string &s3,
        int first, int second, int third , map<int, vector<int>> &resRepo) {

    if (resRepo.find(third) != resRepo.end()) {
        if ((resRepo[third][0] == first)
                && (resRepo[third][1] == second)) {
            return resRepo[third][2];
        }
    }
    if ((first == (signed)s1.size()) && (second == (signed)s2.size())
            && (third == (signed)s3.size())) {
        resRepo[third].push_back(first);
        resRepo[third].push_back(second);
        resRepo[third].push_back(1);
        return true;
    }
    bool res = false;
    if ( s3[third] == s1[first] ) {
        res |= charMatchRecursive(s1, s2, s3, 
                first+1, second, third+1, resRepo);
    }
    if (!res) {
        if (s3[third] == s2[second]) {
            res |= charMatchRecursive(s1, s2, s3, 
                    first, second + 1, third+1, resRepo);
        }
    }
    resRepo[third].push_back(first);
    resRepo[third].push_back(second);
    resRepo[third].push_back(res);
    return res;
}

bool Solution::isInterleave( string s1, string s2, string s3){
    if ((s1.size() + s2.size()) != s3.size())
        return false;
    bool flag = false;
    map<int, vector<int> > resRepo;
    flag = charMatchRecursive( s1, s2, s3, 0, 0, 0, resRepo);
    return flag;
}

int main(int argc, char *argv[]) {
    Solution s;
    string s1("aabcc"), s2("dbbca"), s3("aadbbcbcac");
    cout << s.isInterleave(s1, s2, s3) << endl;
	return 1;
}
