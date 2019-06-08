// Problem:   https://www.hackerrank.com/contests/101hack50/challenges/frog-in-maze/problem

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
// ---------------------------  TEMPLATE ENDS  -------------------------------------------------------

const pii dxy[] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
const int mod = 1e9+7;
const int inf = 2e18;
const ld eps = 1e-9;
const int NN = 30;


string maze[NN];
int countt[NN*NN], forw[NN][NN];
pii rev[NN*NN];
pii tunnels[NN][NN];
bool vis[NN][NN];
vector<vector<ld>> mat;
int n, m;

bool see(int i, int j){
     return (i >= 0 and i < n and j >= 0 and j < m and vis[i][j]);
}
    
bool is_adjacent(int v, int u){
    int x = rev[v].fi, y = rev[v].se;
    for(auto &p : dxy) {
        int _x = x+p.fi, _y = y+p.se;
        if(see(_x, _y) and forw[_x][_y] == u) {
            return 1;
        }
    }    
    return 0;    
}


int gauss(vector <vector<ld>> &a, vector<ld> &ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
    vector<int> where (m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i) {
            if (fabs (a[i][col]) > fabs (a[sel][col]))
                sel = i;
        }
        if (fabs (a[sel][col]) < eps)
            continue;
        for (int i = col; i <= m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i = row + 1; i < n; ++i) {
            ld c = a[i][col] / a[row][col];
            for (int j = col; j <= m; ++j)
                a[i][j] -= a[row][j] * c;

        }
        ++row;
    }

    ans.assign (m, 0);
    ld t;
    for (int j = m-1; j >= 0; j--) {
        if (where[j] != -1) {
            t = 0.0;
            for (int k = j+1; k < m; k++){
                t += ans[k] * a[where[j]][k];
            }
            ans[j] =  (a[where[j]][m] - t) / a[where[j]][j]; 
        }
    }
    for (int i = 0; i < m; ++i) {
        if (where[i] == -1)
            return inf;
    }
    return 1;
}


void solve(){
    int i = 0, j = 0, k = 0;
    cin >> n >> m >> k;

    fr (i, 0, n) {
        cin>>maze[i];
    }

    pii A;
    memset(forw, -1, sizeof forw);
    fr(i, 0, n){
        fr(j, 0, m){
            tunnels[i][j] = {-1, -1};
            if(maze[i][j] == 'A') {
                A = {i, j};
            }
        }
    }

    fr (i, 0, k){
        int x, y, u, v;
        cin>>x>>y>>u>>v;
        x--; y--; u--; v--;
        tunnels[x][y] = {u,v};
        tunnels[u][v] = {x,y};
    }    
    int so = 0;
    fr(i, 0, n){
        fr(j, 0, m) {
            if(maze[i][j] != '#' and maze[i][j] != '%' && maze[i][j] != '*') {
                forw[i][j] = so;
                rev[so] = {i, j};
                vis[i][j] = 1;
                so++;
                for(auto &p : dxy){
                    int _x = i + p.fi, _y = j+ p.se;
                    if(_x >= 0 and _x < n && _y >= 0 and _y < m and maze[_x][_y] != '#')
                        countt[so-1]++;
                }
            }
        }
    }
    
    mat.resize(so, vector<ld>(so+1, 0.0));
    for(int v = 0; v < so; v++){
        if(!countt[v]){
            fr(j, 0, so){
                mat[v][j] = j == v ? 1 : 0;
            }
        }
        else{
            fr(j, 0, so) {
                if(j == v) {
                    mat[v][j] = 1;
                    continue;
                }
                pii g = rev[j];
                pii to = tunnels[g.fi][g.se];
                if(is_adjacent(v, j)) {
                    if(to != pii(-1, -1) and vis[to.fi][to.se]) {
                        mat[v][forw[to.fi][to.se]] = -1/(ld)countt[v];
                    }
                    else {
                        mat[v][j] = -1/(ld)countt[v];
                    }
                }
            }
            int e = 0;
            for(auto &p : dxy) {
                int x = rev[v].fi + p.fi, y = rev[v].se + p.se;
                if(x >= 0 and x < n and y >= 0 and y <  m and maze[x][y] == '%')
                    e++;
            }
            mat[v][so] = e/(ld)countt[v];
        }
    }
 
    int s = forw[A.fi][A.se]; 
    std::vector<ld> ans;
    int sols = gauss(mat, ans);
    cout << ans[s] << endl;
}

int32_t main(){
#ifndef DEBUG
    ios::sync_with_stdio(false); cin.tie(0); 
#endif
    cout<<fixed<<setprecision(13);
    solve();
    return 0;
}
