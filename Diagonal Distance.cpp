#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
	
#define INF 1987654321
#define IINF 2987654321987654321
#define MOD 1000000007

const int MAXN = 5e4 + 50;
vector<int> adj[MAXN];
vector<pii> qlist;
int n, q;
void readInput() {
	scanf("%d", &n);
	rep(i, n-3) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	scanf("%d", &q);
	qlist.resize(q);
	rep(i, q) scanf("%d%d", &qlist[i].first, &qlist[i].second);
}



struct Polygon {
	int sz, depth;
	vector<int> points;
	vector<vector<int>> graph;
	vector<int> dist[2];	// dist[0]: distance from x, dist[1]: distance from y

	int x, y;				// split edge, x < y
	Polygon *l, *r;			// l: vertices between x and y;
};


const int MAXD = 28;
int val[MAXN], ri[MAXN][MAXD];
void decompose(Polygon *p) {
	int n = p->sz, d = p->depth;
	int n_third = (n-1)/3 + 1;
	vector<int> &pt = p->points;
	vector<vector<int>> &gr = p->graph;

	for(int i = 0; i < n; i++)
		ri[pt[i]][d] = i;

	// find x, y
	p->x = p->y = 0;
	for(int i = 0; i < n; i++)
		val[pt[i]] = i;

	for(int i = 0; i < n; i++) {
		int u = pt[i];
		for(auto v : gr[i]) {
			int subSize = abs(val[u] - val[v]) + 1;
			if(n_third <= subSize && subSize <= (n - n_third)) {
				p->x = min(u, v), p->y = max(u, v);
				break;
			}
		}
		if(p->x) break;
	}

	// find distance by bfs
	for(int k = 0; k < 2; k++) {
		vector<int> &dist = p->dist[k];
		dist.assign(n, INF);
		int s = k ? p->y : p->x;
		queue<int> que;
		que.push(ri[s][d]);
		dist[ri[s][d]] = 0;
		while(!que.empty()) {
			int ci = que.front();
			que.pop();
			for(auto nxt : gr[ci]) {
				int ni = ri[nxt][d];
				if(dist[ni] > dist[ci]+1)
					dist[ni] = dist[ci]+1, que.push(ni);
			}
		}
	}


	int x = p->x, y = p->y;
	p->l = new Polygon(), p->r = new Polygon();


	// initialize l
	p->l->points.push_back(x);
	p->l->graph.push_back(vector<int>());
	for(auto e : gr[ri[x][d]])
		if(x <= e && e <= y) p->l->graph.back().push_back(e);

	for(int i = ri[x][d]+1; i < ri[y][d]; i++) {
		p->l->points.push_back(pt[i]);
		p->l->graph.push_back(gr[i]);
	}

	p->l->points.push_back(y);
	p->l->graph.push_back(vector<int>());
	for(auto e : gr[ri[y][d]])
		if(x <= e && e <= y) p->l->graph.back().push_back(e);

	p->l->sz = (int)p->l->points.size();
	p->l->depth = p->depth + 1;


	// initialize r
	p->r->points.push_back(y);
	p->r->graph.push_back(vector<int>());
	for(auto e : gr[ri[y][d]])
		if(y <= e || e <= x) p->r->graph.back().push_back(e);

	for(int i = ri[y][d]+1; i != ri[x][d]; i = (i < n-1 ? i+1 : 0)) {
		p->r->points.push_back(pt[i]);
		p->r->graph.push_back(gr[i]);
	}

	p->r->points.push_back(x);
	p->r->graph.push_back(vector<int>());
	for(auto e : gr[ri[x][d]])
		if(y <= e || e <= x) p->r->graph.back().push_back(e);

	p->r->sz = (int)p->r->points.size();
	p->r->depth = p->depth + 1;


	// recursively decompose
	decompose(p->l);
	decompose(p->r);
	exit(0);
}



Polygon *root;
void preprocess() {
	root = new Polygon();
	root->sz = n;
	root->depth = 0;
	repp(v, n) root->points.push_back(v);
	repp(v, n) root->graph.push_back(adj[v]);
	decompose(root);
}




int main() {
	readInput();
	preprocess();

}
