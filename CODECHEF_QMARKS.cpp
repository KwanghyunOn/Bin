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

const int MAXN = 1050;
struct Node {
	bool isEnd;
	int count, dp[MAXN];
	Node *nxt[26], *f, *o;
	Node() : isEnd(false), count(0), f(NULL), o(NULL) {
		rep(i, MAXN) dp[i] = -INF;
		rep(i, 26) nxt[i] = NULL;
	}
} *root;


vector<Node*> order;
void buildTrie(vector<string> &p) {
	root = new Node();
	order.clear();

	for(int i = 0; i < (int)p.size(); i++) {
		Node *cur = root;
		for(char c : p[i]) {
			int x = c - 'a';
			if(!cur->nxt[x]) cur->nxt[x] = new Node();
			cur = cur->nxt[x];
		}
		cur->isEnd = true;
		cur->count++;
	}

	queue<Node*> que;
	order.push_back(root);
	for(int i = 0; i < 26; i++) if(root->nxt[i]) {
		root->nxt[i]->f = root;
		que.push(root->nxt[i]);
	}
	while(!que.empty()) {
		Node *q = que.front(); que.pop();
		order.push_back(q);
		if(q->isEnd) q->o = q;
		else q->o = q->f->o;
		for(int i = 0; i < 26; i++) if(q->nxt[i]) {
			Node *t = q->nxt[i];
			t->f = q->f;
			while(t->f != root && !t->f->nxt[i]) t->f = t->f->f;
			if(t->f->nxt[i]) t->f = t->f->nxt[i];
			que.push(t);
		}
	}

	for(auto t : order)
		if(t->isEnd && t->f->o) t->count += t->f->o->count;
}


void calcDP(string &s) {
	int n = (int)s.size();
	for(auto t : order) t->dp[n] = t->count;
	for(int k = n-1; k >= 0; k--) {
		if(s[k] == '?') {
			for(auto t : order) {
				for(int i = 0; i < 26; i++)
					if(t->nxt[i]) t->dp[k] = max(t->dp[k], t->nxt[i]->dp[k+1] + t->count);
			}
		} else {
			int x = s[k] - 'a';
			for(auto t : order)
				if(t->nxt[x]) t->dp[k] = t->nxt[x]->dp[k+1] + t->count;
		}

		for(auto t : order)
			if(t->f) t->dp[k] = max(t->dp[k], t->f->dp[k]);
	}
}


string str = "";
void print(Node *t, int k) {
	if(t == root) str = "";
	cout << str << ": " << t->dp[k] << endl;
	for(int i = 0; i < 26; i++) if(t->nxt[i]) {
		str.push_back((char)('a'+i));
		print(t->nxt[i], k);
		str.pop_back();
	}
}


void solve() {
	int n, m; cin >> n >> m;
	string s; cin >> s;
	vector<string> p(m);
	rep(i, m) cin >> p[i];
	
	buildTrie(p);
	calcDP(s);

	print(root, 7);

	cout << root->dp[0] << endl;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int T; cin >> T;
	while(T--) solve();
}
