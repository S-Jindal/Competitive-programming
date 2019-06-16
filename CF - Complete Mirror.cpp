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
#define SZ(x) (int)x.size()
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<pii> vpi;
// ---------------------------  TEMPLATE ENDS  -------------------------------------

const pii dxy[] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
const int mod = 987654319, B = 123456;
const int inf = 2e18;
const ld eps = 1e-9;
const int NN = 1e5 + 2;

vvi adj;
map<int, int> to[NN];
vi dp;

int call(int u, int p) {
	int so = -1, c = SZ(adj[u]);
	dp[u] = 1;
	if(u > 1 and c == 1) return 1;
	for(auto v : adj[u]) {
		if(v != p) {
			int g = call(v, u);
			g = (g*B + c) % mod;
			to[u][v] = g;

			if(so == -1) {
				so = g;
			}
			if(!dp[v] or so != g){
				dp[u] = 0;
			}
		} 
	}
	return dp[u] ? so : -1;
}

void gocheck(int u, int p, int recv) {
	int c = SZ(adj[u]);
	recv = (recv * B + c) % mod;
	if(to[u].empty() or (dp[u] and to[u].begin()->se == recv)) {
		cout<<u<<el;
		exit(0);
	} 
	int cnt = 0, sav = -1;
	for(auto &nxt : to[u]) {
		if(nxt.se != recv) 
			cnt++, sav = nxt.fi;
	}
	if(cnt == 0) {
		for(auto v : adj[u]) 
			if(v != p) 
				gocheck(v, u, recv);
	}
	else if(cnt == 1) 
		gocheck(sav, u, recv);
	
}


void solve(){
	int i = 0, j = 0, k = 0, n = 0, m = 0;
	cin>>n;
	dp.assign(n+1, 0);
	adj.resize(n+5);
	fr(i, 0, n-1) {
		int u, v;
		cin>>u>>v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	call(1, 0);
	if(dp[1]) {
		cout<<"1\n";
		exit(0);
	}
	if(SZ(adj[1]) == 1) {
		gocheck(adj[1][0], 1, 1);
	}
	else {
		std::set<int> uniq;
		for(auto &l: to[1]) {
			uniq.insert(l.second);
		}

		for(auto iter = uniq.begin(); k < 2 and iter != uniq.end(); k++, iter++) {
			int cnt = 0, sav = -1, e = *iter;
			if(e < 0)
				continue;
			for(auto &p : to[1]) {
				if(p.second != e) {
					cnt++;
					sav = p.first;
				}
			}
			if(cnt == 0) {
				for(auto v : adj[1])
					gocheck(v, 1, e);
			}
			else if(cnt == 1){
				gocheck(sav, 1, e);
			}
		}
	}
	cout << "-1\n";
}

int32_t main(){
#ifndef TRACE
	ios::sync_with_stdio(false); cin.tie(0); 
#endif
	int T = 1, tc;
      // cin >> T;
	for(tc = 1; tc <= T; tc++){
		solve();
	}
	return 0;
}
