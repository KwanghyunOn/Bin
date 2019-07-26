#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
	
#define INF 1987654321
#define IINF 2987654321987654321
#define MOD 998244353

inline madd(ll a, ll b) { return (a+b)%MOD; }
inline mmul(ll a, ll b) { return (a*b)%MOD; }
inline msub(ll a, ll b) { return (a-b+MOD)%MOD; }

const int LOGN = 30;
ll mpow(ll a, int b) {
	ll apow = a, res = 1;
	for(int i = 0; i < LOGN; i++) {
		if(b & (1<<i)) res = mmul(res, apow); 
		apow = mmul(apow, apow);
	}
	return res;
}


const ll g = 15311432;
const int gpow = 23;
ll inv2[LOGN];

void fft(vector<ll> &a, bool invert) {
	int n = (int)a.size();
	for(int i = 1, j = 0; i < n; i++) {
		int bit = (n >> 1);
		for(; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}
	int k = 1;
	for(int len = 2; len <= n; len <<= 1, k++) {
		ll w = g;
		for(int i = 0; i < gpow-k; i++) w = mmul(w, w);
		for(int i = 0; i < n; i += len) {
			ll wpow = 1;
			for(int j = 0; j < len/2; j++) {
				ll u = a[i+j], v = mmul(wpow, a[i+j+len/2]);
				a[i+j] = madd(u, v);
				a[i+j+len/2] = msub(u, v);
				wpow = mmul(wpow, w);
			}
		}
	}
	if(invert)
		for(int i = 0; i < n; i++) a[i] = mmul(a[i], inv2[k-1]);
}


void preprocess() {
	inv2[0] = 1;
	inv2[1] = (MOD+1)/2;
	for(int i = 2; i < LOGN; i++)
		inv2[i] = mmul(inv2[i-1], inv2[1]);
}


int main() {
	freopen("input.txt", "r", stdin);
	
	preprocess();
	
}
