/*  https://www.codechef.com/problems/CHSTR   */

// Solution using Z algorithm

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


// ------- O(N) space, O(1) time per query -------- 
const int maxn = NN;
int fact[maxn], inv[maxn], invFact[maxn];

int ncr(int n, int r){
	if(n < 0 || r < 0 || n < r) return 0;

	int v = (invFact[r] * invFact[n-r]) %mod;
	return (v*fact[n])%mod;
}

void pre(){
	int i;
	fact[0] = fact[1] = 1;
	for(i = 2; i < maxn; i++) {
		fact[i] = (fact[i-1]*i)%mod;
	}

	inv[0] = 0;
	inv[1] = 1;
	for (i = 2; i < maxn; i++) {
		inv[i] = mod - ((int) (mod / i) * inv[mod % i] % mod);
	}

	invFact[0] = 1;
	for (i = 1; i < maxn; i++) {
		invFact[i] = (inv[i] * invFact[i - 1] % mod);
	}
}

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

vi z_function(int shift, string &s) {
	int n = s.length();
	vi res = {n-shift};
	int L = 0, R = 0;
	for (int i = shift+1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R-L+shift] == s[R]) R++;
			res.eb(R-L);
			R--;
		} else {
			int k = i-L;
			if (res[k] < R-i+1) res.pb(res[k]);
			else {
				L = i;
				while (R < n && s[R-L+shift] == s[R]) R++;
				res.pb(R-L); 
				R--;
			}
		}
	}
	return res;
}

string s;
void solve(){
	int i = 0, j = 0, k = 0, n = 0, m = 0;
	cin >> n >> m;
	cin >> s;
	vi cum(n+2, 0), cnt(n+2);
	fr(i, 0, n) {
		vi z = z_function(i, s);
		debug(i, z);
		sort(all(z));
		for(k = 1, j = 0; k <= n-i; k++) {
			while(j < z.size() and z[j] < k){
				j++;
			}
			if(j < z.size())
				cum[z.size() - j]++;
		}
		debug(cum);
	}     
	fr(i, 1, n+1) {
		cnt[i] = cum[i] - cum[i+1];
	}
	// debug(cum, cnt);
	vector<int> ans(n+1, 0);
	fr(i, 1, n+1) {
		fr(j, i, n+1) {
			ans[i] += (ncr(j, i)*cnt[j] % mod);
			ans[i] %= mod;
		}

	}
	while(m--) {
		cin>>k;
		if(k > n) cout<<"0\n";
		else {
			cout << ans[k]<<el;
		}
	}
}

int32_t main(){
#ifndef DEBUG
	ios::sync_with_stdio(false); cin.tie(0); 
#endif
	pre();
	int T = 1, tc;
	cin >> T;
	for(tc = 1; tc <= T; tc++){
		solve();
	}
	return 0;
}




// Solution using Trie


#include <bits/stdc++.h>
using namespace std;

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
// ---------------------------  TEMPLATE ENDS  -------------------------------------

const pii dxy[] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
const int mod = 1e9+7;
// const int inf = 2e18;
const ld eps = 1e-9;
const int NN = 5001;

long long fact[NN], inv[NN], invFact[NN];
long long ncr(int n, int r){
	if(n < 0 || r < 0 || n < r) return 0;

	int v = (invFact[r] * invFact[n-r]) %mod;
	return (v*fact[n])%mod;
}

void pre(){
	int i;
	fact[0] = fact[1] = 1;
	for(i = 2; i < NN; i++) {
		fact[i] = (fact[i-1]*i)%mod;
	}

	inv[0] = 0;
	inv[1] = 1;
	for (i = 2; i < NN; i++) {
		inv[i] = mod - ((int) (mod / i) * inv[mod % i] % mod);
	}

	invFact[0] = 1;
	for (i = 1; i < NN; i++) {
		invFact[i] = (inv[i] * invFact[i - 1] % mod);
	}
}


const int MAXLEN = 2500, ALPHA = 26;
int trie[NN * MAXLEN][ALPHA], so = 0;
int trie_cnt[NN * MAXLEN];

string s;
vi cum, cnt;

void insert(int ind) {
	int n = s.size();
	for(int i = ind, u = 1; i < n; i++) {
		int to = s[i] - 'a';
		if(trie[u][to]) {
			u = trie[u][to];
			trie_cnt[u]++;
		} else { 
			so++;
			trie[u][to] = so;
			u = so;
			trie_cnt[u] = 1;
		}
		cum[trie_cnt[u]]++;
	}
}


void solve(){
	int i = 0, j = 0, k = 0, n = 0, m = 0;
	cin>>n>>m;
	cin>>s;
	
	fr(i, 0, n*MAXLEN) {
		fr(j,0,26) {
			trie[i][j] = 0;
		}
		trie_cnt[i] = 0;
	}	
	cum.assign(n+2, 0);
	cnt.assign(n+2, 0);
	so = 1;
	for(i = n-1; i >= 0; i--) { 
		insert(i);
		debug(cum);
	}
	fr(i, 1, n+1) {
		cnt[i] = cum[i] - cum[i+1];
	}

	vector<long long> ans(n+1, 0);
	fr(i, 1, n+1) {
		fr(j, i, n+1) {
			ans[i] += (ncr(j, i)*cnt[j]*1LL % mod);
			ans[i] %= mod;
		}

	}
	debug(cnt, ans);

	while(m--) {
		cin>>k;
		if(k > n) cout<<"0\n";
		else {
			cout << ans[k]<<el;
		}
	}
}

int32_t main(){
#ifndef TRACE
	ios::sync_with_stdio(false); cin.tie(0); 
#endif
	pre();
	int T = 1, tc;
	cin >> T;
	for(tc = 1; tc <= T; tc++){
		solve();
	}
	return 0;
}
