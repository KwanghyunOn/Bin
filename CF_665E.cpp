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

struct Node {
	int mi;		// minimum index
	Node *nxt[2];
	Node() : mi(INF) { nxt[0] = nxt[1] = NULL; }
} *root;

const int LOGN = 31;
void addToTrie(int m, int id) {
	Node *cur = root;
	for(int i = LOGN-1; i >= 0; i--) {
		int x = (m >> i) & 1;
		if(!cur->nxt[x]) cur->nxt[x] = new Node();
		cur = cur->nxt[x];
		cur->mi = id;
	}
}

const int MAXN = 1e6 + 50;
int f[MAXN], a[MAXN], flag[LOGN];
int main() {
	int n, k; scanf("%d%d", &n, &k);
	for(int i = 0; i < LOGN; i++)
		flag[i] = (k >> i) & 1;
	repp(i, n) scanf("%d", &a[i]);
	addToTrie(a[n]);
	for(int i = n-1; i >= 1; i--) {
		int t = k ^ a[i];

	}
}
