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
const int NN = 1e5 + 2;

void solve(){
      int i = 0, j = 0, cnt_b = 0, cnt_a = 0, n = 0, m = 0;
 	string a, b;
 	cin >> a >> b;
 	int na = a.length(), nb = b.length();
 	for(i = 0; i < nb; i++) {
 		cnt_b += b[i] == '1';
 		cnt_a += a[i] == '1';
 	}
 	int ans = (cnt_b + cnt_a) % 2 == 0;
 	for(i = nb; i < na; i++) {
 		cnt_a -= a[i - nb] == '1';
 		cnt_a += a[i] == '1';
 		ans += ((cnt_a + cnt_b)%2 == 0);
 	}
 	cout << ans;
}

int32_t main(){
      ios::sync_with_stdio(false); cin.tie(0); 
      int T = 1, tc;

      for(tc = 1; tc <= T; tc++){
            solve();
      }
      return 0;
}
