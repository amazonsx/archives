#include <iostream>
#include <map>
#include <queue>
#define DEBUG
using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode*> neighbors;
    UndirectedGraphNode(int x): label(x) {}
};

class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node);
};

struct NodeFlag {
    UndirectedGraphNode *node;
    int flag; 
    NodeFlag():node(NULL), flag(0){}
    NodeFlag(UndirectedGraphNode *ptr, int flag):node(ptr), flag(flag){}
};

UndirectedGraphNode* Solution::cloneGraph(UndirectedGraphNode *node) {
    if (!node)  return NULL;
    queue<UndirectedGraphNode*> nodeQueue;
    map<int, NodeFlag> labels;

    UndirectedGraphNode *head = new UndirectedGraphNode(node->label);
    NodeFlag headFlag(head, 1);
    labels[head->label] = headFlag;
    for (int i = 0; i < (signed)node->neighbors.size(); i ++) {
        nodeQueue.push(node->neighbors[i]);
        UndirectedGraphNode *neighbor = NULL;
        if (node->neighbors[i] != node ) {
            neighbor = new UndirectedGraphNode(node->neighbors[i]->label);
            NodeFlag flag(neighbor, 0);
            labels[neighbor->label] = flag;
        } else neighbor = head;
        head->neighbors.push_back(labels[neighbor->label].node);
    }

    UndirectedGraphNode *current = NULL, *cpCurrent = NULL;
    while(!nodeQueue.empty()) {
        current = nodeQueue.front();
        nodeQueue.pop();

        if (labels[current->label].flag == 1)   continue;

        labels[current->label].flag = 1;
        cpCurrent = labels[current->label].node;
        for (int i = 0; i < (signed)current->neighbors.size(); i ++) {
            if (labels.find(current->neighbors[i]->label) == labels.end() ) {
                UndirectedGraphNode *neighbor = new UndirectedGraphNode(current->neighbors[i]->label);
                NodeFlag flag(neighbor, 0);
                labels[neighbor->label] = flag;
                nodeQueue.push(current->neighbors[i]);
            } else if (labels[current->neighbors[i]->label].flag == 0) {
                nodeQueue.push(current->neighbors[i]);
            }
            cpCurrent->neighbors.push_back(labels[current->neighbors[i]->label].node); 
        }
    }

    return head;
}

int main(int argc, char *argv[]) {
	return 1;
}
