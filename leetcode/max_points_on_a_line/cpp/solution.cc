#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#define MULTIPLE_SOLUTION
#define DEBUG
using namespace std;

struct Point {
	int x;
	int y;
	Point(): x(0), y(0){}
	Point(int a, int b): x(a), y(b){}
};
typedef struct Point Point;

class Solution{
private:
    int maxPointsS1(vector<Point> &points);
    int maxPointsS2(vector<Point> &points);
public:
    int maxPoints(vector<Point> &points);
};

int Solution::maxPointsS1(vector<Point> &points) {
    int max = 0;
    map<double, int> countMap;
    for ( int i = 0; i < (signed)points.size(); i ++) {
        countMap.clear();
        int tmpMax = 1, coincideCount = 0;
        for ( int j = i+1; j < (signed)points.size(); j ++) {
            double slope  = numeric_limits<double>::infinity();
            if ( points[j].x == points[i].x) {
                if ( points[j].y == points[j].y) {
                    coincideCount ++; 
                    continue;
                }
            } else { slope = 1.0*( points[j].y - points[i].y )/(points[j].x - points[i].x); }
            if (countMap.find(slope) == countMap.end() ) {
                countMap[slope] = 1;
            }
            countMap[slope] ++;
            if (countMap[slope] > tmpMax)   tmpMax = countMap[slope];
        }
        if ( max < (tmpMax + coincideCount) )  max = tmpMax + coincideCount;
    }
    return max;
}

int Solution::maxPointsS2(vector<Point> &points){
	int max = 0;
	//in these special cases, we can get results immediately
	int size = points.size();
	if ( size <= 2 ) return size;

    map< double, int> linePoints;
    for ( int i = 0; i < size; i ++ ) {
        linePoints.clear();
        int samePoints = 0;
        int tmpMax = 0;
        for ( int j = i + 1; j < size; j ++) {
            double slope = numeric_limits<double>::infinity();
            if (points[j].x != points[i].x) {
                slope = 1.0*(points[i].y - points[j].y)/(points[i].x - points[j].x);
            } else if (points[j].y == points[i].y) {
                samePoints ++;
                continue;
            }
            linePoints[slope] ++;
            if ( linePoints[slope] > tmpMax) tmpMax = linePoints[slope];
        }
        if ( max < (samePoints + tmpMax))   max = samePoints + tmpMax;
    }
	return max+1;
}

int Solution::maxPoints(vector<Point> &points){
    int res = maxPointsS1(points);
#ifdef MULTIPLE_SOLUTION
    int res1 = maxPointsS2(points);
    assert(res == res1);
#endif
    return res;
}

int main(int argc, char *argv[]){
	Solution s;
	int max;
	vector<Point> vp;
	vector<Point> &points = vp;
	
	max = s.maxPoints(points);
	cout << "A null point vector:" << max << endl;
	cout << "-------------------------" << endl;
	
	//Point p(0, 0);
	//Point q(-1, -1);
	//Point r(2, 2);
	Point p(1, 1);
	Point q(1, 1);
	Point r(1, 1);
	//Point o(-6, -1);
	vp.insert( vp.end(), p);
	vp.insert( vp.end(), q);
	vp.insert( vp.end(), r);
	//vp.insert( vp.end(), o);
	max = s.maxPoints(points);
	cout << "res: " << max << endl;
	cout << "-------------------------" << endl;
/*
	Point a(1, 2);
	Point b(2, 2);
	Point c(2, 4);
	Point d(3, 4);
	Point e(4, 6);
	vp.clear();
	vp.insert( vp.end(), a);
	vp.insert( vp.end(), b);
	vp.insert( vp.end(), c);
	vp.insert( vp.end(), d);
	vp.insert( vp.end(), e);
	max = s.maxPoints(points);
	cout << "A null point vector:" << max << endl;
	cout << "-------------------------" << endl;
*/
	return 1;
}
