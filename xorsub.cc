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
const int NN = 1e5 + 2;

vvi adj;

void solve(){
	int i = 0, j = 0, k = 0, n = 0, m = 0;
	cin>>n>>k;
	vi a(n);
	fr(i, 0, n){
		cin>>a[i];
	}     

	sort(all(a), greater<int>());
	i = 0;
	vi table(11, -1);
	for(int bit = 10; bit >= 0; bit--){
		for(j = i; j < n; j++){
			if((a[j] >> bit) & 1){
				break;
			}
		}
		if(j < n){
			swap(a[i], a[j]);
			for(j = i+1; j < n; j++){
				if((a[j] >> bit) & 1)
					a[j] ^= a[i];
			}

			table[bit] = a[i];
			i++;
		}
	}

	int ans = k;
	for(int c = 1; c < (1<<10); c++){
 		// check whether this exist
		bool e = 1;
		for(int bit = 10, cur = 0; bit >= 0; bit--){
			if( ((c>>bit) & 1) == ((cur>>bit) & 1)) continue;
			if(table[bit] != -1) cur ^= table[bit];
			else e = 0;
		}

		if(e) remax(ans, c^k);

	}
	cout<<ans<<el;
}

int32_t main(){
#ifndef DEBUG
	ios::sync_with_stdio(false); cin.tie(0); 
#endif
	int T = 1, tc;
	cin >> T;
	for(tc = 1; tc <= T; tc++){
		solve();
	}
	return 0;
}


