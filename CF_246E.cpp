#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> Pi;
typedef pair<ll, ll> Pll;
 
#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
 
#define INF 987654321
#define IINF 2987654321987654321
#define MOD 1000000007

const int MAXN = 1e5 + 50;
vector<int> adj[MAXN];
string s[MAXN];
int n;
void readInput() {
	cin >> n;
	repp(v, n) {
		string s;
		cin >> s[v] >> pa[v][0];
		adj[pa[v][0]].push_back(v);
	}
}

struct Query { int d, id; };
vector<Query> qlist[MAXN];
int q;
void readQuery() {
	cin >> q;
	repp(i, q) {
		int v, d; cin >> v >> d;
		qlist[v].push_back({d, i});
	}
}


int sz[MAXN], depth[MAXN];
int tin[MAXN], tout[MAXN], vin[2*MAXN], CUR_TIME;
void preprocess(int v) {
	tin[v] = ++CUR_TIME;
	vin[tin[v]] = v;
	sz[v] = 1;
	for(auto c : adj[v]) {
		depth[c] = depth[v] + 1;
		preprocess(c);
		sz[v] += sz[c];
	}
	tout[v] = ++CUR_TIME;
}


map<string, int> M[MAXN];
void dfs(int v, bool keep) {
	int big = -1;
	for(auto c : adj[v])
		if(big == -1 || sz[c] > sz[big]) big = c;
	for(auto c : adj[v])
		if(c != big) dfs(c, false);
	
	if(big != -1) dfs(big, true);
	for(auto c : adj[v]) if(c != big) {
		for(int t = tin[c]; t < tout[c]; t++)
			if(vin[t]) 
	}
}
