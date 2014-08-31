/*
 * The cpp implentation of max points on a line
 * Caveat:
 *	boundary condition:
 *		points with same x value;
 *		points with same x an y value;
 *		to be continued 
 *		Its very complicated
 */
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <math.h>
#include <stdlib.h>
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
	public:
		int maxPoints(vector<Point> &points);
};

int Solution::maxPoints(vector<Point> &points){
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
        cout << samePoints << "       " << tmpMax << endl;
        if ( max < (samePoints + tmpMax))   max = samePoints + tmpMax;
    }

	return max+1;
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
