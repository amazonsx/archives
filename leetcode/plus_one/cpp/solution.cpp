#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
	public:
		vector<int> plusOne(vector<int> &digits);
};

vector<int> Solution::plusOne(vector<int> &digits) {
	int len = digits.size();
	//if the digits is empty, should i return 1 or empty
	if (!len) return digits;
	int carry_over = 1;
	for ( int i = len - 1; i >=0; i --) {
		int current_digit = digits[i];
		if ( current_digit < 9) {
			digits[i] += carry_over;
			carry_over = 0;
		} else {
			if (carry_over) {
				digits[i] = 0;
			} 
		}
	}
	if (carry_over) {
		digits.insert(digits.begin(), 1);
	}
	return digits;
}

int main(int argc, char *argv[]) {
	Solution s;
	int arr_i[] = {4, 8, 9, 2, 3};
	vector<int> digits_i;
	for (int i = 0; i < 5; i ++) {
		cout << arr_i[i] << " ";
		digits_i.push_back(arr_i[i]);
	}
	cout << endl;
	vector<int> res = s.plusOne(digits_i);
	for (int i = 0; i < digits_i.size(); i ++) {
		cout << digits_i[i] << " ";
	}
	cout << endl;

	res.clear();
	int arr_ii[] = {1, 9, 9, 9, 9};
	vector<int> digits_ii;
	for (int i = 0; i < 5; i ++) {
		cout << arr_ii[i] << " ";
		digits_ii.push_back(arr_ii[i]);
	}
	cout << endl;
	res = s.plusOne(digits_ii);
	for (int i = 0; i < res.size(); i ++) {
		cout << res[i] << " ";
	}
	cout << endl;

	res.clear();
	int arr_iii[] = {9, 9, 9, 9, 9};
	vector<int> digits_iii;
	for (int i = 0; i < 5; i ++) {
		cout << arr_iii[i] << " ";
		digits_iii.push_back(arr_iii[i]);
	}
	cout << endl;
	res = s.plusOne(digits_iii);
	for (int i = 0; i < res.size(); i ++) {
		cout << res[i] << " ";
	}
	cout << endl;
	return 1;
}
