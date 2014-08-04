#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <sys/time.h>
#include <stdlib.h> //atoi
#define DEBUG
using namespace std;

struct AddrTreeNode{
    string path;
    int current;
    int len;
    vector<AddrTreeNode*> kids;
    AddrTreeNode(int x, int y):path(""), current(x), len(y){}
};

class Solution {
    private:
        bool recognizeIpAddresses( string &s, int current, int index,
                AddrTreeNode *parent, map<int, map<int, vector<AddrTreeNode*> > > &mem);
    public:
        vector<string> restoreIpAddresses(string s);
};
bool Solution::recognizeIpAddresses( string &s, int current, int index,
        AddrTreeNode *parent, map<int, map<int, vector<AddrTreeNode*> > > &mem){
    if (index == 4) {
        if (current == (signed)s.size())
            return true;
        else 
            return false;
    } else if (index <= 3){
        if (current == (signed)s.size()) {
            return false;
        }
    }

    if (mem.find(current) != mem.end()) {
        if (mem[current].find(index) != mem[current].end()) {
            if ( !mem[current][index].empty() ) {
                (parent->kids).insert(parent->kids.end(), 
                        mem[current][index].begin(), 
                        mem[current][index].end());
                return true;
            } else return false;
        }
    }

    char buff[3] = {'\0'};
    bool flag = false;
    vector<AddrTreeNode*> curRes;
    mem[current][index] = curRes;
    for( int i = 0; i < 3; i ++) {
        if ((current+i) >= (signed)s.size())   break;
        buff[i] = s[current + i];
        if ((i>0) && (buff[0] == '0'))    break;
        int num = atoi(buff);
        if (num == 0) {
            AddrTreeNode *curNode = new AddrTreeNode(current, i+1);
            bool cur_flag = recognizeIpAddresses(s, current+i+1, index+1, curNode, mem);
            if (cur_flag) {
                mem[current][index].push_back(curNode);
                parent->kids.push_back(curNode);
                flag |= cur_flag;
            }
        } else if (num > 255) {
            break;
        } else {
            AddrTreeNode *curNode = new AddrTreeNode(current, i+1);
            bool cur_flag = recognizeIpAddresses(s, current+i+1, index+1, curNode, mem);
            if (cur_flag) {
                mem[current][index].push_back(curNode);
                parent->kids.push_back(curNode);
                flag |= cur_flag;
            }
        }
    }
    return flag;
}

vector<string> Solution::restoreIpAddresses(string s) {
    map<int, map<int, vector<AddrTreeNode*> > > mem;
    AddrTreeNode head(-1, -1);

    bool flag = recognizeIpAddresses(s, 0, 0, &head, mem);
    vector<string> res;
    if (!flag)  return res;

    stack<AddrTreeNode*> resStack;
    resStack.push(&head);
    while(!resStack.empty()) {
        AddrTreeNode *current = resStack.top();
        string path = current->path;
        resStack.pop();
        if (!current->kids.empty()) {
            for ( unsigned i = 0; i < current->kids.size(); i ++) {
                current->kids[i]->path 
                    = path + s.substr(
                            current->kids[i]->current, 
                            current->kids[i]->len) + ".";
                resStack.push(current->kids[i]);
            }
        } else {
            res.push_back(path.substr(0, path.size()-1));
        }
        current->path = "";
    }

    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    struct timeval first;
    struct timeval second;
    string str1 = "0000";
    cout << str1 << endl;    
    gettimeofday(&first, NULL);
    vector<string> res = s.restoreIpAddresses(str1);
    gettimeofday(&second, NULL);
    for (unsigned i = 0; i < res.size(); i ++) {
        cout << res[i] << "    ";
    }
    cout << endl;
    cout << "The time cost of this operation is --- " 
         << 1000000 * (second.tv_sec - first.tv_sec) + (second.tv_usec -first.tv_usec)
         << endl;
    cout << "---------------------" << endl;

    string str2 = "25525511222";
    cout << str2 << endl;    
    gettimeofday(&first, NULL);
    res = s.restoreIpAddresses(str2);
    gettimeofday(&second, NULL);
    for (unsigned i = 0; i < res.size(); i ++) {
        cout << res[i] << "    ";
    }
    cout << endl;
    cout << "The time cost of this operation is --- " 
         << 1000000 * (second.tv_sec - first.tv_sec) + (second.tv_usec -first.tv_usec)
         << endl;
    cout << "---------------------" << endl;


    string str3 = "255255255255";
    cout << str3 << endl;    
    gettimeofday(&first, NULL);
    res = s.restoreIpAddresses(str3);
    gettimeofday(&second, NULL);
    for (unsigned i = 0; i < res.size(); i ++) {
        cout << res[i] << "    ";
    }
    cout << endl;
    cout << "The time cost of this operation is --- " 
         << 1000000 * (second.tv_sec - first.tv_sec) + (second.tv_usec -first.tv_usec)
         << endl;
    cout << "---------------------" << endl;

    string str4 = "133133133122";
    cout << str4 << endl;    
    gettimeofday(&first, NULL);
    res = s.restoreIpAddresses(str4);
    gettimeofday(&second, NULL);
    for (unsigned i = 0; i < res.size(); i ++) {
        cout << res[i] << "    ";
    }
    cout << endl;
    cout << "The time cost of this operation is --- " 
         << 1000000 * (second.tv_sec - first.tv_sec) + (second.tv_usec -first.tv_usec)
         << endl;
    cout << "---------------------" << endl;

    string str5 = "774094";
    cout << str5 << endl;    
    gettimeofday(&first, NULL);
    res = s.restoreIpAddresses(str5);
    gettimeofday(&second, NULL);
    for (unsigned i = 0; i < res.size(); i ++) {
        cout << res[i] << "    ";
    }
    cout << endl;
    cout << "The time cost of this operation is --- " 
         << 1000000 * (second.tv_sec - first.tv_sec) + (second.tv_usec -first.tv_usec)
         << endl;
    cout << "---------------------" << endl;

    string str6 = "010010";
    cout << str6 << endl;    
    gettimeofday(&first, NULL);
    res = s.restoreIpAddresses(str6);
    gettimeofday(&second, NULL);
    for (unsigned i = 0; i < res.size(); i ++) {
        cout << res[i] << "    ";
    }
    cout << endl;
    cout << "The time cost of this operation is --- " 
         << 1000000 * (second.tv_sec - first.tv_sec) + (second.tv_usec -first.tv_usec)
         << endl;
    cout << "---------------------" << endl;

    string str7 = "172162541";
    cout << str7 << endl;    
    gettimeofday(&first, NULL);
    res = s.restoreIpAddresses(str7);
    gettimeofday(&second, NULL);
    for (unsigned i = 0; i < res.size(); i ++) {
        cout << res[i] << "    ";
    }
    cout << endl;
    cout << "The time cost of this operation is --- " 
         << 1000000 * (second.tv_sec - first.tv_sec) + (second.tv_usec -first.tv_usec)
         << endl;
    cout << "---------------------" << endl;
    return 1;
}
