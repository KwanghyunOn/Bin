// https://www.hackerrank.com/contests/world-codesprint-6/challenges/functional-palindromes

#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
 
#define INF 987654321
#define IINF 87654321987654321
#define MOD 1000000007

inline madd(ll a, ll b) { return (a+b) % MOD; }
inline mmul(ll a, ll b) { return (a*b) % MOD; }
inline msub(ll a, ll b) { return (a-b+MOD) % MOD; }
ll inverse(ll a, ll m) {
    ll m0 = m, t, q;
    ll x0 = 0, x1 = 1;
 
    if (m == 1)
      return 0;
 
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
       x1 += m0;
    return x1;
}



const int MAXN = 1e5 + 50;
int x[MAXN], y[MAXN], cnt[MAXN];
int sa[MAXN], rk[MAXN], lcp[MAXN];
void suffixArray(int n, char *s) {
	memset(cnt, 0, sizeof cnt);
	int m = 255;
	for(int i = 0; i < n; i++) cnt[x[i] = s[i]]++;
	for(int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
	for(int i = 0; i < n; i++) sa[--cnt[x[i]]] = i;
	for(int len = 1, sz = 1; sz < n; len <<= 1, m = sz) {
		int p = 0;
		for(int i = n-len; i < n; i++) y[p++] = i;
		for(int i = 0; i < n; i++) if(sa[i] >= len) y[p++] = sa[i]-len;
		for(int i = 1; i <= m; i++) cnt[i] = 0;
		for(int i = 0; i < n; i++) cnt[x[i]]++;
		for(int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
		for(int i = n-1; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];
		swap(x, y), sz = 1, x[sa[0]] = 1;
		for(int i = 1; i < n; i++) {
			if(y[sa[i-1]] != y[sa[i]] || y[sa[i-1]+len] != y[sa[i]+len]) sz++;
			x[sa[i]] = sz;
		}
	}
	for(int i = 0; i < n; i++) rk[sa[i]] = i;
}

void findLCP(int n, char *s) {
	int h = 0;
	for(int i = 0; i < n; i++) {
		if(rk[i]) {
			int prv = sa[rk[i]-1];
			while(s[prv+h] == s[i+h]) h++;
			lcp[rk[i]] = h;
		}
		h = max(h-1, 0);
	}
}

const int LOGN = 18;
int sp[MAXN][LOGN], log_2[MAXN];
void buildSparseTable(int n, int *a) {
	for(int i = 0; i < n; i++)
		sp[i][0] = a[i];
	for(int x = 1; x < LOGN; x++)
		for(int i = 0; i+(1<<x) <= n; i++)
			sp[i][x] = min(sp[i][x-1], sp[i+(1<<(x-1))][x-1]);

	for(int x = 0; x < LOGN; x++)
		for(int i = (1<<x); i < min(MAXN, 1<<(x+1)); i++)
			log_2[i] = x;
}

inline int rangeMin(int l, int r) {
	int p = log_2[r-l+1];
	return min(sp[l][p], sp[r-(1<<p)+1][p]);
}

inline int rangeLCP(int i, int j, int n) {
	if(i == j) return n-sa[i];
	if(i > j) swap(i, j);
	return rangeMin(i+1, j);
}



struct Node {
	int len, l, r, count;
	Node *suf, *nxt[26];
	Node() : len(0), l(0), r(0), count(0), suf(NULL) { for(int i = 0; i < 26; i++) nxt[i] = NULL; }
} *iroot, *root;

char s[MAXN];
Node *maxSuf;
void addChar(int p) {
	int x = s[p] - 'a';
	Node *cur = maxSuf;
	while(true) {
		if(p-(cur->len)-1 >= 0 && s[p] == s[p-(cur->len)-1])
			break;
		cur = cur->suf;
	}
	if(cur->nxt[x]) {
		cur->nxt[x]->count++;
		maxSuf = cur->nxt[x];
		return;
	}

	cur->nxt[x] = new Node();
	Node *t = cur->nxt[x];
	t->len = cur->len + 2;
	t->l = p - t->len + 1;
	t->r = p;
	t->count = 1;
	maxSuf = t;

	if(cur == iroot) {
		t->suf = root;
		return;
	}

	cur = cur->suf;
	while(true) {
		if(p-(cur->len)-1 >= 0 && s[p] == s[p-(cur->len)-1])
			break;
		cur = cur->suf;
	}
	t->suf = cur->nxt[x];
}

vector<Node*> order;
void buildPalTree() {
	iroot = new Node();
	root = new Node();
	iroot->suf = root->suf = iroot;
	iroot->len = -1;
	root->len = 0;
	maxSuf = root;

	int n = strlen(s);
	for(int i = 0; i < n; i++)
		addChar(i);

	queue<Node*> que;
	que.push(iroot);
	que.push(root);
	while(!que.empty()) {
		Node *q = que.front(); que.pop();
		for(int i = 0; i < 26; i++) if(q->nxt[i]) {
			order.push_back(q->nxt[i]);
			que.push(q->nxt[i]);
		}
	}
	reverse(order.begin(), order.end());
	for(auto t : order)
		t->suf->count += t->count;
}



ll hval[MAXN], pinv[MAXN];
const ll P = 100001;
void calcHash(int n) {
	ll ppow = 1;
	for(int i = n-1; i >= 0; i--) {
		hval[i] = madd(hval[i+1], mmul((ll)s[i], ppow));
		ppow = mmul(ppow, P);
	}

	pinv[0] = 1, pinv[1] = inverse(P, MOD);
	for(int i = 2; i <= n; i++)
		pinv[i] = mmul(pinv[i-1], pinv[1]);
}

inline ll hashValue(int l, int r, int n) {
	return mmul(msub(hval[l], hval[r+1]), pinv[n-1-r]);	
}



typedef pair<pii, int> piii;
int main() {
	int n, q; scanf("%d%d%s", &n, &q, s);
	buildPalTree();
	suffixArray(n, s);
	findLCP(n, s);
	buildSparseTable(n, lcp);

	vector<piii> v;
	for(auto t : order)
		v.push_back({{t->l, t->r}, t->count});
	sort(v.begin(), v.end(), [n](const piii &a, const piii &b) {
		int la = a.first.second - a.first.first + 1, lb = b.first.second - b.first.first + 1;
		if(min(la, lb) <= rangeLCP(rk[a.first.first], rk[b.first.first], n)) return la < lb;
		else return rk[a.first.first] < rk[b.first.first];
	});
	int m = (int)v.size();
	vector<ll> c(m);
	rep(i, m) c[i] = v[i].second;
	for(int i = 1; i < m; i++) c[i] += c[i-1];

	/*
	for(auto e : v) {
		for(int i = e.first.first; i <= e.first.second; i++) printf("%c", s[i]);
		printf(": %d\n", e.second);
	}
	return 0;
	*/

	calcHash(n);
	while(q--) {
		ll k; scanf("%lld", &k);
		if(k > c[m-1]) printf("-1\n");
		else {
			int i = lower_bound(c.begin(), c.end(), k) - c.begin();
			printf("%lld\n", hashValue(v[i].first.first, v[i].first.second, n));
		}
	}
}
