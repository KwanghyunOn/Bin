#include <bits/stdc++.h>
#include "werewolf.h"

using namespace std;
 
typedef long long ll;
typedef pair<int, int> Pi;
typedef pair<ll, ll> Pll;
 
#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
 
#define INF 87654321
#define IINF 87654321987654321
#define MOD 1000000007


const int MAXN = 2e5 + 50;
int par[MAXN];
int find(int x) {
	return (par[x] == x) ? x : (par[x] = find(par[x]));
}

void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	par[x] = y;
}



vector<int> al[MAXN], ar[MAXN];
int n;
struct Node {
	Node* l, r, p;
	int id, li, ri;
} tx[MAXN], ty[MAXN], f[MAXN];

void buildTree() {
	rep(i, n) par[i] = i;
	for(int i = n-1; i >= 0; i--) {
		for(int j : ar[i]) {
			int fi = find(i), fj = find(j);
			if(fi == fj) continue;
			
		}
	}
}

vector<int> check_validity(int N, vector<int> X, vector<int> Y,
								vector<int> S, vector<int> E,
								vector<int> L, vector<int> R) {
	n = N;
	int m = (int)X.size();
	rep(i, m) {
		if(X[i] < Y[i]) {
			al[Y[i]].push_back(X[i]);
			ar[X[i]].push_back(Y[i]);
		} else {
			al[X[i]].push_back(Y[i]);
			ar[Y[i]].push_back(X[i]);
		}
	}

	buildTree();
	vector<int> res;
	int q = (int)S.size();
	rep(i, q) res.push_back((query(S[i], E[i], L[i], R[i])) ? 1 : 0);
	return res;
}
