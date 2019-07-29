#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define rep(pos, len) for(int pos=0; pos<len; pos++)
#define repp(pos, len) for(int pos=1; pos<=len; pos++)

#define INF 987654321
#define IINF 2987654321987654321
#define MOD 1000000007

typedef pair<ll, int> pli;

struct Node {
	int to;
	ll weight;
};

const int MAXN = 2e5 + 50;
vector<Node> adj[MAXN];
int n, k;
void readInput() {
	scanf("%d%d", &n, &k);
	rep(i, n-1) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
}


bool vis[MAXN];
int sz[MAXN];
void dfsSize(int v, int p) {
	sz[v] = 1;
	for(auto c : adj[v]) if(!vis[c.to] && c.to != p) {
		dfsSize(c.to, v);
		sz[v] += sz[c.to];
	}
}

int dfsCentroid(int v, int p, int size) {
	for(auto c : adj[v])
		if(!vis[c.to] && c.to != p && sz[c.to] > size/2)
			return dfsCentroid(c.to, v, size);
	return v;
}


int ans = INF;
void merge(int v, int p, int len, ll wsum, map<ll, int> &M, vector<pli> &tmp) {
	if(wsum > k) return;
	if(M.find(k-wsum) != M.end()) ans = min(ans, M[k-wsum] + len);
	tmp.emplace_back(wsum, len);
	for(auto c : adj[v]) if(!vis[c.to] && c.to != p)
		merge(c.to, v, len+1, wsum + c.weight, M, tmp);
}

void solve(int ctr) {
	map<ll, int> M;
	M.insert({0, 0});		// centroid itself
	for(auto c : adj[ctr]) if(!vis[c.to]) {
		vector<pli> tmp;
		merge(c.to, ctr, 1, c.weight, M, tmp);
		for(auto e : tmp) {
			if(M.find(e.first) != M.end()) M[e.first] = min(M[e.first], e.second);
			else M.insert(e);
		}
	}
}

void decompose(int v) {
	dfsSize(v, -1);
	int ctr = dfsCentroid(v, -1, sz[v]);
	solve(ctr);
	vis[ctr] = true;
	for(auto c : adj[ctr])
		if(!vis[c.to]) decompose(c.to);
}


int main() {
	// freopen("input.txt", "r", stdin);
	readInput();
	decompose(0);
	printf("%d\n", (ans == INF) ? -1 : ans);
}
