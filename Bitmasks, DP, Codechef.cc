//CODECHEF : SUPERSTRINGS 

// Solution Copyright @ Jindal
#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define gc getchar_unlocked
#define fi first
#define se second
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mp make_pair
#define vi vector<int>
#define vll vector<ll>
const int mod = (int)1e9+7;

inline int in()  
{
	int NR=0,sign=1;    char c=gc();
    while( c < 48 || c > 57 ){if(c=='-')sign=0; c=gc();}
    while(c>47 && c< 58)
    {    NR = (NR << 3) + (NR << 1) + (c - 48);    c=gc();    }
    return (sign?NR:(-NR));
}


int n,p,q,l,m,i,j;
int mx = (1<<20)-1;
ll supermasks[mx+1];
int a[mx];
ll dp0[mx+1][20];
int cnt[mx+1];	// cnt of strings/input with that bitmask
void solve(){
	// calculate supermasks of all numbers from 0 to mx
	supermasks[mx]=cnt[mx];
	for(i=mx-1; i>=0; i--){
	
		k=0;
		for(j=1<<19; j>0; j>>=1){
			if((j&i)==0)
				k++;
		}
		dp0[i][k] = supermasks[i] = cnt[i];
		for(j=1<<19; j>0; j>>=1){
			if(i&j==0){
				q = i|j;
				break;
			}
		}
		for(j=j>>1, p=k-1; j>0 && p>0; j>>=1){
			if(i & j == 0){
				dp0[i][p] = dp0[i][p+1] + dp0[q][p]; 
				supermasks[i] += dp0[i][p];
				p--;
				q=i|j;
			}
		}
		supermasks[i] += cnt[mx];
	}
	ll ans=0;
	for(i=0; i<n; i++){
		j = mx-a[i];
		ans += supermasks[j];
	}
	cout<<ans;
}

int main(int argc, char const *argv[])
{
	scanf("%d",&n);
	char s[100];
	for(i=0; i<n; i++){
		scanf("%s", s);
		l = strlen(s);
		k = 0;
		for(j=0; j<l; j++){
			k = k|(1<<(s[j]-'A'));
		}
		a[i]=k;
		cnt[k]++;
	}
	solve();
	return 0;
}
