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

ll gcd(ll a, ll b) {
	if(!b) return a;
	return gcd(b, a%b);
}

ll inverse(ll a, ll m) {
    ll m0 = m, t, q;
    ll x0 = 0, x1 = 1;
 
    if (m == 1)
      return 0;
 
    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;
 
        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
 
    // Make x1 positive
    if (x1 < 0)
       x1 += m0;
    return x1;
}


ll p = 9705276, q = 12805858, pinv = -1;
Pll findNum(ll m) {
	ll x = (m * pinv) % q;
	ll y = (m - p*x) / q;
	if(p*x + q*y == m && x >= 0 && y >= 0) return {x, y};
	else return {-1, -1};
}

int main() {
	ll g = gcd(p, q);
	p /= g;
	q /= g;
	pinv = inverse(p, q);

	int n; scanf("%d", &n);
	vector<Pll> v;
	rep(i, n) {
		double t; scanf("%lf", &t);
		ll m = (ll)(t*1e5 + 0.5);
		if(m%g) continue;
		Pll tmp = findNum(m/g);
		if(tmp.first != -1) v.push_back(tmp);
	}
}
