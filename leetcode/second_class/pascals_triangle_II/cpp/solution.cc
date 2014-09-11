#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    vector<int> getRow( int rowIndex);
};
vector<int> Solution::getRow( int rowIndex) {
    vector<int> res;
    res.push_back(1);
    if (rowIndex == 0)  return res;
    vector<int> former = getRow( rowIndex - 1 );
    for ( int i = 0; i < (signed)former.size()-1; i ++) {
        res.push_back(former[i] + former[i+1]);
    }
    res.push_back(1);
    return res;
}

int main(int argc, char *argv[]) {
	return 1;
}
