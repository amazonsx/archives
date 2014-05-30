#include <iostream>
using namespace std;

class Solution{
public:
    int singleNumber(int A[], int n){
        if (n <= 0){
            cout << "The length of array is invalid --- " << n << endl;
            return  -1;
        }
        int result = 0;
        while (n -- ) {
            result ^= A[n]; 
        }
        return result;
    }
};


int main(){
    Solution s;    
    int A[] = {1, 2, -1, 3, 3, -1, 1};
    int result = s.singleNumber(A, sizeof(A)/ sizeof(int));
    cout << "The result is ---" << result << endl;
    return 0;
}
