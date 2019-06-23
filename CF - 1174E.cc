//    This problem can also be solved without DP using only combinatorics. 
//    This is DP based solution

#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define fr(i,j,k) for(i = j; i < (k); i++)
#define all(x) x.begin(), x.end()
#define el '\n'
#define remax(a,b) a = max(a, b)
#define remin(a,b) a = min(a, b)
#define sz(x) int32_t(x.size())


typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<pii> vpi;
// ---------------------------  TEMPLATE ENDS  -------------------------------------
const int mod = 1e9+7;
const int NN = 1e6 + 2;

int dp2[NN][20][2];

void solve(){
	int i = 0, j = 0, k = 0, n = 0, m = 0;
	cin >> n;
	int pow2 = 0;
	for(; (1<<(pow2 + 1)) <= n; pow2++);

	if((1<<(pow2 - 1)) * 3 <= n) 
		dp2[1][pow2 - 1][1] = 1;
	dp2[1][pow2][0] = 1;

	for(int len = 2; len <= n; len++) {
			// for pow3 = 1
		for(int x = 0; x < pow2; x++) {
			int &v = dp2[len][x][1];
			v = dp2[len - 1][x + 1][1] * 1LL * (n/((1<<x) * 3) - n/((1<<(x + 1)) * 3)) % mod;
			v = (v + (dp2[len - 1][x][1] * 1LL * (n/((1<<x) * 3) - len + 1) % mod)) % mod;
		}

			// for pow3 = 0
		for(int x = 0; x < pow2; x++) {
			int &v = dp2[len][x][0];
			v = dp2[len - 1][x + 1][0] * 1LL * (n/(1<<x) - n/(1<<(x+1))) % mod;
			v = (v + (dp2[len - 1][x][0] * 1LL * (n/(1<<x) - len + 1) % mod)) % mod;
			v = (v + (dp2[len - 1][x][1] * 1LL * (n/(1<<x) - n/((1<<x) * 3)) % mod)) % mod;
		}
	}

	cout << dp2[n][0][0] << el;
}

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	solve();
	return 0;
}
