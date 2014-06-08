#include <cstring>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[] ){

	string test("123");
	size_t pos;
	int value = stoi(test, &pos, 10);
	cout << "the test: " << test << "the value: " << value << ", the pos" << pos << endl;

	test = "123t";
	value = stoi(test, &pos, 10);
	cout << "the test: " << test << "the value: " << value << ", the pos" << pos << endl;

	//test = "t";
	//value = stoi(test, &pos, 10);
	//cout << "the test: " << test << "the value: " << value << ", the pos" << pos << endl;

	test = "-8";
	value = stoi(test, &pos, 10);
	cout << "the test: " << test << "the value: " << value << ", the pos" << pos << endl;
	vector<string> arr(2, "9", "23");
	//vector<int> arr(9, 23);
	cout << arr.size() << endl;
	return 1;
}

