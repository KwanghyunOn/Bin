#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> Pi;
typedef pair<ll, ll> Pll;
 
#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
 
#define INF 87654321
#define IINF 87654321987654321
#define MOD 1000000007
// 1-index
#define L(x) ((x)<<1)
#define R(x) (((x)<<1)+1)

const int MAXN = 2e5 + 50;
struct Line {
	ll t, val, lx, rx;
} l[MAXN];

ll L;
int n, k;

bool check(ll maxY) {
	ll cx = 0, nx = -1;
	int cnt = 0;
	repp(i, n) {
		Line cl = l[i];
		if(cl.t == 1) {
			cl.lx = max(cl.lx, cl.val-maxY);
			if(cl.lx > cl.rx) continue;
			if(2*cl.lx <= cl.val + cx) {
				nx = cl.val;
				if(nx >= L) {
					cnt++;
					cx = nx;
					break;
				}
			} else if(nx == -1) {
				return false;
			} else {
				cx = nx;
				nx = -1;
				cnt++;
			}
		} else {
			cl.rx = min(cl.rx, cl.val+maxY);
			if(cl.lx > cl.rx) continue;
			if(cl.val <= cx) {
				nx = 2*cl.rx - cl.val;
				if(nx >= L) {
					cnt++;
					cx = nx;
					break;
				}
			} else if(nx == -1) {
				return false;
			} else {
				cx = nx;
				nx = -1;
				cnt++;
			}
		}
	}

	return cx >= L && cnt <= k;
}

void solve() {
	scanf("%lld%d%d", &L, &n, &k);
	L *= 2;
	ll px, py; scanf("%lld%lld", &px, &py);
	px *= 2, py *= 2;
	repp(i, n) {
		ll cx, cy; scanf("%lld%lld", &cx, &cy);
		cx *= 2, cy *= 2;
		if(px+py == cx+cy)
			l[i] = {1, px+py, px, cx};
		else
			l[i] = {-1, px-py, px, cx};
		px = cx, py = cy;
	}

	ll low = 0, high = (ll)2e12 + 50, res = -1;
	while(low <= high) {
		ll mid = (low + high) / 2;
		if(check(mid)) {
			res = mid;
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	if(res == -1) printf("-1\n");
	else if(res&1) printf("%d 2\n", res);
	else printf("%d 1\n", res/2);
}


int main() {
	int T; scanf("%d", &T);
	repp(tnum, T) {
		printf("Case #%d\n", tnum);
		solve();
	}
}
