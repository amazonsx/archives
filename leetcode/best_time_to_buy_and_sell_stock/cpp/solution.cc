#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    int maxProfit( vector<int> &prices);
};

int Solution::maxProfit( vector<int> &prices) {
    if (prices.size() <= 1) return 0;

    int min = prices[0], max = -1;
    int profit = 0;
    for ( int i = 1; i < (signed)prices.size(); i ++) {
        if (( prices[i] > prices[i-1] ) 
                && ( prices[i] > max) )
            max = prices[i];
        else if ( prices[i] < min ) {
            if ( (max-min) > profit)    profit = max - min;
            min = prices[i];
            max = -1;
        }
    }
    if ( (max - min) > profit)
        profit = max - min;
    return profit;
}

int main(int argc, char *argv[]) {
	return 1;
}
