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
int mod = 1e9+7;
const int inf = 2e18;
const ld eps = 1e-9;
const int NN = 1e5 + 2;

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

int pow(int a, unsigned int b, int m = mod) {
        a %= m;
        int res = 1;
        while (b > 0) {
            if (b & 1)
                res = res * a % m;
            a = a * a % m;
            b >>= 1;
        }
        return res;
}


template <typename T>
struct matrix {
	vector < vector <T> > A;
	int r, c;

	matrix(int rows, int cols, T defualt_val = (T)0) : r(rows), c(cols) {
		A.assign(r , vector <T> (c , defualt_val));
	}

	//Identity matrix
	matrix(int n) : r(n), c(n) {
		A.assign(n , vector <T> (n));
		for(int i = 0; i < n; i++)
			A[i][i] = (T)1;
	}

	matrix(vvi& v) {
		r = v.size();
		c = v[0].size();
		*this = matrix(r, c);
		for(int i = 0; i < r; i++) { 
			for(int j = 0; j < c; j++) {
				A[i][j] = v[i][j];
			}
		}
	}
	// Overload to access/set elements without using dot operator
	// matrix m(5,3):  m[i][j] or m.A[i][j] both are valid to access
	vector<T>& operator [](int i) {
		assert(i < r);
		assert(i >= 0);
		return A[i];
	}

	matrix operator * (matrix &B) {		
		assert(c == B.r);
		int i,j,k;
		int x = r;
		int y = c;
		int z = B.c;

		matrix <T> C(x,z,0);

		for(i=0 ; i<x ; i++)
			for(j=0 ; j<z ; j++)
				for(k=0 ; k<y ; k++)
					C[i][j] = (C[i][j] + (1LL*A[i][k] * 1LL*B[k][j] % mod) ) % mod;

		return C;
	}

	matrix operator + (matrix &B) {
		assert(r == B.r);
		assert(c == B.c);
		matrix <T> C(r,c,0);
		int i,j;
		for(i = 0; i < r; i++)
			for(j = 0; j < c; j++)
				C[i][j] = (A[i][j] + B[i][j]) % mod;
		return C;
	}

	//unary(-): to get negative of matrix
	matrix operator - () {
		matrix <T> C(r,c);
		int i,j;
		for(i=0;i<r;i++)
			for(j=0;j<c;j++)
				C[i][j] = -A[i][j];

		return C;
	}

	matrix operator - (matrix &B) {
		assert(r == B.r);
		assert(c == B.c);

		matrix <T> C(r,c,0);
		int i,j;
		for(i=0;i<r;i++) {
			for(j=0;j<c;j++) {
				C[i][j] = (A[i][j] - B[i][j])%mod;
				if(C[i][j] < 0)
					C[i][j] += mod;
			}
		}
		return C;
	}

	matrix pow(long long n) {
		assert(r == c and n >= 0);
		int i,j;
		matrix C(r);

		matrix X = *this;

		while(n) {
			if(n&1)
				C = C * X;

			X = X * X;
			n >>= 1;
		}
		return C;
	}

	friend ostream& operator << (ostream &out, matrix &M)  {
		for (int i = 0; i < M.r; ++i) 
			for (int j = 0; j < M.c; ++j) 
				out << M[i][j] << " \n"[j == M.c-1];

		out << endl;
		return out;
	}	
};


void solve(){
	int i = 0, j = 0, k = 0, n = 0, m = 0, a, b, ans = 0;
	cin >> n >> a >> b >> mod;
	debug(n, a, b, mod);
	std::vector<unsigned int> cum(20, 0), c(20);
	unsigned int up = 0;
	for(i = 1; i < 19; i++) {	
		up = up * 10 + 9;
		if(up >= a) {
			cum[i] = (up - a) / b + 1;
			remin(cum[i], (unsigned int)n);
		}
		debug(i, cum[i]);
		c[i] = cum[i] - cum[i-1];
	}	
	debug(cum, c);
	int s = (a + ((n-1) * b % mod)) % mod;
	b %= mod; b = mod - b;
	for(unsigned int d = 18, so = 1; d > 0; d--) {
		
		if(c[d] == 0) continue;
		k = pow(10, d, mod);
		debug(d, c[d], s, k, so);

		matrix<int> coeff(3);
		coeff[0][1] = (s - b + mod) % mod;
		coeff[0][2] = b;
		coeff[1][1] = coeff[2][1] = coeff[2][2] = k;
		coeff = coeff.pow(c[d]);
		
		int v = (coeff[0][1] + coeff[0][2]) % mod;
		ans = (ans + (v * so % mod)) % mod;
		s = (s + ((c[d] % mod) * b % mod)) % mod;
		int x = pow(pow(10, d, mod), c[d], mod);		
		so = so * x % mod;
	}
	cout << ans << el;
}
int32_t main(){
#ifndef DEBUG
	ios::sync_with_stdio(false); cin.tie(0); 
#endif

	solve();
	return 0;
}