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

long long ask(const std::vector<int> &w);
void answer(int s, int t);

struct Node {
	int to, id;
};

const int MAXN = 9e4 + 50;
vector<Node> adj[MAXN];

void bfs(int s, vector<int> &d) {
	fill(d.begin(), d.end(), -1);
	d[s] = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()) {
		int v = que.front();
		que.pop();
		for(auto c : adj[v]) if(d[c.to] == -1) {
			d[c.to] = d[v] + 1;
			que.push(c.to);
		}
	}
}

void find_pair(int n, vector<int> U, vector<int> V, int A, int B) {
	int m = (int)U.size();
	for(int i = 0; i < m; i++) {
		adj[U[i]].push_back({V[i], i});
		adj[V[i]].push_back({U[i], i});
	}

	vector<int> w(m, 0);
	ll d = ask(w) / A;		// distance from S to T


	// find edge in path S to T
	int low = 0, high = m-1, x;
	while(low <= high) {
		int mid = (low + high) / 2;
		rep(i, m) w[i] = (i <= mid) ? 1 : 0;
		if(ask(w) > d*A) {
			x = mid;
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}


	// dijkstra from each end of edge x
	vector<int> du(n), dv(n);
	bfs(U[x], du);
	bfs(V[x], dv);

	vector<int> utree, vtree;
	rep(i, n) {
		if(du[i] == dv[i] - 1) utree.push_back(i);
		if(dv[i] == du[i] - 1) vtree.push_back(i);
	}
	sort(utree.begin(), utree.end(), [du](int a, int b) { return du[a] < du[b]; });
	sort(vtree.begin(), vtree.end(), [dv](int a, int b) { return dv[a] < dv[b]; });


	// find S
	vector<int> c(n, 0);
	low = 0, high = (int)utree.size()-1;
	int S;
	while(low <= high) {
		int mid = (low + high) / 2;
		for(int i = 0; i < (int)utree.size(); i++)
			c[utree[i]] = (i <= mid) ? 1 : 2;
		fill(w.begin(), w.end(), 0);
		rep(i, m) if(c[U[i]] + c[V[i]] == 3) w[i] = 1;
		if(ask(w) == d*A) {
			S = utree[mid];
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}

	// find T
	fill(c.begin(), c.end(), 0);
	low = 0, high = (int)vtree.size()-1;
	int T;
	while(low <= high) {
		int mid = (low + high) / 2;
		for(int i = 0; i < (int)vtree.size(); i++)
			c[vtree[i]] = (i <= mid) ? 1 : 2;
		fill(w.begin(), w.end(), 0);
		rep(i, m) if(c[U[i]] + c[V[i]] == 3) w[i] = 1;
		if(ask(w) == d*A) {
			T = vtree[mid];
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}

	answer(S, T);
}


typedef pair<ll, int> pli;
int n, m, a, b, s, t;
vector<Node> graph[MAXN];
ll dist[MAXN];
long long ask(const vector<int> &w) {
	rep(i, n) dist[i] = IINF;
	priority_queue<pli, vector<pli>, greater<pli>> pq;
	dist[s] = 0;
	pq.push({dist[s], s});
	while(!pq.empty()) {
		ll d; int x;
		tie(d, x) = pq.top();
		pq.pop();
		if(dist[x] < d) continue;
		for(auto c : adj[x]) if(dist[c.to] > dist[x] + (w[c.id] ? b : a)) {
			dist[c.to] = dist[x] + (w[c.id] ? b : a);
			pq.push({dist[c.to], c.to});
		}
	}
	return dist[t];
}

void answer(int s_, int t_) {
	if((s == s_ && t == t_) || (s == t_ && t == s_))
		cout << "CORRECT!" << endl;
	else
		cout << "WRONG!" << endl;
}

int main() {
	scanf("%d%d%d%d%d%d", &n, &m, &a, &b, &s, &t);
	vector<int> U(m), V(m);
	rep(i, m) scanf("%d%d", &U[i], &V[i]);
	rep(i, m) {
		graph[U[i]].push_back({V[i], i});
		graph[V[i]].push_back({U[i], i});
	}
	find_pair(n, U, V, a, b);
}
