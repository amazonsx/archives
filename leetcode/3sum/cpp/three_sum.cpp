#include <iostream>
#define DEBUG
using namespace std;

class Solution {
    private:
        void quicksort( vector<int> &num);
	public:
        vector<vector<int> > threeSum(vector<int> &num);
};

void Solution::quicksort(vector<int> &num) {
    int len = num.size();
    if (len == 0) return;
}

vector<vector<int> > Solution::threeSum(vector<int> &num) {
    int len = num.size();
    vector<vector<int> >  res;
    return res;
}

int main(int argc, char *argv[]) {
	return 1;
}
