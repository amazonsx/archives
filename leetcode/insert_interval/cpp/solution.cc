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
    vector<Interval>::iterator cursor = intervals.begin(); 
    int flag = 0;
    while (cursor != intervals.end()) {
        if (newInterval.start < cursor->start) {
            if (newInterval.end < cursor->start) {
                intervals.insert(cursor, newInterval);
                flag = 1;
                break;
            } else if (newInterval.end <= cursor->end) {
                cursor->start = newInterval.start;
                flag = 1;
                break;
            } else {
                vector<Interval>::iterator tmp = cursor;
                tmp->start = newInterval.start;
                cursor ++;
                if (cursor == intervals.end()) {
                    tmp->end = newInterval.end;
                }
                while (cursor != intervals.end()) {
                    if (newInterval.end < cursor->start) {
                        tmp->end = newInterval.end;
                        break;
                    } else if (newInterval.end <= cursor->end) {
                        tmp->end = cursor->end;
                        cursor = intervals.erase(cursor);
                        break;
                    } else {
                        cursor = intervals.erase(cursor);
                        if (cursor == intervals.end())
                            tmp->end = newInterval.end;
                    }
                }
                flag = 1;
                break;
            }
        } else if (newInterval.start <= cursor->end) {
            if (newInterval.end <= cursor->end) {
                flag = 1;
                break;
            } else {
                vector<Interval>::iterator tmp = cursor;
                cursor ++;
                if (cursor == intervals.end()) {
                    tmp->end = newInterval.end;
                }
                while (cursor != intervals.end()) {
                    if (newInterval.end < cursor->start) {
                        tmp->end = newInterval.end;
                        break;
                    } else if (newInterval.end <= cursor->end) {
                        tmp->end = cursor->end;
                        cursor = intervals.erase(cursor);
                        break;
                    } else {
                        cursor = intervals.erase(cursor);
                        if (cursor == intervals.end())
                            tmp->end = newInterval.end;
                    }
                }
                flag = 1;
                break;
            }
        } else {
            cursor ++;
        }
    }
    if (flag == 0) {
        intervals.push_back(newInterval);
    }

    return intervals;
}

int main(int argc, char *argv[]) {
    Solution s;
    Interval i1(2, 5);
    Interval i2(6, 7);
    Interval i3(8, 9);
    vector<Interval> intervals;
    intervals.push_back(i1);
    intervals.push_back(i2);
    intervals.push_back(i3);

    Interval newInterval(0, 10);
    /*
    Interval i1(1, 8);
    vector<Interval> intervals;
    intervals.push_back(i1);
    Interval newInterval(10, 15);
    */
    /*
    Interval i1(0, 9);
    vector<Interval> intervals;
    intervals.push_back(i1);
    Interval newInterval(14, 15);
    */

    vector<Interval> res = s.insert(intervals, newInterval);
    for ( int i = 0; i < (signed)res.size(); i ++ ) {
        cout << res[i].start << "    " << res[i].end << endl;
    }
	return 1;
}
