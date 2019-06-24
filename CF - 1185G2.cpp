#include <bits/stdc++.h>
using namespace std;

#define int long long
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
// --------------------------------------------------------------------

const pii dxy[] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
const int mod = 1e9+7;
const int inf = 2e18;
const ld eps = 1e-9;
const int NN = 52;

int32_t dp[NN][NN][NN][3];
int32_t dp_useful[NN][NN][NN];
int32_t choose_01[NN][NN][2501];
int32_t choose_2[NN][2501];
int fact[NN];

void pre_compute() {
	fact[0] = 1;
	for(int i = 1; i < NN; i++) {
		fact[i] = fact[i-1]*i % mod;
	}
	dp[0][0][1][2] = dp[0][1][0][1] = dp[1][0][0][0] = 1;
	for(int g0 = 0; g0 < NN/2+1; g0++) {
		for(int g1 = 0; g1 < NN/2+1; g1++) {
			for(int g2 = 0; g2 < NN/2+1; g2++) {
				for(int lst = 0; lst < 3; lst++) {
					for(int nxt_lst = 0; nxt_lst < 3; nxt_lst++) {
						if(nxt_lst != lst) {
							int32_t *v = &(dp[g0 + (nxt_lst == 0)][g1 + (nxt_lst == 1)][g2 + (nxt_lst == 2)][nxt_lst]); 
							*v = (*v + 1LL*dp[g0][g1][g2][lst]) % mod;
						}
					}
				}
			}
		}
	}
	int i, j, k;
	fr(i, 0, NN/2 + 1) {
		fr(j, 0, NN/2 + 1) {
			fr(k, 0, NN/2 + 1) {
				vi v = {i, j, k};
				int mult = 1;
				for(int it : v) {
					mult = mult * fact[it] % mod;
				}
				int q = 0;
				for(int lst: {0, 1, 2}) {
					q = (q + dp[i][j][k][lst])%mod; 	
				}
				dp_useful[i][j][k] = q * mult % mod;
			}
		}
	}
}

void solve(){
	int T, i = 0, j = 0, k = 0, n = 0, m = 0;
	cin >> n >> T;
	vi t(n), g(n);

	int ans = 0;
	choose_2[0][0] = 1;
	choose_01[0][0][0] = 1;

	fr(i, 0, n) {
		cin >> t[i] >> g[i];
		g[i]--;

		if(g[i] == 2) {
			for(int c = NN-1; c > 0; c--) {
				for(int s = T; s >= t[i]; s--) {
					choose_2[c][s] = (choose_2[c][s] + choose_2[c-1][s - t[i]]) % mod;
				}
			}
		}
		else {
			for(int a = NN-1; a >= 0; a--) {
				if(g[i] == 0 and a == 0)
					continue;
				for(int b = NN-1; b >= 0; b--) {
					if(g[i] == 1 and b == 0) continue;
					for(int s = T; s >= t[i]; s--) {
						choose_01[a][b][s] = (choose_01[a][b][s] + 
									 choose_01[a - (g[i] == 0)][b - (g[i] == 1)][s - t[i]]) % mod;
					}
				}
			}
		}
	}
	int num0, num1, num2;
	fr(num0, 0, NN/2+1) {
		fr(num1, 0, NN/2+1) {
			for(int tt = 0; tt <= T; tt++) {
				if(!choose_01[num0][num1][tt])
					continue;
				fr(num2, 0, NN/2+1) {
					if(!choose_2[num2][T - tt])
						continue;

					int x = choose_2[num2][T-tt] * 1LL * choose_01[num0][num1][tt] % mod;
					x = x * dp_useful[num0][num1][num2] % mod;
					ans = (ans + x) % mod;
				}
			}
		}
	}

	cout << ans << el;
}

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0); 
	int T = 1, tc;
	pre_compute();
	for(tc = 1; tc <= T; tc++){
		solve();
	}
	return 0;
}
