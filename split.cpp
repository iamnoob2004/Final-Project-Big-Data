#include<bits/stdc++.h>
using namespace std;

#define all(a) a.begin(),a.end()
#define pb push_back
#define sz(a) ((int)a.size())

using ll=long long;

using pii=pair<int,int>;
using pll=pair<ll,ll>;
using point=pair<int,vector<double>>;

const int N=300000,K=50;
int n,m,k;
point a[N];
mt19937 rng(777771449);
/*
void split_order(){
    vector<int> tar={3,1,2,0};
    vector<vector<int>> want;
    for(int i=0; i<n; ++i){
        vector<int> ord(m-1);
        iota(all(ord),0);
        sort(all(ord),[&](int x, int y){return a[i][x+1]<a[i][y+1];});
        if(ord==tar){
            want.pb(a[i]);
        }
    }
    cout << sz(want) << ' ' << m << "\n";
    for(int i=0; i<sz(want); ++i){
        for(int j=0; j<m; ++j) cout << want[i][j] << ' ';
        cout << '\n';
    }
}
*/
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cout << fixed << setprecision(10);
    cin >> n >> m;
    int cur=0;
    for(int i=0; i<n; ++i){
        a[i].second.resize(m-1);
        cin >> a[i].first;
        for(int j=0; j<m-1; ++j) cin >> a[i].second[j];
    }
    vector<point> want;
    for(int i=0; i<n; ++i){
        if(a[i].second[0]<0.01&&a[i].second[2]>0.95){
            want.pb(a[i]);
        }
    }
    /*
    sort(all(want),[&](vector<int> vec1, vector<int> vec2){
        int mn11=min(vec1[1],vec1[4]),mx11=max(vec1[1],vec1[4]);
        int mn12=min(vec1[2],vec1[3]),mx12=max(vec1[2],vec1[3]);
        int mn21=min(vec2[1],vec2[4]),mx21=max(vec2[1],vec2[4]);
        int mn22=min(vec2[2],vec2[3]),mx22=max(vec2[2],vec2[3]);
        double r1=max(1.0*mx11/mn11,1.0*mx12/mn12);
        double r2=max(1.0*mx21/mn21,1.0*mx22/mn22);
        return r1<r2;
    });
    */
    cout << sz(want) << ' ' << m << "\n";
    for(int i=0; i<sz(want); ++i){
        cout << want[i].first << ' ';
        for(int j=0; j<m-1; ++j) cout << want[i].second[j] << ' ';
        //cout << 1.0*(want[i][2]+want[i][3])/(want[i][1]+want[i][4]) << ' ';
        cout << '\n';
    }
}
