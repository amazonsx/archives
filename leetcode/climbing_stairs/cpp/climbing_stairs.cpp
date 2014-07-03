#include <iostream>
#define DEBUG
using namespace std;

class Solution {
    private:
        int recursiveWay(int n, int* mem_list);
        int iterativeWay(int n);
	public:
        int climbStairs(int n);
};
int Solution::recursiveWay(int n, int *mem_list) {
    if (mem_list[n] != -1) return mem_list[n];
    if (( n == 0) || (n == 1)) {
        mem_list[n] = 1;
        return 1;
    }
    int res =  recursiveWay(n-1, mem_list) + recursiveWay(n - 2, mem_list);
    mem_list[n] = res;
    return res;
}
int Solution::iterativeWay(int n) {
    if ((n == 0)||(n==1)) return 1;
    int *mem_list = new int[n+1];
    for ( int i = 0; i <= n; i ++){
        if ( (i == 0)||(i == 1) ) mem_list[i] = 1;
        else 
            mem_list[i] = mem_list[i-1] + mem_list[i-2];
    }
    
    return mem_list[n];
}
int Solution::climbStairs(int n) {
    // recursive way
    /*
    int *mem_list = new int[n+1];
    for ( int i = 0; i <= n; i ++)
        mem_list[i] = -1;
    return recursiveWay(n, mem_list);
    */
    return iterativeWay(n);
}

int main(int argc, char *argv[]) {
    Solution s;
    cout << s.climbStairs(0) << endl; //1
    cout << s.climbStairs(1) << endl; //1
    cout << s.climbStairs(2) << endl; //2
    cout << s.climbStairs(3) << endl; //3
    cout << s.climbStairs(4) << endl; //5
    cout << s.climbStairs(1000) << endl;
	return 0;
}
