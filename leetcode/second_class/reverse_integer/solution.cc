#include <iostream>
#include <math.h>
#define DEBUG
using namespace std;

class Solution {
	public:
		int reverse(int x, int *overflow);
};

int Solution::reverse(int x, int *overflow) {
	unsigned int maxint = ((int)pow(2,(8*sizeof(int) - 2)) << 1) + 1;
	int overflow_bits = 1;
	int tmp = maxint;
	while (tmp){
		tmp = tmp/10;
		overflow_bits ++;
	}
	int sflag = (x<0)?-1:1;
	tmp = x*sflag;
	int actual_bits = 1, current_val = 0;
	unsigned int tmp_res = 0;
	unsigned int mask = (int)pow(2,(sizeof(int)*8 - 1)) - 1;
	
	tmp_res = 0;
	int res = 0;
	while (tmp) {
		current_val = tmp % 10;
		tmp = tmp / 10;	
		tmp_res = tmp_res*10 + current_val;
		actual_bits ++;
		// the reversed integer may overflow
		if ((actual_bits == overflow_bits) &&(tmp >= 10)) {
			*overflow = -1;
		} else if ((*overflow == -1) &&(tmp < 10)) {
			if (tmp_res > mask) {
				tmp_res = (mask | tmp_res);
				*overflow = 1;
			} else *overflow = 0;
		}
	}
	current_val = 0;
	unsigned int high_value = (int)(pow(2, 8*sizeof(int) - 1));
	while (high_value) {
		current_val = tmp_res & high_value;
		res = (res << 1) + ((current_val == 0)?0:1);
		high_value >>= 1;
	}
	res = res*sflag;
#ifdef DEBUG
	cout << "x: " << x << endl;
	cout << "mask: " << mask << endl;
	cout << "tmp_res: " << tmp_res << endl;
	cout << "res: " << res << endl;
#endif

	return res;
}

int main(int argc, char *argv[]){
	Solution s;
	int overflow = 0;
	int x = 1000;
	s.reverse( x, &overflow);
	x = -123123;
	s.reverse( x, &overflow);
	x = 1000000003;
	s.reverse( x, &overflow);
	//x = 2^();
	//s.reverse( x, &overflow);
	return 1;
}
