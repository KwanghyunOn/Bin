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

struct SegmentTree {
	int n;
	vector<int> st;
	void init(int sz) {
		n = 1;
		while(n < sz) n <<= 1;
		st.assign(2*n, 0);
	}

	void update(int p, int val) {
		p += n-1;
		st[p] += val;
		for(p >>= 1; p; p >>= 1)
			st[p] = st[2*p] + st[2*p+1];
	}

	int rangeSum(int l, int r) {
		int sum = 0;
		for(l += n-1, r += n-1; l <= r; l >>= 1, r >>= 1) {
			if(l&1) sum += st[l++];
			if(!(r&1)) sum += st[r--];
		}
		return sum;
	}
} tree;

struct Node { int to, w; };

const int MAXN = 1e5 + 50;
int n, L, W;
vector<Node> adj[MAXN];
void readInput() {
	cin >> n >> L >> W;
	for(int i = 2; i <= n; i++) {
		int p, w; cin >> p >> w;
		adj[i].push_back({p, w});
		adj[p].push_back({i, w});
	}
}



// Centroid decomposition
bool vis[MAXN];
void dfsSize(int v, int p) {
	sz[v] = 1;
	for(auto c : adj[v]) if(!vis[c.to] && c.to != p) {
		dfsSize(c.to, v);
		sz[v] += sz[c.to];
	}
}

int findCtr(int v, int p, int size) {
	for(auto c : adj[v])
		if(!vis[c.to] && c.to != p && sz[c.to] > size/2) return findCtr(c.to, v, size);
	return v;
}

int dsum[MAXN], wsum[MAXN];
ll calc(int v, int p) {
	vector<pii> t;
	queue<pii> que;
	que.emplace(v, p);
	while(!que.empty()) {
		int v, p;
		tie(v, p) = que.front(); que.pop();
		t.emplace_back(dsum[v], wsum[v]);
		for(auto c : adj[v]) if(!vis[c.to] && c.to != p) {
			dsum[c.to] = dsum[v] + 1;
			wsum[c.to] = wsum[v] + c.w;
			que.emplace(c.to, v);
		}
	}
	sort(t.begin(), t.end(), [](const pii &a, const pii &b) { return a.second < b.second; });
	int p = 0;
	for(int i = (int)t.size()-1; t >= 0; t--) {
		while(p < (int)t.size() && t[p].second + t[i].second <= W)
			tree[p++].
	}
}

void decompose(int v, ll &cnt) {
	dfsSize(v, -1);
	int ctr = findCtr(v, -1, sz[v]);

	dsum[ctr] = wsum[ctr] = 0;
	cnt += calc(ctr, -1);
	for(auto c : adj[ctr]) if(!vis[c.to]) {
		dsum[c.to] = 1, wsum[c.to] = c.w;
		cnt -= calc(c.to, ctr);
	}

	vis[ctr] = true;
	for(auto c : adj[ctr])
		if(!vis[c.to]) decompose(c.to, cnt);
}
