#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <sys/time.h>
#define DEBUG
using namespace std;

struct TreeNode{
    unsigned start;
    int len;
    vector<TreeNode*> descendants;
    TreeNode():start(0),len(-1){}
    TreeNode(unsigned start, int len):start(start), len(len) {}
};

class Solution {
private:
    bool splitWords(string s, unsigned start, unordered_set<string> &dict, 
            map<char, vector<unsigned int> > dict_data, TreeNode *head, map<int, map<int, TreeNode*> > &mem_nodes );
    void BFS( TreeNode *head, string s, map<TreeNode*, unordered_set<string> > &mem_str);
    void init( map<char, vector<unsigned int> > &dict_data, unordered_set<string> &dict);
public:
    vector<string> wordBreak(string s, unordered_set<string> &dict);
};

void Solution::BFS( TreeNode *head, string s, map<TreeNode*, unordered_set<string> > &mem_str) {
    if ( head->descendants.size() == 0) { 
        mem_str[head].insert(s.substr(head->start, head->len));
        return;
    }
    if (mem_str.find(head) != mem_str.end())    return;
    string current("");     
    if (head->len > 0)
        current = s.substr(head->start, head->len) + " ";

    for ( unsigned int i = 0; i < head->descendants.size(); i ++) {
        BFS( head->descendants[i], s, mem_str);
        for ( unordered_set<string>::iterator iter = mem_str[head->descendants[i]].begin();
                iter != mem_str[head->descendants[i]].end(); iter ++) {
            string tmp = current + *iter;
            mem_str[head].insert(tmp);
        }
    }
}

void Solution::init( map<char, vector<unsigned int> > &dict_data, unordered_set<string> &dict) {
    for ( unordered_set<string>::iterator iter = dict.begin();
            iter != dict.end(); iter ++) {
        if ( dict_data[(*iter)[0]].size() == 0){
            dict_data[(*iter)[0]].push_back(iter->size());
            dict_data[(*iter)[0]].push_back(iter->size());
        } else {
            if ( iter->size() < dict_data[(*iter)[0]][0]) {
                dict_data[(*iter)[0]][0] = iter->size();
            } else if (iter->size() > dict_data[(*iter)[0]][1]) {
                dict_data[(*iter)[0]][1] = iter->size();
            }
        }
    }
}

bool Solution::splitWords(string s, unsigned start, unordered_set<string> &dict, 
        map<char, vector<unsigned int> > dict_data, TreeNode *head, 
        map<int, map<int, TreeNode*> > &mem_nodes) {
    // corner case: start = s.size() = 0
    if (start == s.size())  {
        return true;
    }
    if (start > s.size()) {
        return false;
    }
    if (dict_data.find(s[start]) == dict_data.end()) {
        return false;
    }
    unsigned int len = dict_data[s[start]][0];
    bool res = false;
    while( len <= dict_data[s[start]][1]) {
        if ((start + len) > s.size())   break;
        string current = s.substr(start, len);
        if ( dict.find(current) != dict.end()) {
            if (mem_nodes.find(start) != mem_nodes.end()) {
                if (mem_nodes[start].find(len) != mem_nodes[start].end()) {
                    if (mem_nodes[start][len] != NULL){
                        head->descendants.push_back(mem_nodes[start][len]);
                        res = true;
                    }
                    len ++;
                    continue;
                }
            } 
            TreeNode *currentNode = new TreeNode( start, len);
            bool cur_res = splitWords( s, start + len, dict, dict_data, currentNode, mem_nodes);
            if (cur_res) {
                head->descendants.push_back( currentNode);
                mem_nodes[start][len] =  currentNode;
            } else {
                mem_nodes[start][len] =  NULL;
                delete currentNode;
            }
            res |= cur_res;
        }
        len ++;
    }
    
    if (!res) return false;
    return true;
}

vector<string> Solution::wordBreak(string s, unordered_set<string> &dict) {
    map<char, vector<unsigned int> >  dict_data;
    init( dict_data, dict);

    vector<string> res;
    if (dict_data.size() == 0) {
        return res;
    }
    TreeNode head;
    map<int, map<int, TreeNode*> > mem_nodes;
    bool avail = splitWords(s, 0, dict, dict_data, &head, mem_nodes);
    if (!avail) return res;

    map<TreeNode*, unordered_set<string> > mem_str;
    BFS( &head, s, mem_str);
    for ( unsigned i = 0; i < head.descendants.size(); i ++) {
        res.insert(res.end(), mem_str[head.descendants[i]].begin(), mem_str[head.descendants[i]].end());
    }
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    /*
    string str("catsanddog");
    unordered_set<string> dict({"cat", "cats", "and", "sand", "dog"});
    string str("a");
    unordered_set<string> dict({"b"});
    string str("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab");
    unordered_set<string> dict({"aaaaaaaaaaa", "aaaaaa", "b"});
    string str("ab");
    unordered_set<string> dict({"a", "b"});
    string str("aaaaaaa");
    unordered_set<string> dict({"aaaa", "aa"});
    */
    string str("a");
    unordered_set<string> dict({"a"});

    struct timeval first;
    gettimeofday(&first, NULL);

    vector<string> res = s.wordBreak(str, dict);

    struct timeval second;
    gettimeofday(&second, NULL);
    cout << "Total time" << 1000000 * (second.tv_sec - first.tv_sec ) + second.tv_usec - first.tv_usec << endl;

    cout << "Res size is " << res.size() << endl;
    for ( unsigned int i = 0; i < res.size(); i ++ ) {
        cout << res[i] <<"-"<< endl;
    }
	return 1;
}
