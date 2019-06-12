// https://codeforces.com/problemset/problem/464/B

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

struct Node {
	ll x[3];
} a[8];

void solve() {
	
}

void dfs(int i) {
	if(i == 8) {
		solve();
		return;
	}
	sort(a[i].x, a[i].x+3);
	do {
		dfs(i+1);
	} while(next_permutation(a[i].x, a[i].x+3));
}

int main() {
	rep(i, 8) rep(j, 3) scanf("%lld", &a[i].x[j]);
	dfs(1);
	printf("NO\n");
}
