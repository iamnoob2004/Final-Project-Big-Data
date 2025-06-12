#include<bits/stdc++.h>
using namespace std;

#define all(a) a.begin(),a.end()
#define pb push_back
#define sz(a) ((int)a.size())

using ll=long long;

using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int N=300000,K=50;
int n,m,k;
vector<int> a[N];

signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cout << fixed << setprecision(10);
    cin >> n >> m;
    int cur=0;
    for(int i=0; i<n; ++i){
        a[i].resize(m);
        for(int j=0; j<m; ++j) cin >> a[i][j];
    }
    cout << n << ' ' << m << "\n";
    for(int i=0; i<n; ++i){
        double tot=0;
        for(int j=1; j<m; ++j) tot+=1ll*a[i][j]*a[i][j];
        tot=sqrt(tot);
        cout << a[i][0] << ' ';
        for(int j=1; j<m; ++j){
            cout << a[i][j]/tot << ' ';
        }
        cout << '\n';
    }
}
