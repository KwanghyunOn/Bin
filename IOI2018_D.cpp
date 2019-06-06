#include <bits/stdc++.h>
#include "doll.h"
 
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

int S;
void connect(int root, vector<int> &v, vector<int> &c, vector<int> &x, vector<int> &y) {
	int k = (int)v.size();
	if(k == 1) {
		c[root] = v[0];
		return;
	} else if(k == 2) {
		c[root] = ++S;
		x[S] = v[0];
		y[S] = v[1];
		return;
	}

	int t = 1;
	while(k > (1<<t)) t++;
	vector<Pi> cur;
	cur.push_back({++S, 0});
	c[root] = S;
	int pow2 = 1;
	for(int i = 1; i <= t-2; i++) {
		vector<Pi> next;
		for(auto e : cur) {
			x[e.first] = S+1;
			y[e.first] = S+2;
			next.push_back({++S, e.second});
			next.push_back({++S, e.second + pow2});
		}
		cur = next;
		pow2 *= 2;
	}

	for(auto e : cur) {

	}
}

void create_circuit(int m, vector<int> a) {
	int n = (int)a.size();
 	S = m;
}
