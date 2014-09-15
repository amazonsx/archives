#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define DEBUG
using namespace std;

class Solution {
    private:
        int level_;
    public:
        void wineCal(int bottle, int level, int index, 
                vector<map<int, double> > &linkedG, int levelCount);
        double getSpecCap(int bottle, int level, int index);
        void process(string infPath, string outfPath);
};

double Solution::getSpecCap(int bottle, int level, int index) {
    vector<map<int, double> > linkedG(level+1, map<int, double>());
    level_ = level;
    int levelCount = 0;
    for ( int i = 1; i <= level; i ++)  levelCount += i;
    wineCal( bottle, level, index, linkedG, levelCount);
    double res =  250.0*linkedG[level][index];
    if ( res > 250.0)   return 250.0;
    else    return res;
}


void Solution::wineCal(int bottle, int level, int index, 
        vector<map<int, double> > &linkedG, int levelCount) { 
    if (linkedG[level].find(index) != linkedG[level].end()) return;
    if ( level == 1 ) {
        linkedG[level][1] = bottle*3 - 1;
        return;
    }
    vector<int> linkedUpstairs;
    int upLevelCount = levelCount - level;
    if ( index <= upLevelCount) {
        wineCal(bottle, level-1, index, linkedG, upLevelCount);
        linkedG[level][index] += linkedG[level-1][index]/3;
    }
    if ( (index - level + 1) > upLevelCount-level+1 && (index-level+1) <= upLevelCount) {
        wineCal(bottle, level-1, index-level+1, linkedG, upLevelCount);
        linkedG[level][index] += linkedG[level-1][index-level+1]/3;
    }
    if ( (index - level ) > upLevelCount-level+1 && (index-level) <= upLevelCount) {
        wineCal(bottle, level-1, index-level, linkedG, upLevelCount);
        linkedG[level][index] += linkedG[level-1][index-level]/3;
    }
    if ( level != level_) {
        linkedG[level][index] -= 1;
        if ( linkedG[level][index] < 0) linkedG[level][index] = 0;
    }
}

int main(int argc, char *argv[]) {
    Solution s;
    cout << s.getSpecCap(1, 2, 1) << endl;
    cout << s.getSpecCap(1, 1, 1) << endl;
    cout << s.getSpecCap(2, 1, 1) << endl;
    cout << s.getSpecCap(20, 1, 1) << endl;
    cout << s.getSpecCap(1, 3, 1) << endl;
    cout << s.getSpecCap(2, 3, 1) << endl;
    cout << s.getSpecCap(10, 4, 10) << endl;
    return 1;
}
