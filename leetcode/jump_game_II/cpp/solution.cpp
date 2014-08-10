#include <iostream>
#include <map>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
private:
    int minJumpWithMem(int *A, int n, int current, int minSteps, map<int, int> &stepsMem, int detectedLoc);
    int minJump(int *A, int n, int current, int minSteps, int detectedLoc);
public:
    int jump(int A[], int n);
    int jumpWithMem(int A[], int n);
};

int Solution::minJumpWithMem(int *A, int n, int current, int minSteps, 
        map<int, int> &stepsMem, int detectedLoc) {
    if (stepsMem.find(current)!= stepsMem.end())
        return stepsMem[current];

    if (minSteps < 0)
        return minSteps + 1;

    int curMax = A[current];
    if (curMax == 0) return n;
    if ((curMax + current) >= (n-1))
        return 1;

    int curMinSteps = n - current - 1;
    for ( int i = 1; i <= curMax; i ++) {
        //The following operation optimises this algorithm a lot
        //This could eliminate millions of duplicated operations
        if (detectedLoc >= (current+i+A[current+i]))
            continue;
        int nextMinStepsLimit = minSteps - 1;
        if (nextMinStepsLimit > curMinSteps)
            nextMinStepsLimit = curMinSteps;
        int min = minJumpWithMem(A, n, current+i, nextMinStepsLimit, stepsMem, current+curMax);
        stepsMem[current+i] = min;
        if (min < curMinSteps)
            curMinSteps = min;
    }
    stepsMem[current] = curMinSteps + 1;
    return curMinSteps + 1;
}

int Solution::minJump(int *A, int n, int current, int minSteps, int detectedLoc) {
    if (minSteps < 0)
        return minSteps + 1;

    int curMax = A[current];
    if (curMax == 0) return n;
    if ((curMax + current) >= (n-1))
        return 1;

    int curMinSteps = n - current - 1;
    for ( int i = 1; i <= curMax; i ++) { 
        //The following operation optimises this algorithm a lot
        //This could eliminate millions of duplicated operations
        if ( detectedLoc >= (current+i+A[current+i]))
            continue;
        int nextMinStepsLimit = minSteps - 1;
        if (nextMinStepsLimit > curMinSteps)
            nextMinStepsLimit = curMinSteps;
        int min = minJump(A, n, current+i, nextMinStepsLimit, current+curMax);
        if (min < curMinSteps)
            curMinSteps = min;
    }
    return curMinSteps + 1;
}

int Solution::jump(int A[], int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    int minSteps = minJump(A, n, 0, n-1, 1);
    return minSteps;
}
int Solution::jumpWithMem(int A[], int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    map<int, int> stepsMem;
    int minSteps = minJumpWithMem(A, n, 0, n-1, stepsMem, 1);
    return minSteps;
}

int main(int argc, char *argv[]) {
    // 2
    //int arr[] = {2, 3, 1, 1, 4}; 
    //
    //int arr[] = {5,6,4,4,6,9,4,4,7,4,4,8,2,6,8,1,5,9,6,5,2,7,9,7,9,6,9,4,1,6,8,8,4,4,2,0,3,8,5};
    int arr[] = {8,2,4,4,4,9,5,2,5,8,8,0,8,6,9,1,1,6,3,5,1,2,6,6,0,4,8,6,0,3,2,8,7,6,5,1,7,0,3,4,8,3,5,9,0,4,0,1,0,5,9,2,0,7,0,2,1,0,8,2,5,1,2,3,9,7,4,7,0,0,1,8,5,6,7,5,1,9,9,3,5,0,7,5};
    //int arr[] = {1, 2, 3};
    Solution s;
    struct timeval first, second;
    gettimeofday(&first, NULL);
    cout << s.jump(arr, sizeof(arr)/sizeof(int)) << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ---- "
         << 1000000*(second.tv_sec - first.tv_sec) + (second.tv_usec - first.tv_usec) 
         << endl;

    gettimeofday(&first, NULL);
    cout << s.jumpWithMem(arr, sizeof(arr)/sizeof(int)) << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ---- "
         << 1000000*(second.tv_sec - first.tv_sec) + (second.tv_usec - first.tv_usec) 
         << endl;

	return 1;
}
