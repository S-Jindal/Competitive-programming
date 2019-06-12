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
const int mod = 1e9 + 6, mod1 = 1e9 + 7;
const int inf = 2e18;
const ld eps = 1e-9;
const int NN = 1e5 + 2;

vvi adj;

int pow(int a, int b, int m = mod) {
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

	//matrix with given dimensions and random values
	matrix(int rows, int cols) : r(rows), c(cols) {
		A.assign(r , vector<T>(c));
	}

	//matrix with given value and dimensions
	matrix(int rows, int cols, T val) : r(rows), c(cols) {
		A.assign(r , vector <T> (c , val));
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

vvi one = { {1,1, 1, 1, 1}, 
	{1, 0, 0, 0, 0},
	{0,1,0,0, 0},
	{0,0,0,1, 1},
	{0, 0, 0, 0, 1}
};

vvi two = { {1, 1, 1},
		{1, 0, 0}, 
		{0, 1, 0}
};

void solve(){
      int i = 0, f1, f2, f3, c, j = 0, k = 0, n = 0, m = 0;
      cin >> n >> f1 >> f2 >> f3 >> c;
      k = pow(c, 2, mod1);      
      int p;
      matrix<int> h(one);
      matrix<int> g(two);

      int ans = 1;
      h = h.pow(n-3);
      p = h[0][4];
      ans = ans * pow(k, p, mod1) % mod1;
      g = g.pow(n-3);
      ans = ans * pow(f3, g[0][0], mod1) % mod1;
      ans = ans * pow(f2, g[0][1], mod1) % mod1;
      ans = ans * pow(f1, g[0][2], mod1) % mod1;

      cout << ans << endl;
}

int32_t main(){
#ifndef TRACE
	ios::sync_with_stdio(false); cin.tie(0); 
#endif	
	solve();

	return 0;
}
