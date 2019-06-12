#include <bits/stdc++.h>
using namespace std;
// #define DEBUG

// ------------------------- DEBUGGING -----------------------------------------------------------------
#ifdef DEBUG
#define debug(args...) { vector<string> _v = split(#args, ','); err( _v.begin(), args); cerr << endl; }
vector<string> split( const string& s, char c) {
      vector<string> v;
      stringstream ss( s);
      string x;
      while ( getline( ss, x, c))
            v.emplace_back( x);
      return move( v);
}
void err( vector<string>::iterator it) { }
template<typename T, typename... Args>
void err( vector<string>::iterator it, T a, Args... args) {
      cerr << it -> substr( ( *it)[0] == ' ', it -> length()) << " = " << a << '\t';
      err( ++it, args...);
}
#else
#define debug(...)
#endif
// -------------------------- MACROS -------------------------------------------------------------------

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

typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<pii> vpi;
// ---------------------------  TEMPLATE ENDS  -------------------------------------------------------

const pii dxy[] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
const int mod = 1e9+7;
const int inf = 2e18;
const ld eps = 1e-9;
const int NN = 5e5 + 2, MAXLOG = 19;

vvi adj;
vi in[NN];
int dp[NN][MAXLOG];

void solve(){
      int i = 0, j = 0, k = 0, n = 0, m = 0;
      cin>>n>>m;
      vi l(n), r(n);
      fr(i,0,n){
      	cin>>l[i]>>r[i];
      	in[l[i]].pb(i);
      }

      multiset<int> curr;
      fr(i, 0, NN){
      	for(auto& x : in[i]) {
      		curr.insert(r[x]);
      	}

      	if(!curr.empty()) {
			k = *curr.rbegin();
			if(k < i) curr.clear();
			else {
				dp[i][0] = k;
			}    		
      	}
      }

      for(i = NN-2; i >= 0; i--){
      	for(j = 1; j < MAXLOG and dp[i][j-1] > i; j++) {
      		dp[i][j] = dp[dp[i][j-1]][j-1];
      		if(dp[i][j] == dp[i][j-1]) {
      			dp[i][j] = 0;
      			break;
      		}
      	}
      }

      while(m--){
      	int x, y, ans = 0;
      	cin>>x>>y;
      	for(j = MAXLOG-1; j >= 0 and x < y; j--) {
      		if(dp[x][j] > x and dp[x][j] <= y) {
      			x = dp[x][j];
      			ans += (1<<j);
      		}
      	}
      	if(x < y) {
      		if(dp[x][0] >= y)
      			ans++;
      		else
      			ans = -1;
      		cout<<ans<<el;
      	}
     		else{
     			cout<<ans<<el;
     		}
      }
}

int32_t main(){
#ifndef DEBUG
      ios::sync_with_stdio(false); cin.tie(0); 
#endif
      int T = 1, tc;
      // cin >> T;
      for(tc = 1; tc <= T; tc++){
            solve();
      }
      return 0;
}
