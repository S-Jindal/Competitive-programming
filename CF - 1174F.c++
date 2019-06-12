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
const int NN = 2e5 + 2;

vvi adj(NN);
bool mark[NN];

int sub[NN], par[NN], h[NN];
void dfs(int u, int p){
	par[u] =p;
	h[u] = h[p]+1;
	for(auto x : adj[u]) if (x != p) dfs(x, u);
}
void subtree_sizes(int u, int nott){
    sub[u]=1;
    for(auto x : adj[u]){
        if(x != nott and !mark[x]){
            subtree_sizes(x, u);
            sub[u]+=sub[x];
        }
    }
}

int centroid (int u, int prev) {
    subtree_sizes(u, prev);
    int cur = u;
    while(1) {
        int c = -1, maxsz = 0;
        for(auto v : adj[cur]){
            if(v == prev or mark[v]) continue;
            if(sub[v] > maxsz){
                c = v;
                maxsz = sub[v];
            }
        }
        if(maxsz > sub[u]/2){
            prev = cur;
            cur = c;
        }
        else
        	break;
    }
    mark[cur]=1;
    return cur;
}

int query(char t, int node){
	cout << t << ' '<<node<<endl;
	int dis; cin>>dis;
	return dis;
}

void solve(){
	int i = 0, j,k, n = 0, ans;
	cin>>n;
	fr(i, 0, n-1){
		cin>>j>>k;
		adj[j].pb(k);
		adj[k].pb(j);
	}
	h[0] = -1;
	dfs(1, 0);
	int d1 = query('d', 1);
	int l = 1, dl = d1;
	while(1){
		int c = centroid(l, par[l]);
		int hc = h[c] - h[l], hx = d1 - h[l];
		debug(c, l, hc, hx);
		if(hx == 0){
			ans = l;
			break;
		}
		int D = query('d', c), hh = (hc+hx - D)/2;
		debug(D);
		if(D == 0) {
			ans = c;
			break;
		}
		int climb = hc - hh;
		while(climb--){
			c = par[c];
		}
		if(h[c] == d1){
			ans = c;
			break;
		}
		debug(c);
		l = query('s', c);
	}

	cout << "! " << ans;
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
