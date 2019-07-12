// https://www.hackerrank.com/contests/world-codesprint-5/challenges/challenging-palindromes/problem

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

const int MAXN = 2e5 + 50;
const int LOGN = 18;

int x[MAXN], y[MAXN], cnt[MAXN];
void suffixArray(string &s, int *sa, int *rk) {
	memset(cnt, 0, sizeof cnt);
	int n = (int)s.size(), m = 255;
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

void findLCP(string &s, int *sa, int *rk, int *lcp) {
	int h = 0, n = (int)s.size();
	for(int i = 0; i < n; i++) {
		if(rk[i]) {
			int prv = sa[rk[i]-1];
			while(s[prv+h] == s[i+h]) h++;
			lcp[rk[i]] = h;
		}
		h = max(h-1, 0);
	}
}



void manacher(string &s, int *A, int *B) {
	int n = (int)s.size();
	int P = -1, R = -1;
	for(int i = 0; i < n; i++) {
		if(i <= R) A[i] = min(A[2*P-i], R-i);
		else A[i] = 0;
		while(0 <= i-A[i]-1 && i+A[i]+1 < n && s[i-A[i]-1] == s[i+A[i]+1]) A[i]++;
		if(R < i+A[i]) R = i+A[i], P = i;
	}

	P = -1, R = -1;
	for(int i = 0; i < n; i++) {
		if(i <= R) B[i] = min(B[2*P-i-1], R-i+1);
		else B[i] = 0;
		while(0 <= i-B[i]-1 && i+B[i] < n && s[i-B[i]-1] == s[i+B[i]]) B[i]++;
		if(R < i+B[i]-1) R = i+B[i]-1, P = i;
	}
}



pii sp[MAXN][LOGN];
int log_2[MAXN];
void buildSparseTable(int n, pii *a) {
	for(int i = 0; i < n; i++)
		sp[i][0] = a[i];
	for(int x = 1; x < LOGN; x++)
		for(int i = 0; i + (1<<x) <= n; i++)
			sp[i][x] = max(sp[i][x-1], sp[i+(1<<(x-1))][x-1]);

	for(int x = 0; x < LOGN; x++)
		for(int i = (1<<x); i < min(MAXN, (1<<(x+1))); i++)
			log_2[i] = x;
}

pii rangeMax(int l, int r) {
	int p = log_2[r-l+1];
	return max(sp[l][p], sp[r-(1<<p)+1][p]);
}



int sa[MAXN], rk[MAXN], lcp[MAXN];
int rodd[MAXN], reven[MAXN], maxlcp[MAXN];
pii mr[MAXN];
string maxString(string &a, string &rb) {
	manacher(rb, rodd, reven);
	int n = (int)rb.size(), lcur = n;
	for(int i = n-1; i >= 0; i--) {
		for(int j = lcur-1; j >= i-rodd[i]; j--)
			mr[j] = {i, 0};
		lcur = min(lcur, i-rodd[i]);
		for(int j = lcur-1; j >= i-reven[i]; j--)
			mr[j] = {i-1, 1};
		lcur = min(lcur, i-reven[i]);
	}
	buildSparseTable(n, mr);

	string s = a + "#" + rb;
	suffixArray(s, sa, rk);
	findLCP(s, sa, rk, lcp);

	rep(i, (int)s.size()) cout << i << ": " << s.substr(sa[i], s.size()-sa[i]) << endl;

	int m = (int)s.size(), curlcp = INF;
	for(int i = 0; i < m; i++) {
		if(sa[i] < (int)a.size()) curlcp = INF;
		else {
			curlcp = min(curlcp, lcp[i]);
			maxlcp[i] = max(maxlcp[i], curlcp);
		}
	}
	curlcp = INF;
	for(int i = m-1; i >= 0; i--) {
		if(sa[i] < (int)a.size()) curlcp = lcp[i];
		else {
			if(curlcp != INF) maxlcp[i] = max(maxlcp[i], curlcp);
			curlcp = min(curlcp, lcp[i]);
		}
	}

	rep(i, m) cout << maxlcp[i] << " ";
	cout << endl;
	cout << rangeMax(1, 3).first << endl;

	int mx = 0, L = -1;
	pii R = {-1, -1};
	for(int i = 0; i < m; i++) if(sa[i] >= (int)a.size()) {
		if(maxlcp[i] == 0) continue;
		int k = sa[i]-((int)a.size()+1);
		pii p = rangeMax(k+1, k+maxlcp[i]);
		int curlen = (p.second) ? 2*(p.first-k+1) : 2*(p.first-k)+1;
		if(curlen > mx) {
			mx = curlen;
			L = k, R = p;
		}
	}

	if(mx == 0) return "";
	string res = "";
	if(R.second) {
		string t = rb.substr(L, R.first-L+1);
		res = t;
		reverse(t.begin(), t.end());
		res += t;
		return res;
	} else {
		string t = rb.substr(L, R.first-L);
		res = t;
		res.push_back(rb[R.first]);
		reverse(t.begin(), t.end());
		res += t;
		return res;
	}
}


void solve() {
	string a, b; cin >> a >> b;	
	string ra = a, rb = b;
	reverse(ra.begin(), ra.end());
	reverse(rb.begin(), rb.end());

	cout << maxString(a, rb) << endl;
	return;

	string s1 = maxString(a, rb), s2 = maxString(b, ra);
	if(s1.size() != s2.size()) {
		if(s1.size() < s2.size()) swap(s1, s2);
		cout << s1 << endl;
	} else {
		if(s1 > s2) swap(s1, s2);
		if((int)s1.size() == 0) cout << -1 << endl;
		else cout << s1 << endl;
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
}
