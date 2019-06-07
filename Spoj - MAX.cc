#include <bits/stdc++.h>
using namespace std;

------------------------- MACROS -------------------------------------------------------------------
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

void solve(){
      int i = 0, n, j;
      cin>>n;
      vi a(n);
      fr(i, 0, n){
      	cin>>a[i];
      }
      sort(all(a), greater<int>());
      i = 0;
      vi aux;
      for(int bit = 62; bit >= 0 and i < n; bit--){
      	for(j = i; j < n; j++){
      		if((1LL<<bit)&a[j]){
      			break;
      		}
      	}      	
      	if(j < n) {
      		swap(a[i], a[j]);
      		fr(j, i+1, n){
      			if((1LL<<bit)&a[j]) {
      				a[j] ^= a[i];
      			}
      		}
      		aux.pb(a[i]);
      		i++;
      	}
      }
      int ans = 0;
      for(auto x : aux){
      	int bit = 62;
      	for(; bit >= 0; bit--){
      		if ((1LL<<bit) & x)
      		{
      			break;
      		}
      	}
      	if(bit >= 0 and !((1LL<<bit) & ans)) {
      		ans ^= x;
      	}
      }

      cout << ans << endl;
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

// - - - - - - - - - - - - - - - - - - - - - - - -

/* Alternative Solution. A bit faster */

#include <bits/stdc++.h>
using namespace std;

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
const int NN = 1e5 + 2;
// #define 1 1LL
void solve(){
	int i = 0, n, j;
	cin>>n;
	vi a(n);
	fr(i, 0, n){
		cin>>a[i];
	}
	sort(all(a), greater<int>());
	i = 0;
	vi table(65, -1);
	for(int bit = 62; bit >= 0 and i < n; bit--) {
		for(j = i; j < n; j++){
			if((1LL<<bit)&a[j]){
				break;
			}
		}      	
		if(j < n) {
			swap(a[i], a[j]);
			fr(j, i+1, n){
				if((1LL<<bit)&a[j]) {
					a[j] ^= a[i];
				}
			}
			table[bit] = a[i];
			i++;
		}
	}
	int ans = 0;
	for(int bit = 62; bit >= 0; bit--){
		if(table[bit] != -1 and !((ans>>bit) & 1) ){
			ans ^= table[bit];
		}
	}

	cout << ans << endl;
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


