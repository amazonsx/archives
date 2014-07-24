#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

struct Interval {
    int start;
    int end;
    Interval():start(0), end(0) {}
    Interval(int s, int e):start(s), end(e) {}
};

class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval);
};

vector<Interval> Solution::insert(vector<Interval> &intervals, Interval newInterval){
    if (intervals.empty()) {
        intervals.push_back(newInterval);
    }
    int currentStart = -1;
    int flag = 0;
    vector<Interval>::iterator iter = intervals.begin();
    while (iter != intervals.end()) {
        if (newInterval.start > iter->end) {   
            iter ++;
            if (iter == intervals.end()) {
                intervals.push_back(newInterval);
            }
            continue;
        } else if ( flag == 1 ) {
            if (newInterval.end > iter->end) {
                iter = intervals.erase(iter);
                if (iter == intervals.end()) {
                    Interval inter(currentStart, newInterval.end);
                    intervals.push_back(inter);
                }
                continue;
            } else if (newInterval.end < iter->start) {
                Interval inter(currentStart, newInterval.end);
                intervals.insert( iter - 1, inter);
            } else {
                iter->start = currentStart;
            }
            break;
        } else if (newInterval.start <= iter->start) {
            if (newInterval.end < iter->start) {
                vector<Interval>::iterator pos = intervals.begin();
                if (iter != intervals.begin()) pos = iter - 1;
                intervals.insert( pos, newInterval);
            } else if (newInterval.end <= iter->end) {
                iter->start = newInterval.start;
            } else {
                currentStart = newInterval.start;
                flag = 1;
                iter = intervals.erase(iter);
                if (iter == intervals.end()) {
                    Interval inter(currentStart, newInterval.end);
                    intervals.push_back(inter);
                }
                continue;
            }
            break;
        }  else if (newInterval.start <= iter->end) {
            if (newInterval.end <= iter->end) {
                break;
            } else {
                currentStart = iter->start;
                flag = 1;
                iter = intervals.erase(iter);
                if (iter == intervals.end()) {
                    Interval inter(currentStart, newInterval.end);
                    intervals.push_back(inter);
                }
                continue;
            }
        }
    }
    vector<Interval> res;
    res.assign(intervals.begin(), intervals.end());
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    /*
    Interval i1(2, 5);
    Interval i2(6, 7);
    Interval i3(8, 9);
    vector<Interval> intervals;
    intervals.push_back(i1);
    intervals.push_back(i2);
    intervals.push_back(i3);

    Interval newInterval(0, 10);
    */
    /*
    Interval i1(1, 8);
    vector<Interval> intervals;
    intervals.push_back(i1);
    Interval newInterval(10, 15);
    */
    Interval i1(0, 9);
    vector<Interval> intervals;
    intervals.push_back(i1);
    Interval newInterval(14, 15);

    vector<Interval> res = s.insert(intervals, newInterval);
    for ( int i = 0; i < (signed)res.size(); i ++ ) {
        cout << res[i].start << "    " << res[i].end << endl;
    }
	return 1;
}
