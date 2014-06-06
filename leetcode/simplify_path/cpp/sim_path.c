#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution{
	public:
		string simplifyPath(string path);
};

string Solution::simplifyPath(string path){
	if (path.empty())	return "/";
	stack<string> s_path;
	int size = path.size();
	string name("");
	char current;
	int init_slash_flag = 0;
	int dot_num = 0;
	
	for (int i = 0; i < size; i ++ ) {
		current = path[i];	
		if ( current == '/' ) {
			if ( init_slash_flag == 0 ) {
				init_slash_flag = 1;
				if(!name.empty() ) {
					s_path.push(name);
					name.clear();
				}
			}
			for (int j = i + 1; j < size; j ++ ) {
				if ( path[j] == '/') i ++;
				else break;
			}
			init_slash_flag = 0;
			continue;
		}else if ( current == '.' ) {
			name = '.';
			dot_num++;
			if (dot_num == 1) {
				if ( path[i+1] == '.' )
					dot_num ++;
				while ( (size != (i + 1)) && (path[i+1] != '/')) {  
				   	name += path[i+1];
					i ++;
			   	}
				if ((dot_num == 2)&&(name.size() == 2)) {
				   	if(!s_path.empty()) s_path.pop();
				   	name.clear(); 
				} else if ((dot_num == 1) && (name.size() == 1)) {
				   	name.clear();
			   	}
			}
			dot_num  = 0;
		}else {
			name += current;
		}
	}
	if (name.size() != 0)	s_path.push(name);
	name = "";
	if (s_path.empty()) return "/";
	string path_name("");
	string slash("/");
	while (!s_path.empty()) {
	   	name = s_path.top();
	   	s_path.pop();
		path_name = slash + name + path_name;
	}
	return path_name;
}

int main(int argc, char *argv[]){
	Solution s;
	string path("/////home/../home////../a/b///c/../");
	string res = s.simplifyPath(path);
	cout << res << endl;

	path = "/..";
	res = s.simplifyPath(path);
	cout << res << endl;
	return 1;
}
