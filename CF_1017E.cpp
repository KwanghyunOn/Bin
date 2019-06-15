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


/********** struct point **********/
typedef complex<double> Point;
#define x real()
#define y imag()
#define M_PI 3.14159265358979323846

Point scale(Point p, Point o, double factor) { return o + (p-o)*factor; }
Point rotate(Point p, double a) { return p * polar(1.0, a); }
Point perp(Point p) { return {-p.y, p.x}; }
double sq(Point v) { return v.x*v.x + v.y*v.y; }
double dot(Point v, Point w) { return (conj(v) * w).x; }
double cross(Point v, Point w) { return (conj(v) * w).y; }
double angle(Point v, Point w) {
	double cosA = dot(v, w) / abs(v) / abs(w);
	return acos(max(-1.0, min(1.0, cosA)));
}
double ccw(Point a, Point b, Point o) { return cross(a-o, b-o); }


// finding convex hull
vector<Point> convexHull(vector<Point> p) {
	sort(p.begin(), p.end(), [](Point a, Point b) {
		return make_tuple(a.x, a.y) < make_tuple(b.x, b.y);
	});
	vector<Point> hull;
	hull.reserve(p.size() + 1);
	for(int phase = 0; phase < 2; phase++) {
		auto start = hull.size();
		for(auto v : p) {
			while(hull.size() >= start+2 && ccw(v, hull.back(), hull[hull.size()-2]) <= 0)
				hull.pop_back();
			hull.push_back(v);
		}
		hull.pop_back();
		reverse(p.begin(), p.end());
	}
	if(hull.size() == 2 && hull[0] == hull[1]) hull.pop_back();
	return hull;
}



int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<Point> a(n), b(m);
	rep(i, n) {
		double px, py;
		scanf("%lf%lf", &px, &py);
		a[i] = {px, py};
	}
	rep(i, m) {
		double px, py;
		scanf("%lf%lf", &px, &py);
		b[i] = {px, py};
	}

	a = convexHull(a);
	b = convexHull(b);
	if(a.size() != b.size()) {
		printf("NO\n");
		return 0;
	}
	int k = (int)a.size();
	vector<double> av, bv;
	for(int i = 0; i < k; i++) {
		av.push_back(abs(a[i] - a[(i+1)%k]));
		av.push_back(angle(a[i] - a[(i+1)%k], a[(i+2)%k] - a[(i+1)%k]));
		bv.push_back(abs(b[i] - b[(i+1)%k]));
		bv.push_back(angle(b[i] - b[(i+1)%k], b[(i+2)%k] - b[(i+1)%k]));
	}
}
