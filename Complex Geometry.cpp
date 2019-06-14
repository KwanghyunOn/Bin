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

typedef complex<double> Point;
#define x real()
#define y imag()
#define PI 3.14159265358979323846

Point rotate(Point p, double a) { return p * polar(1.0, a); }
Point linearTransformation(Point x, Point p, Point fp, Point q, Point fq) {
	return fp + (x-p) * (fq-fp) / (q-p);
}
double dot(Point v, Point w) { return (conj(v) * w).x; }
double cross(Point v, Point w) { return (conj(v) * w).y; }
double angle(Point v, Point w) {
	double cosA = dot(v, w) / abs(v) / abs(w);
	return acos(max(-1.0, min(1.0, cosA)));
}
double orient(Point a, Point b, Point c) { return cross(b-a, c-a); }
bool inAngle(Point o, Point a, Point b, Point p) {
	assert(orient(o, a, b) != 0);
	if(orient(o, a, b) < 0) swap(a, b);
	return orient(o, a, p) >= 0 && orient(o, b, p) <= 0;
}
double orientedAngle(Point o, Point a, Point b) {
	if(orient(o, a, b) >= 0) return angle(a-o, b-o);
	else return 2*PI - angle(a-o, b-o);
}
