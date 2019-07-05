#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
 
#define INF 87654321
#define IINF 87654321987654321
#define MOD 1000000007

typedef pair<ll, int> pli;
struct SegmentTree {
	int n;
	vector<pli> st;
	void buildTree(vector<ll> val) {
		int sz = (int)val.size();
		n = 1;
		while(n < sz) n <<= 1;
		st.assign(2*n, {-1, 0});

		rep(i, sz) st[n+i] = {val[i], -(i+1)};
		for(int i = n-1; i >= 1; i--)
			st[i] = max(st[2*i], st[2*i+1]);
	}

	int argmax(int l, int r) {
		pli res = {-1, 0};
		for(l += n-1, r += n-1; l <= r; l >>= 1, r >>= 1) {
			if(l&1) res = max(res, st[l++]);
			if(!(r&1)) res = max(res, st[r--]);
		}
		return -res.second;
	}
};



struct Node {
	ll a, b;		// y = ax + b
	int l, r;
	ll f(int x) {
		return a*x + b;
	}
	void print() {
		printf("%lldx + %lld, [%d, %d]\n", a, b, l, r);
	}
};

const int MAXN = 75e4 + 50;
Node tree[4*MAXN], lazy[4*MAXN];
int n, q;
void pushDown(int id) {
	if(lazy[id].l) {
		tree[2*id] = tree[2*id+1] = lazy[id];
		lazy[2*id] = lazy[2*id+1] = lazy[id];
	} else {
		tree[2*id].b += lazy[id].b;
		tree[2*id+1].b += lazy[id].b;
		lazy[2*id].b += lazy[id].b;
		lazy[2*id+1].b += lazy[id].b;
	}
	lazy[id] = {0, 0, 0, 0};
}

void rangeUpdate(int s, int e, Node t, int l = 1, int r = n, int id = 1) {
	if(e < l || r < s) return;
	if(s <= l && r <= e) {
		tree[id] = lazy[id] = t;
		return;
	}
	int mid = (l + r) / 2;
	pushDown(id);
	rangeUpdate(s, e, t, l, mid, 2*id);
	rangeUpdate(s, e, t, mid+1, r, 2*id+1);
}

void rangeAdd(int s, int e, ll val, int l = 1, int r = n, int id = 1) {
	if(e < l || r < s) return;
	if(s <= l && r <= e) {
		tree[id].b += val;
		lazy[id].b += val;
		return;
	}
	int mid = (l + r) / 2;
	pushDown(id);
	rangeAdd(s, e, val, l, mid, 2*id);
	rangeAdd(s, e, val, mid+1, r, 2*id+1);
}

Node findNode(int x) {
	int l = 1, r = n, id = 1;
	while(l < r) {
		int mid = (l + r) / 2;
		pushDown(id);
		if(x <= mid) {
			r = mid;
			id = 2*id;
		} else {
			l = mid+1;
			id = 2*id+1;
		}
	}
	return tree[id];
}




ll h[MAXN], c[MAXN];
int li[MAXN], ri[MAXN];
vector<int> ql[MAXN];

void dfs(int s, int e, SegmentTree &htree) {
	if(s == e) {
		rangeUpdate(s, e, {0, h[s], s, e});
		for(int i : ql[s]) {
			int mi = htree.argmax(li[i], ri[i]);
			c[i] = min(c[i], (mi-li[i]+1)*h[mi] + findNode(ri[i]).f(ri[i]));
		}
		return;
	}

	int v = htree.argmax(s, e);
	if(s < v) dfs(s, v-1, htree);
	if(v < e) dfs(v+1, e, htree);

	ll lval = (s < v) ? findNode(v-1).f(v-1) : 0;
	Node lnode = {h[v], (lval + (-v+1)*h[v]), -1, -1};
	rangeAdd(v+1, e, (v-s+1) * h[v]);

	if(v < e) {
		bool flag = false;
		int cur = v+1;
		while(cur <= e) {
			Node cnode = findNode(cur);
			if(cnode.f(cnode.r) < lnode.f(cnode.r)) {
				int meetX = (lnode.a != cnode.a) ? (cnode.b - lnode.b) / (lnode.a - cnode.a) : cnode.r;
				lnode.l = v, lnode.r = meetX;
				rangeUpdate(v, meetX, lnode);
				rangeUpdate(meetX+1, cnode.r, {cnode.a, cnode.b, meetX+1, cnode.r});
				flag = true;
				break;
			}
			cur = cnode.r + 1;
		}
		if(!flag) {
			lnode.l = v, lnode.r = e;
			rangeUpdate(v, e, lnode);
		}
	} else {
		lnode.l = lnode.r = v;
		rangeUpdate(v, v, lnode);
	}
	

	for(int i : ql[v]) {
		int mi = htree.argmax(li[i], ri[i]);
		c[i] = min(c[i], (mi-li[i]+1)*h[mi] + findNode(ri[i]).f(ri[i]));
	}
}



void solve() {
	SegmentTree htree;
	htree.buildTree(vector<ll>(h+1, h+n+1));
	repp(i, q) {
		int mi = htree.argmax(li[i], ri[i]);
		if(mi < ri[i]) ql[htree.argmax(mi+1, ri[i])].push_back(i);
	}
	dfs(1, n, htree);
	repp(i, n) ql[i].clear();
}



vector<ll> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
	n = (int)H.size(), q = (int)L.size();
	fill(c, c+MAXN, IINF);
	rep(i, q) if(L[i] == R[i]) c[i+1] = H[L[i]];


	rep(i, q) L[i]++, R[i]++;	// make 1-index

	// pivot is right of max
	repp(i, n) h[i] = H[i-1];
	repp(i, q) {
		li[i] = L[i-1];
		ri[i] = R[i-1];
	}
	solve();

	// pivot is left of max
	repp(i, n) h[i] = H[n-i];
	repp(i, q) {
		ri[i] = (n+1)-L[i-1];
		li[i] = (n+1)-R[i-1];
	}
	solve();

	return vector<ll>(c+1, c+q+1);
}



int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	vector<int> H(n), L(q), R(q);
	rep(i, n) scanf("%d", &H[i]);
	rep(i, q) scanf("%d%d", &L[i], &R[i]);
	for(auto e : minimum_costs(H, L, R))
		printf("%lld\n", e);
}
