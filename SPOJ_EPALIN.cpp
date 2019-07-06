// https://www.spoj.com/problems/EPALIN/

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

const int MAXN = 1e5 + 50;
int z[MAXN];
string s;

void calcZ() {
	int L = 0, R = 0;
	int n = (int)s.size();
	for(int i = 1; i < n; i++) {
		if(i > R) {
			L = R = i;
			while(R < n && s[R-L] == s[R]) R++;
			z[i] = R-L; R++;
		} else {
			int k = i-L;
			if(z[k] < R-i+1) z[i] = z[k];
			else {
				L = i;
				while(R < n && s[R-L] == s[R]) R++;
				z[i] = R-L; R--;
			}
		}
	}
}

void solve(string &t) {
	string rt = t;
	reverse(rt.begin(), rt.end());
	s = rt + "$" + t;
	calcZ();
	int mx = 0, n = (int)t.size();
	for(int l = 1; l <= n; l++)
		if(z[n-l] == l) mx = l;

	t += t.substr(0, n-mx);
	cout << t << endl;
}


int main() {
	string t;
	while(cin >> t) {
		solve(t);
	}
}
