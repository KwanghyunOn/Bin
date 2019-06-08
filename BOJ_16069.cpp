#include <bits/stdc++.h>
//#include "doll.h"
 
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

typedef unsigned long long ull;

ll lpow(ll a, ll b) {
	ll res = 1;
	for(int i = 0; i < 64; i++) {
		if(b&(1LL<<i)) res *= a;
		a *= a;
	}
	return res;
}

inline ll f3(ll n) {
	return n*(n+1)*(2*n+1)/6;
}

const int M3 = 350505;
int main() {
	ll m; cin >> m;
	ll s = 0;

	// n = 3
	ll low = 1, high = M3;
	while(low <= high) {
		ll mid = (low + high) / 2;
		if(f3(mid) <= m) {
			s = mid;
			low = mid+1;
		} else {
			high = mid-1;
		}
	}
	if(f3(s) == m) {
		cout << 3 << " " << s << endl;
		return 0;
	}

	// n >= 4
	for(ll n = 4; n <= 53; n++) {
		for(ll s = 1; )
	}
}
