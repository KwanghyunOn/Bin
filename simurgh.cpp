#include <bits/stdc++.h>
#include "simurgh.h"

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)

#define INF 987654321
#define IINF 2987654321987654321
#define MOD 1000000007

struct Edge {
	int to, id;
};

const int MAXN = 505;
vector<Edge> adj[MAXN], tree[MAXN];

int num[MAXN], cur;
Edge pa[MAXN];
pii low[MAXN];
void dfs(int v, int p) {
	num[v] = ++cur;
	low[v] = {num[v], -1};
	for(auto c : adj[v]) if(c.to != p) {
		if(num[c.to]) low[v] = min(low[v], {num[c.to], c.id});
		else {
			pa[c.to] = {v, c.id};
			tree[v].push_back(c);
			tree[c.to].push_back(pa[c.to]);
			dfs(c.to, v);
			low[v] = min(low[v], low[c.to]);
		}
	}
}



int treeVal, royal[MAXN*MAXN], val[MAXN];
void findRoyalInTree(int n, vector<int> &_u, vector<int> &_v) {
	vector<int> r;
	for(int v = 1; v < n; v++)
		r.push_back(pa[v].id);
	treeVal = count_common_roads(r);

	for(int v = 1; v < n; v++) {
		if(royal[pa[v].id] != -1) continue;

		if(low[v].second == -1) {
			royal[pa[v].id] = 1;
			continue;
		}
		
		int newEdge = low[v].second;
		r.push_back(newEdge);
		int x = _u[newEdge], y = _v[newEdge];	// x-y is back-edge
		if(num[x] > num[y]) swap(x, y);		// x is ancestor

		int t = y;
		while(t != x) {
			if(royal[pa[t].id] != -1) {
				int ei = pa[t].id;
				r.erase(find(r.begin(), r.end(), ei));
				royal[newEdge] = count_common_roads(r) - (treeVal - royal[ei]);
				r.push_back(ei);
				break;
			}
			t = pa[t].to;
		}

		if(royal[newEdge] != -1) {
			r.erase(find(r.begin(), r.end(), pa[v].id));
			royal[pa[v].id] = treeVal - (count_common_roads(r) - royal[newEdge]);
			r.push_back(pa[v].id);
		} else {
			int t = y, mx = treeVal;
			while(t != x) {
				int ei = pa[t].id;
				r.erase(find(r.begin(), r.end(), ei));
				val[t] = count_common_roads(r);
				r.push_back(ei);

				mx = max(mx, val[t]);
				t = pa[t].to;
			}

			t = y;
			while(t != x) {
				royal[pa[t].id] = mx - val[t];
				t = pa[t].to;
			}
		}

		r.erase(find(r.begin(), r.end(), newEdge));
	}
}



bool vis[MAXN];
void dfsTree(int v, int p) {
	vis[v] = true;
	for(auto c : tree[v]) if(!vis[c.to]) {
		pa[c.to] = {v, c.id};
		dfsTree(c.to, v);
	}
}

void solve(int n, int r) {
	memset(vis, 0, sizeof vis);
	dfsTree(r, -1);
	vector<Edge> ev;
	for(auto c : adj[r])
		if(royal[c.id] == -1) ev.push_back(c);

	int start = 0, sz = (int)ev.size();
	while(start < sz) {
		int low = start, high = sz-1, res = -1;
		while(low <= high) {
			memset(vis, 0, sizeof vis);
			int mid = (low + high) / 2, curVal = treeVal;
			vector<int> q;
			for(int i = 0; i <= mid; i++) {
				q.push_back(ev[i].id);
				vis[ev[i].to] = true;
				curVal -= royal[pa[ev[i].to].id];
			}
			for(int i = 0; i < n; i++)
				if(i != r && !vis[i]) q.push_back(pa[i].id);

			if(count_common_roads(q) > curVal) {
				res = mid;
				high = mid-1;
			} else {
				low = mid+1;
			}
		}

		if(res == -1) break;
		royal[ev[res].id] = 1;
		start = res + 1;
	}
}



vector<int> find_roads(int n, vector<int> u, vector<int> v) {
	memset(royal, -1, sizeof royal);

	// make adjacent list
	int m = (int)u.size();
	for(int i = 0; i < m; i++) {
		adj[u[i]].push_back({v[i], i});
		adj[v[i]].push_back({u[i], i});
	}

	// find dfs tree
	dfs(0, -1);

	// find royal road in dfs tree
	findRoyalInTree(n, u, v);

	// find every royal roads
	for(int root = 1; root <= n; root++)
		solve(n, root);

	vector<int> rv;
	for(int i = 0; i < m; i++)
		if(royal[i] == 1) rv.push_back(i);
	return rv;
}