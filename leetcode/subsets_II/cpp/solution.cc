#include <iostream>
#include <map>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
private:
    void quicksort(vector<int> &S, int left, int right);
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S);
};

void Solution::quicksort( vector<int> &S, int left, int right) {
    if (left >= right)  return;
    int i = left - 1, j = left;
    int pivot = S[right];
    while ( j < right) {
        if ( S[j] <= pivot) {
            i ++;
            int tmp = S[i];
            S[i] = S[j];
            S[j] = tmp;
        }
        j ++;
    }
    S[right] = S[++i];
    S[i] = S[right];
    quicksort(S, left, i - 1);
    quicksort(S, i+1, right);
    
}

vector<vector<int> > Solution::subsetsWithDup(vector<int> &S) {     
    vector<vector<int> > res;
    vector<int> empty_set;
    res.push_back(empty_set);

    quicksort(S, 0, S.size());

    map< int, int> intMap;
    for ( int i = 0; i < (signed)S.size(); i ++){
        intMap[S[i]] ++;
    }
        
    for ( int i = 0; i < (signed); ){
    }
}


int main(int argc, char *argv[]) {
	return 1;
}
