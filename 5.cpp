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

const int MAXN = 5e5 + 50;
pii p[MAXN], hull[MAXN];
int sz = 0;

inline bool check(pii a, pii b) {
	return a.first < b.first && a.second < b.second;
}

inline int dist(pii a, pii b) {
	return max(abs(a.first - b.first), abs(a.second - b.second));
}

void solve() {
	sz = 0;
	int d, n; scanf("%d%d", &d, &n);
	repp(i, n) scanf("%d%d", &p[i].first, &p[i].second);
	sort(p+1, p+n+1, greater<pii>());

	ll sum = 0;
	for(int i = 1; i <= n; i++) {
		int low = 1, high = sz, res = -1;
		while(low <= high) {
			int mid = (low + high) / 2;
			if(hull[mid].first - hull[mid].second > p[i].first - p[i].second) {
				res = mid;
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		}

		int t = min(d-p[i].first, d-p[i].second);
		if(res == -1) {
			if(sz && check(p[i], hull[1])) t = min(t, dist(p[i], hull[1]));
		} else {
			if(check(p[i], hull[res])) t = min(t, dist(p[i], hull[res]));
			if(res+1 <= sz && check(p[i], hull[res+1])) t = min(t, dist(p[i], hull[res+1]));
		}

		printf("(%d,%d): %d\n", p[i].first, p[i].second, t);
		sum += t;

		while(sz && p[i].second <= hull[sz].second) sz--;
		hull[++sz] = p[i];
	}
	printf("%lld\n", sum);
}

int main() {
	int T; scanf("%d", &T);
	repp(tnum, T) {
		printf("Case #%d\n", tnum);
		solve();
	}
}
