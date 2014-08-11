#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    int canCompleteCircuit( vector<int> &gas, vector<int> &cost);
};

int Solution::canCompleteCircuit( vector<int> &gas, vector<int> &cost) {
    vector<int> candidateStart;
    int allGas = 0, allCost = 0;
    for( int i = 0; i < (signed)gas.size(); i ++) {
        allGas += gas[i];
        allCost += cost[i];
        if (gas[i] >= cost[i]) 
            candidateStart.push_back(i);
    }

    if (candidateStart.size() == 0) return -1;
    if (allGas < allCost)   return -1;

    int len = (signed)gas.size();
    for ( int i = 0; i < (signed)candidateStart.size(); i++) {
        int start = candidateStart[i];
        int j = 0, flag = 1;
        int remain = 0;
        while ( j < len) {
            int current = (start+j) % len;
            if ((remain + gas[current]) >= cost[current]) {
                remain = remain + gas[current] - cost[current];
            } else {
                flag = 0;
                break;
            }
            j ++;
        }
        if (flag)   return start;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int arr1[] = {1, 2, 3, 3};
    int arr2[] = {2, 1, 5, 1};
    vector<int> gas(arr1, arr1+sizeof(arr1)/sizeof(int));
    vector<int> cost(arr2, arr2+sizeof(arr2)/sizeof(int));
    Solution s;
    cout << s.canCompleteCircuit(gas, cost) << endl;

	return 1;
}

