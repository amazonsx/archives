#include <iostream>
#define DEBUG
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x):val(x), next(NULL) {}
};

class Solution {
	public:
		bool hasCycle(ListNode *head);
}

bool Solution::hasCycle(ListNode *head) {
	ListNode *first = head;
	ListNode *second = head;
	while (first != NULL) {
		first = first->next;
		second = second->next;
		if (second != NULL)	second = second->next;
		else return false;
		if ((!first)||(!second)) return false;
		if (first == second) return true;
	}
	return false;
}


int main(int argc, char *argv[]) {
	return 1;
}
