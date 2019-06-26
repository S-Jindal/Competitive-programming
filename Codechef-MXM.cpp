#include <bits/stdc++.h>
using namespace std;

//------------------------- DEBUGGING -----------------------------------------------------------------------
#ifdef DEBUG
#define debug( args... ) { vector<string> _v = split( #args, ','); err( _v.begin(), args); cerr << '\n'; }
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
//------------------------ MACROS ----------------------------------------------------------------------------

#define int long long
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define fr(i,j,k) for(i = j; i < (k); i++)
#define bck(i,j,k) for(i = j; i > (k); i--)
#define all(x) x.begin(), x.end()
#define el '\n'

typedef long double DO;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
//---------------------------  TEMPLATE ENDS, MAKE CHANGES FROM HERE ----------------------------------------

const int mod = 1e9+7;
const int inf = 2e18;
const DO eps = 1e-9;
const int NN = 1e5 + 5;

int K;

int check(vi &v, int pos) {
    vi leftbits(NN, 0), rightbits(NN, 0);
    for(int i = 0; i < v.size(); i++) {
        if(i <= pos) leftbits[ v[i] ]++;
        else if(i > pos+1)
            rightbits[ v[i] ]++;
    }

    for(int x = 0; x < NN-1; x++) {
        int h = leftbits[x]/K;
        leftbits[x] -= h*K;
        leftbits[x+1] += h;
        h = rightbits[x]/K;
        rightbits[x] -= h*K;
        rightbits[x+1] += h;
    }
    for(int x = NN-1; x >= 0; x--) {
        if(leftbits[x] > rightbits[x]) return -1;
        else if(rightbits[x] > leftbits[x]) return 1;
    }
    return 0;
}
void solve(){
    int i = 0, j = 0, k = 0, n = 0, m = 0;
    cin >> n >> K;
    vi a(n);
    for (i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int lo = 0, hi = n-2;
        debug(lo, hi, m);
    while(hi > lo) {
        m = hi+lo >> 1;
        int res = check(a, m);
        if(res > 0) lo = m+1;
        else if(res == 0) {
            cout << m+1 << el;
            return;
        }
        else
            hi = m;
    }
    cout << lo+1 << el;
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