#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

struct Interval {
    int start;
    int end;
    Interval():start(0),end(0){}
    Interval(int s, int e):start(s), end(e) {}
};

class Solution {
    private:
        void quicksort(vector<Interval> &intervals, int left, int right);
    public:
        // The intervals may be not listed in order
        vector<Interval> merge(vector<Interval> &intervals);
};

void Solution::quicksort(vector<Interval> &intervals, int left, int right) {
    if (left >= right)  return;
    int i = left - 1, j = left; 
    int pivot = intervals[right].start;
    Interval tmp;
    while ( j < right ) {
        if (intervals[j].start <= pivot) {
            i++;
            tmp = intervals[j];
            intervals[j] = intervals[i];
            intervals[i] = tmp;
        }
        j++;
    }
    tmp = intervals[right];
    intervals[right] = intervals[++i];
    intervals[i] = tmp;
    quicksort(intervals, left, i-1);
    quicksort(intervals, i+1, right);
}

vector<Interval> Solution::merge(vector<Interval> &intervals) {
    vector<Interval> res;
    if (intervals.empty())  return res;
    quicksort( intervals, 0, intervals.size()-1);
    vector<Interval>::iterator iter = intervals.begin();
    int formerStart = iter->start;
    int maxEnd = iter->end;
    for (; iter != intervals.end(); iter ++) {
        int curStart = iter->start;

        if (curStart == formerStart) {
            if (iter->end > maxEnd) {
                maxEnd = iter->end;
            }
        } else {
            if (res.empty()) {
                Interval tmp(formerStart, maxEnd);
                res.push_back(tmp);
            } else {
                if (formerStart <= res.back().end) { 
                    if (maxEnd > res.back().end) {
                        res[res.size() - 1].end = maxEnd;
                    } 
                } else {
                    Interval tmp(formerStart, maxEnd);
                    res.push_back(tmp);
                }
            }
            formerStart = curStart;
            maxEnd = iter->end;
        }
    }
    if (res.empty()) {
        Interval tmp(formerStart, maxEnd);
        res.push_back(tmp);
    } else if (formerStart <= res.back().end) { 
        if (maxEnd > res.back().end) {
            res[res.size() - 1].end = maxEnd;
        } 
    } else {
        Interval tmp(formerStart, maxEnd);
        res.push_back(tmp);
    }
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    Interval inter1(1, 4);
    Interval inter2(7, 8);
    Interval inter3(2, 7);
    Interval inter4(10, 11);
    Interval inter5(3, 5);
    Interval inter6(2, 8);
    vector<Interval> intervals;
    intervals.push_back(inter1);
    intervals.push_back(inter2);
    intervals.push_back(inter3);
    intervals.push_back(inter4);
    intervals.push_back(inter5);
    intervals.push_back(inter6);

    vector<Interval> res = s.merge(intervals);
    for (int i = 0; i < (signed)res.size(); i ++) {
        cout << res[i].start << "," << res[i].end << "   " ;
    }
    cout << endl;
    return 1;
}
