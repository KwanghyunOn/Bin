#include <bits/stdc++.h>
//#include "simurgh.h"

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)

#define INF 987654321
#define IINF 2987654321987654321
#define MOD 1000000007

std::vector<int> find_roads(int n, std::vector<int> u, std::vector<int> v);
int count_common_roads(const std::vector<int>& r);

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

int treeVal, royal[MAXN*MAXN];
void findRoyal(int n, vector<int> &u, vector<int> &v) {
	vector<int> r;
	for(int v = 1; v < n; v++)
		r.push_back(pa[v].id);
	treeVal = count_common_roads(r);

	for(int v = 1; v < n; v++) {
		if(low[v].second == -1) {
			royal[pa[v].id] = 1;
			continue;
		}
		
		int newEdge = low[v].second;
		r.push_back(newEdge);

		int x = u[newEdge], y = v[newEdge];	// x-y is back-edge
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
			
		}
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


	return vector<int>();
}



int main() {
	find_roads(4, {0, 0, 0, 1, 1, 2}, {1, 2, 3, 2, 3, 3});
	for(int i = 0; i < 4; i++) {
		printf("%d: ", i);
		for(auto e : tree[i]) printf("%d ", e.to);
		printf("\n");
	}
}
