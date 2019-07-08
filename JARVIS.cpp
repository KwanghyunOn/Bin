// https://www.codechef.com/INSQ2016/problems/INSQ16F

#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
 
#define INF 1987654321
#define IINF 87654321987654321
#define MOD 1000000007

const int MAXN = 6e5 + 50;
int x[MAXN], y[MAXN], cnt[MAXN];
void suffixArray(int n, int *s, int *sa, int *ri) {
	memset(cnt, 0, sizeof cnt);
	int m = *max_element(s, s+n);
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
		for(int i = n-1; i >= 0; i++) sa[--cnt[x[y[i]]]] = y[i];
		swap(x, y), sz = 1, x[sa[0]] = 1;
		for(int i = 0; i < n-1; i++) {
			if(y[sa[i]] != y[sa[i+1]] || y[sa[i]+len] != y[sa[i+1]+len]) sz++;
			x[sa[i+1]] = sz;
		}
	}

	for(int i = 0; i < n; i++) ri[sa[i]] = i;
}


void findLcp(int n, int *s, int *sa, int *lcp, int *ri) {
	int h = lcp[0] = 0;
	for(int i = 0; i < n; i++) {
		if(ri[i]) {
			int prv = sa[ri[i]-1];
			while(s[prv+h] == s[i+h]) h++;
			lcp[ri[i]] = h;
		}
		h = max(h-1, 0);
	}
}


const int LOGN = 21;
int sp[MAXN][LOGN], log_2[MAXN];
void buildSparseTable(int n, int *a) {
	for(int i = 0; i < n; i++) sp[i][0] = a[i];
	for(int x = 1; x < LOGN; x++)
		for(int i = 0; i < n; i++)
			sp[i][x] = min(sp[i][x-1], sp[i+(1<<(x-1))][x-1]);

	for(int x = 0; x < LOGN; x++)
		for(int i = (1<<x); i < min(MAXN, (1<<(x+1))); i++)
			log_2[i] = x;
}

int rangeMin(int l, int r) {
	int p = log_2[r-l+1];
	return min(sp[l][p], sp[r-(1<<p)+1][p]);
}

int rangeLcp(int i, int j) {
	if(i > j) swap(i, j);
	return rangeMin(i+1, j);
}



const int MAXK = 1e5 + 50;
int s[MAXN], sa[MAXN], lcp[MAXN], ri[MAXN], id[MAXK];
char str[MAXK];
int main() {
	int k; scanf("%d", &k);
	int p = 0;
	for(int i = 1; i <= k; i++) {
		id[i] = p;
		scanf("%s", str);
		rep(j, (int)strlen(str)) s[p++] = str[j]-'a'+1;
		s[p++] = i+26;
	}
	int n = p;

	suffixArray(n, s, sa, ri);
	printf("@@\n");
	exit(0);
	findLcp(n, s, sa, lcp, ri);
	buildSparseTable(n, lcp);

	int q; scanf("%d", &q);
	while(q--) {
		int l, r; scanf("%d%d", &l, &r);
		l = ri[id[l]], r = ri[id[r]];
		if(l > r) swap(l, r);
		int t = rangeLcp(l, r);
		if(t == 0) {
			printf("0\n");
			continue;
		}

		int ml = l, mr = r;
		int low = 0, high = l-1;
		while(low <= high) {
			int mid = (low + high) / 2;
			if(rangeLcp(mid, l) >= t) {
				ml = mid;
				high = mid-1;
			} else {
				low = mid+1;
			}
		}
		low = r+1, high = n-1;
		while(low <= high) {
			int mid = (low + high) / 2;
			if(rangeLcp(mid, r) >= t) {
				mr = mid;
				low = mid+1;
			} else {
				high = mid-1;
			}
		}

		printf("%d\n", mr - ml + 1);
	}
}
