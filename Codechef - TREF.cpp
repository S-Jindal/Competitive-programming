#include <bits/stdc++.h>
using namespace std;

#define int 		long long
#define pb 			push_back
#define eb 			emplace_back
#define fi 			first
#define se 			second
#define fr(i,j,k) 	for(i = j; i < (k); i++)
#define all(x) 	 	x.begin(), x.end()
#define el 		 	'\n'
#define remax(a,b)	a = max(a, b)
#define remin(a,b) 	a = min(a, b)
#define SZ(x) 	 	(int)x.size()
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<pii> vpi;
// ---------------------------  TEMPLATE ENDS  -------------------------------------

const pii dxy[] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
const int mod = 1e9+7;
const int inf = 2e18;
const ld eps = 1e-9;
const int NN = 1e5 + 2;

vvi adj;
vi c, par;
vi t, store;

vector< set<pair<pii, int>> > lists;

string to_string(string s) {
	return '"' + s + '"';
}
string to_string(const char* s) {
	return to_string((string) s);
}
string to_string(bool b) {
	return (b ? "true" : "false");
}
template <typename A, typename B>
string to_string(pair<A, B> p) {
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template <typename A>
string to_string(A v) {
	bool first = true;  string res = "{";
	for (const auto &x : v) {
		if (!first) { res += ", "; }
		first = false; res += to_string(x);
	}
	res += "}";	  return res;
}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	cerr << " " << to_string(H);
	debug_out(T...);
}

// #define TRACE
#ifdef TRACE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

bool checker(int x, int tar, int n) {
	int q = 0;
	for(int i = 1; i <= n; i++) {
		if(store[i] > 0 and x >= t[i]) {
			if(store[i] > 1e10/(x-t[i]+1)) return 1;
			q += store[i] * (x - t[i] + 1);
			if(q >= tar) return 1;
		}
	}
	return 0;
}	

void solve(){
	int i = 0, j = 0, tar, k = 0, n = 0, m = 0;
	cin >> n >> tar;
	
	adj.clear();
	adj.resize(n + 1);
	store.assign(n+1, 0);
	par.assign(n+1 , 0);
	c.assign(n+1, 0);
	t.assign(n+1, inf);
	lists.clear();
	lists.resize(n + 1);

	fr(i, 2, n+1) {
		cin>>par[i];
		adj[par[i]].pb(i);
		adj[i].pb(par[i]);
	}     
	fr(i, 2, n+1) {
		cin>>c[i];
	}
	vpi dis;

	fr(i, 2, n+1) {
		if(SZ(adj[i]) == 1) { 
			int u = par[i], d = 0;
			while(u > 0) {
				d++;
				u = par[u];
			}

			dis.eb(d, i);
		}
	}
	sort(all(dis));
	for(auto it : dis) {
		int u = it.se;
		t[u] = it.fi;
		int a = inf;
		while(u > 1) {
			remin(a, c[u]);
			u = par[u];
			// c[u] -= a;
		}

		store[it.se] = a;
		u = it.se;
		while(u > 1) {
			c[u] -= a;
			u = par[u];
		}
	}

	debug(store, t);
	int ans = -1, lo = 0, hi = 1e10;
	while(hi >= lo) {
		int mid = hi + lo >> 1;
		if(checker(mid, tar, n)) {
			ans = mid;
			hi = mid - 1;
		}
		else{
			lo = mid + 1;
		}
	}
	cout << ans << el;
}

int32_t main(){
#ifndef TRACE
	ios::sync_with_stdio(false); cin.tie(0); 
#endif
	int T = 1, tc;
	cin >> T;
	for(tc = 1; tc <= T; tc++){
		solve();
	}
	return 0;
}
