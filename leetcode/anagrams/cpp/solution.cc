#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
private:
    void quicksort( string &str, int begin, int end);
public:
    vector<string> anagrams(vector<string> &strs);
};

void Solution::quicksort(string &str, int begin, int end) {
    if (begin >= end)   return;
    int i = begin - 1, j = begin;
    char pivot = str[end];
    while ( j < end) {
        if ( str[j] <= pivot) {
            i ++;
            char tmp = str[i];
            str[i] = str[j];
            str[j] = tmp;
        }
        j ++;
    }
    str[end] = str[++i];
    str[i] = pivot;
    quicksort(str, begin, i-1);
    quicksort(str, i+1, end);

}

vector<string> Solution::anagrams(vector<string> &strs) {
    map<string, map<bool, string> > strMap;
    vector<string> res;
    for ( int i = 0; i < (signed) strs.size(); i ++) {
        string origin = strs[i];
        quicksort(strs[i], 0, strs[i].size()-1);
        if ( strMap.find(strs[i]) != strMap.end()) {
            if ( strMap[strs[i]].begin()->first == false) {
                res.push_back(strMap[strs[i]][false]);
                strMap[strs[i]].clear();
                strMap[strs[i]][true] = res.back();
            }
            res.push_back(origin);
        } else {
            strMap[strs[i]][false] = origin;
        }
    }

    return res;
}

int main(int argc, char *argv[]) {
    vector<string> strs;
    strs.push_back("c");
    strs.push_back("c");
    //strs.push_back("");

    Solution s;
    vector<string> res = s.anagrams(strs);

    cout << res.size() << endl;
    for ( int i = 0; i < (signed)res.size(); i++) {
        cout << res[i] << "  " ;
    }
    cout << endl;
	return 1;
}

