#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <sys/time.h>
#define DEBUG
using namespace std;

struct WordTreeNode{
    unsigned start;
    int len;
    vector<WordTreeNode*> descendants;
    WordTreeNode():start(0),len(-1){}
    WordTreeNode(unsigned int start, int len):start(start), len(len) {}
};

class Solution {
private:
    bool splitWords(string s, unsigned start, unordered_set<string> &dict, 
            map<char, unordered_set<unsigned int> > &dict_data, WordTreeNode *head, map<int, map<int, WordTreeNode*> > &mem_nodes );
    void BFS( WordTreeNode *head, string s, map<WordTreeNode*, unordered_set<string> > &mem_str, 
            vector<string> &res, string formerStr);
    void init( map<char, unordered_set<unsigned int> > &dict_data, unordered_set<string> &dict);
public:
    vector<string> wordBreak(string s, unordered_set<string> &dict);
}i;

void Solution::BFS( WordTreeNode *head, string s, map<WordTreeNode*, unordered_set<string> > &mem_str, 
        vector<string> &res, string formerStr) {
    if (mem_str.find(head) != mem_str.end()) {
        for ( unordered_set<string>::iterator iter = mem_str[head].begin();
                iter != mem_str[head].end(); iter ++) {
            cout << *iter << endl;
            res.push_back(formerStr + *iter);    
        }
        return;
    }
    string currentStr("");
    if ( head->descendants.size() == 0) { 
        currentStr = s.substr(head->start, head->len);
        mem_str[head].insert(currentStr);
        res.push_back( formerStr + currentStr);
        return;
    }
    // head may be the root which is empty
    if (head->len != -1)
        currentStr = s.substr(head->start, head->len) + " ";

    for ( unsigned int i = 0; i < head->descendants.size(); i ++) {
        BFS( head->descendants[i], s, mem_str, res, formerStr + currentStr);
        for ( unordered_set<string>::iterator iter = mem_str[head->descendants[i]].begin();
                iter != mem_str[head->descendants[i]].end(); iter ++) {
            mem_str[head].insert(currentStr + *iter);
        }
    }
}

void Solution::init( map<char, unordered_set<unsigned int> > &dict_data, unordered_set<string> &dict) {
    for ( unordered_set<string>::iterator iter = dict.begin();
            iter != dict.end(); iter ++) {
        dict_data[(*iter)[0]].insert((*iter).size());
    }
}

bool Solution::splitWords(string s, unsigned start, unordered_set<string> &dict, 
        map<char, unordered_set<unsigned int> > &dict_data, WordTreeNode *head, 
        map<int, map<int, WordTreeNode*> > &mem_nodes) {
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
    bool res = false;
    for ( unordered_set<unsigned int>::iterator iter = dict_data[s[start]].begin();
            iter != dict_data[s[start]].end(); iter ++) {
        int len = (signed)(*iter);
        if ( (start + len) > s.size())  continue;
        string current = s.substr(start, len);
        if (dict.find(current) == dict.end()) continue;
        if (mem_nodes.find(start) != mem_nodes.end()) {
            if (mem_nodes[start].find(len) != mem_nodes[start].end()) {
                if (mem_nodes[start][len] != NULL) {
                    head->descendants.push_back(mem_nodes[start][len]);
                    res = true;
                }
                continue;
            }
        }
        WordTreeNode *currentNode = new WordTreeNode( start, len);
        if ((start+len) == s.size()) {
            head->descendants.push_back(currentNode);
            res = true;
            continue;
        }
        bool current_res = splitWords( s, start+len, dict, dict_data, currentNode, mem_nodes);
        if (current_res) {
            head->descendants.push_back(currentNode);
            mem_nodes[start][len] = currentNode;
        } else {
            delete currentNode;
            mem_nodes[start][len] = NULL;
        }
        res |= current_res;
    }
    return res;    
}

vector<string> Solution::wordBreak(string s, unordered_set<string> &dict) {
    vector<string> res;
    if (dict.size() == 0)   return res;
    map<char, unordered_set<unsigned int> >  dict_data;
    init( dict_data, dict);

    WordTreeNode head;
    // map< start, map< len, WordTreeNode*> > 
    map<int, map<int, WordTreeNode*> > mem_nodes;
    bool avail = splitWords(s, 0, dict, dict_data, &head, mem_nodes);
    if (!avail) return res;

    map<WordTreeNode*, unordered_set<string> > mem_str;
    BFS( &head, s, mem_str, res, "");
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    /*
    string str("aaaaaaa");
    unordered_set<string> dict({"aaaa", "aa"});

    string str("catsanddog");
    unordered_set<string> dict({"cat", "cats", "and", "sand", "dog"});

    string str("a");
    unordered_set<string> dict({"b"});

    string str("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab");
    unordered_set<string> dict({"aaaaaaaaaaa", "aaaaaa", "b"});

    string str("ab");
    unordered_set<string> dict({"a", "b"});

    string str("a");
    unordered_set<string> dict({"a"});

    string str("ab");
    unordered_set<string> dict({"a", "b"});
    */

    string str("aaaaaaa");
    unordered_set<string> dict({"aaaa","aa","a"});

    struct timeval first;
    gettimeofday(&first, NULL);

    vector<string> res = s.wordBreak(str, dict);

    struct timeval second;
    gettimeofday(&second, NULL);
    cout << "Total time: " << 1000000 * (second.tv_sec - first.tv_sec ) + second.tv_usec - first.tv_usec << endl;

    cout << "Res size is " << res.size() << endl;
    for ( unsigned int i = 0; i < res.size(); i ++ ) {
        cout << res[i] <<"-"<< endl;
    }
	return 1;
}
