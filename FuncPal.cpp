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

const int MAXN = 1e5 + 50;
int x[MAXN], y[MAXN], cnt[MAXN];
void suffixArray(int n, char *s, int *sa, int *rk) {
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
		for(int i = 0; i < n; i++) sa[--cnt[x[y[i]]]] = y[i];
		swap(x, y), sz = 1, x[sa[0]] = 1;
		for(int i = 1; i < n; i++) {
			if(y[sa[i-1]] != y[sa[i]] || y[sa[i-1]+len] != y[sa[i]+len]) sz++;
			x[sa[i]] = sz;
		}
	}
	for(int i = 0; i < n; i++) rk[sa[i]] = i;
}

void findLCP(int n, char *s, int *sa, int *rk, int *lcp) {
	int h = 0;
	for(int i = 0; i < n; i++) {
		if(rk[i]) {
			int prv = sa[rk[i]-1];
			while(s[prv+h] == s[i+h]) h++;
			lcp[i] = h;
		}
		h = max(h-1, 0);
	}
}

const int LOGN = 



struct Node {
	int len, l, r;
	Node *suf, *nxt[26];
	Node() : len(0), l(0), r(0), suf(NULL) { for(int i = 0; i < 26; i++) nxt[i] = NULL; }
} *iroot, *root;

char s[MAXN];
Node *maxSuf;
void addChar(int p) {
	int x = s[p] - 'a';
	Node *cur = maxSuf;
	while(true) {
		if(p-cur->len-1 >= 0 && s[p] == s[p-cur->len-1])
			break;
		cur = cur->suf;
	}
	if(cur->nxt[x]) {
		maxSuf = cur->nxt[x];
		return;
	}

	cur->nxt[x] = new Node();
	Node *t = cur->nxt[x];
	t->len = cur->len + 2;
	t->l = p - t->len + 1;
	t->r = p;
	if(cur == iroot) {
		t->suf = root;
		maxSuf = t;
		return;
	}

	cur = cur->suf;
	while(true) {
		if(p-cur->len-1 >= 0 && s[p] == s[p-cur->len-1])
			break;
		cur = cur->suf;
	}
	t->suf = cur->nxt[x];
	maxSuf = t;
}

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
}



map<Node*, string> M;
void dfs(Node *t, string &s) {
	M[t] = s;
	rep(i, 26) if(t->nxt[i]) {
		s.push_back((char)('a'+i));
		dfs(t->nxt[i], s);
		s.pop_back();
	}
}


int sa[MAXN], rk[MAXN], lcp[MAXN];
int main() {
	int n, q; scanf("%d%d%s", &n, &q, s);
	buildPalTree();
	suffixArray(n, s, sa, rk);
	findLCP(n, s, sa, rk, lcp);
	
	vector<pii> v;
	queue<Node*> que;
	que.push(iroot);
	que.push(root);
	while(!que.empty()) {
		Node *q = que.front(); que.pop();
		for(int i = 0; i < n; i++) if(q->nxt[i]) {
			v.push_back({q->nxt[i]->l, q->nxt[i]->r});
			que.push(q->nxt[i]);
		}
	}

	sort(v.begin(), v.end(), [](const pii &a, const pii &b) {
		int la = a.second - a.first + 1, lb = b.second - b.first + 1;

	});
}
