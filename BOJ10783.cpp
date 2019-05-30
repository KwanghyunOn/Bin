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

struct Node {
	int to, weight, ri;
	Node(int t, int w) : to(t), weight(w) {}
	Node(int t, int w, int r) : to(t), weight(w), ri(r) {}
};

const int MAXN = 30050;
vector<Node> adj[2*MAXN];
int n, k;
void readInput() {
	map<Pi, int> M;
	scanf("%d%d", &n, &k);
	repp(i, 2*n) {
		int l, r, s;
		scanf("%d%d%d", &l, &r, &s);
		M[{l,r}]++;
		r += n;
		adj[l].push_back({r, s, (int)adj[r].size()});
		adj[r].push_back({l, s, (int)adj[l].size()-1});
	}
	for(auto e : M) if(e.second > 2) {
		printf("NO\n");
		exit(0);
	}
}



bool bvis[2*MAXN];
bool check(int s) {
	queue<int> que;
	que.push(s);
	bvis[s] = true;
	int vcnt = 0, ecnt = 0;
	while(!que.empty()) {
		int v = que.front();
		que.pop();
		vcnt++;
		ecnt += (int)adj[v].size();
		for(auto c : adj[v]) if(!bvis[c.to]) {
			bvis[c.to] = true;
			que.push(c.to);
		}
	}
	return 2*vcnt == ecnt;
}



bool cvis[2*MAXN], cycleFound;
void dfsCycle(int v, int pi, vector<Node> &path, vector<Node> &cyc) {
	for(int i = 0; i < (int)adj[v].size(); i++) {
		if(cycleFound) return;
		if(i == pi) continue;
		int c = adj[v][i].to;
		if(!cvis[c]) {
			cvis[c] = true;
			path.push_back({c, adj[v][i].weight});
			dfsCycle(c, adj[v][i].ri, path, cyc);
			path.pop_back();
		} else {
			cyc.push_back({c, adj[v][i].weight});
			while(!path.empty() && path.back().to != c) {
				cyc.push_back(path.back());
				path.pop_back();
			}
			cycleFound = true;
			return;
		}
	}
}



int dfsTree(int v, int p1, int p2) {
	int res = 0;
	for(auto c : adj[v]) if(c.to != p1 && c.to != p2) {
		if(c.to <= n) res += c.weight;
		else res -= c.weight;
		res += dfsTree(c.to, v, -1);
	}
	return res;
}

Pi solve(vector<Node> &cyc) {
	int offset = 0, k = (int)cyc.size();
	rep(i, k) {
		int pi = (i>0) ? i-1 : k-1;
		int ni = (i+1)%k;
		offset += dfsTree(cyc[i].to, cyc[pi].to, cyc[ni].to);
	}

	int fval = 0, rval = 0;		// forward value, reverse value
	for(auto e : cyc) {
		if(e.to <= n) fval += e.weight;
		else fval -= e.weight;
	}
	rep(i, k) {
		if(cyc[i].to <= n) rval += cyc[(i+1)%k].weight;
		else rval -= cyc[(i+1)%k].weight;
	}
	if(fval > rval) swap(fval, rval);
	return {fval + offset, rval + offset};
}



int main() {
	readInput();
	vector<int> sv;
	int low = -k, high = k;
	repp(v, 2*n) {
		if(!bvis[v]) {
			if(!check(v)) {
				printf("NO\n");
				return 0;
			}
			vector<Node> path, cyc;
			cycleFound = false;
			dfsCycle(v, -1, path, cyc);
			int f, r;
			tie(f, r) = solve(cyc);
			low += f;
			high += f;
			sv.push_back(r-f);
		}
	}
}
