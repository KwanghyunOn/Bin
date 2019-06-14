#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> Pi;
typedef pair<ll, ll> Pll;
 
#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
 
#define INF 87654321
#define IINF 87654321987654321
#define MOD 1000000007
// 1-index
#define L(x) ((x)<<1)
#define R(x) (((x)<<1)+1)

inline double sq(double t) {
	return t*t;
}

struct Point {
	double x, y;

	Point operator - (const Point &t) const {
		return {x - t.x, y - t.y};
	}
	Point operator + (const Point &t) const {
		return {x + t.x, y + t.y};
	}
	Point operator * (double r) const {
		return {x*r, y*r};
	}
	double norm() {
		return sqrt(x*x + y*y);
	}
};

inline double dist(Point &a, Point &b) {
	return sq(a.x-b.x) + sq(a.y-b.y);
}
inline double triangleArea(Point &a, Point &b, Point &c) {
	return abs(a.x*b.y + b.x*c.y + c.x*a.y - b.x*a.y - c.x*b.y - a.x*c.y) / 2.0;
}
inline double dot(Point &a, Point &b) {
	return a.x*b.x + a.y*b.y;
}
inline double pointToLine(Point &a, Point &p, Point &q) {
	return 2.0 * triangleArea(a, p, q) / ((p-q).norm());
}
inline double pointToSeg(Point &a, Point &p, Point &q) {
	if(dot(a-p, q-p) < 0) return dist(a, p);
	else if(dot(a-q, p-q) < 0) return dist(a, q);
	else return pointToLine(a, p, q);
}
inline double segToSeg(Point &a, Point &b, Point &x, Point &y) {
	return min({pointToSeg(a, x, y), pointToSeg(b, x, y), pointToSeg(x, a, b), pointToSeg(y, a, b)});
}

Point findPoint(Point &a, Point &b, double d) {
	Point c = b-a;
	return a + c * (d / c.norm())
}



const int MAXN = 1e5 + 50;
Point a[MAXN], b[MAXN];
int n, m;
void readInput() {
	scanf("%d", &n);
	repp(i, n) scanf("%lf%lf", &a[i].x, &a[i].y);
	scanf("%d", &m);
	repp(i, m) scanf("%lf%lf", &b[i].x, &b[i].y);
}


void solve() {
	int ai = 1, bi = 1;
	double da = 0.0, db = 0.0;
	while(ai < n && bi < m) {
		Point sa = findPoint(a[ai], a[ai+1], da);
		Point sb = findPoint(b[bi], b[bi+1], db);
		double la = dist(a[ai], a[ai+1]) - da, lb = dist(b[bi], b[bi+1]) - db;
		
	}
}


int main() {
	readInput();
	solve();
}
