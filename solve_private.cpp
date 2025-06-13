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
int n,m,k,gr[N];
point a[N];
vector<double> b[N];
mt19937 rng(777771449);

vector<double> tot[K],tot2[K];
int cnt[K],cnt2[K];

double dis(vector<double> vec1, vector<double> vec2){
    assert(sz(vec1)==m-1&&sz(vec2)==m-1);
    double res=0;
    for(int i=0; i<m-1; ++i) res+=(vec1[i]-vec2[i])*(vec1[i]-vec2[i]);
    return sqrt(res);
}

signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cout << fixed << setprecision(10);
    cin >> n >> m;
    for(int i=0; i<n; ++i){
        a[i].second.resize(m-1);
        cin >> a[i].first;
        for(int j=0; j<m-1; ++j) cin >> a[i].second[j];
    }
    k=4*(m-1)-1;
    for(int i=0; i<k; ++i) tot[i].resize(m-1),tot2[i].resize(m-1);
    map<pii,int> mp;
    for(int i=0; i<n; ++i){
        int msk=0;
        for(int j=0; j<m-1; ++j) if(a[i].second[j]>0.01){
            msk|=1<<j;
        }
        gr[i]=-1;
        if(msk==3){
            gr[i]=0;
        }
        else if(msk==7){
            if(a[i].second[1]>0.76) gr[i]=1;
            else if(a[i].second[1]>0.62) gr[i]=2;
            else gr[i]=3;
        }
        else if(msk==15){
            if(a[i].second[1]>0.76) gr[i]=4;
            else if(a[i].second[2]>0.76) gr[i]=5;
            else gr[i]=6;
        }
        else if(msk==30){
            if(a[i].second[2]>0.76) gr[i]=7;
            else if(a[i].second[3]>0.76) gr[i]=8;
            else gr[i]=9;
        }
        else if(msk==60){
            if(a[i].second[3]>0.76) gr[i]=10;
            else if(a[i].second[4]>0.76) gr[i]=11;
            else gr[i]=12;
        }
        else if(msk==56){
            if(a[i].second[4]>0.76) gr[i]=13;
            else if(a[i].second[4]>0.62) gr[i]=14;
            else gr[i]=15;
        }
        else if(msk==48){
            gr[i]=16;
        }
        if(gr[i]!=-1){
            cnt2[gr[i]]++;
            for(int j=0; j<m-1; ++j) tot2[gr[i]][j]+=a[i].second[j];
        }
    }
    for(int j=0; j<k; ++j) if(cnt2[j]>0){
        cerr << j << ' ' << cnt2[j] << "\n";
        for(int i=0; i<m-1; ++i) tot2[j][i]/=cnt2[j];
    }
    for(int i=0; i<n; ++i){
        if(gr[i]==-1){
            double mn=1e18;
            for(int j=0; j<k; ++j) if(cnt2[j]>0){
                //cerr << i << ' ' << j << ' ' << dis(tot2[j],a[i].second) << "\n";
                if(dis(tot2[j],a[i].second)<mn){
                    mn=dis(tot2[j],a[i].second);
                    gr[i]=j;
                }
            }
            assert(gr[i]>=0);
        }
    }

    for(int i=0; i<n; ++i){
        assert(gr[i]>=0);
        cnt[gr[i]]++;
        for(int j=0; j<m-1; ++j) tot[gr[i]][j]+=a[i].second[j];
    }
    for(int j=0; j<k; ++j) if(cnt[j]>0){
        for(int i=0; i<m-1; ++i) tot[j][i]/=cnt[j];
    }
    
    for(int i=0; i<k; ++i){
        cerr << "group " << i << ' ' << cnt[i] << ' ';
        for(int j=0; j<m-1; ++j) cerr << tot[i][j] << ' ';
        cerr << '\n';
    }
    cout << n << ' ' << m-1 << "\n";
    for(int j=0; j<k; ++j){
        for(int i=0; i<n; ++i) if(gr[i]==j){
            cout << a[i].first << ' ' << gr[i] << ' ';
            for(int r=0; r<m-1; ++r) cout << a[i].second[r] << ' ';
            cout << '\n';
        }
    }
    
}
