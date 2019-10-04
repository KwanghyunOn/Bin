#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)

#define INF 987654321
#define IINF 2987654321987654321
#define MOD 1000000007

inline ll madd(ll a, ll b) { return (a+b)%MOD; }
inline ll msub(ll a, ll b) { return (a-b+MOD)%MOD; }
inline ll mmul(ll a, ll b) { return (a*b)%MOD; }

const int MAXN = 5050;
int n;
vector<int> adj[MAXN];
void readInput() {
	scanf("%d", &n);
	for(int i = 0; i < n-1; i++) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

ll g[MAXN];
void preprocess() {
	g[2] = 1;
	for(int m = 4; m < MAXN; m += 2)
		g[m] = mmul(g[m-2], m-1);
}

ll dp[MAXN][MAXN][2], S[MAXN][2];
ll sz[MAXN], tmp[MAXN][2];
void dfs(int v, int p) {
	sz[v] = 1;
	dp[v][1][0] = 1;

	ll sum = 0;
	for(auto c : adj[v]) if(c != p) {
		dfs(c, v);
		sz[v] += sz[c];

		for(int m = 0; m <= (sum + sz[c]); m++)
			rep(x, 2) tmp[m][x] = 0;
		for(int m = 0; m <= (sum + sz[c]); m++)
			rep(x, 2) rep(y, 2) tmp[m][x^y^1] = madd(tmp[m][x^y^1], mmul(dp[v][m][x], S[c][y]));
		for(int m = 0; m <= sum; m++)
			for(int k = 0; k <= sz[c]; k++)
				rep(x, 2) rep(y, 2) tmp[m+k][x^y] = madd(tmp[m+k][x^y], mmul(dp[v][m][x], dp[c][k][y]));
		for(int m = 0; m <= (sum + sz[c]); m++)
			rep(x, 2) dp[v][m][x] = tmp[m][x];

		sum += sz[c];
	}

	for(int m = 0; m <= sz[v]; m++)
		rep(x, 2) S[v][x] = madd(S[v][x], mmul(dp[v][m][x], g[m]));

	printf("[%d]: %lld, %lld\n", v, S[v][0], S[v][1]);
}


int main() {
	preprocess();
	readInput();
	dfs(1, -1);
	printf("%lld\n", msub(S[1][0], S[1][1]));
}
