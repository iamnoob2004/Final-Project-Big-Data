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
vector<double> tot[K];
int cnt[K];

void k_means_cluster(vector<int> ids, int start, int groups){
    for(int i: ids) gr[i]=rng()%groups+start;
    for(int i=0; i<k; ++i) tot[i].resize(m);
    for(int it=0; it<100; ++it){
        for(int i=start; i<start+groups; ++i) cnt[i]=0;
        for(int i=start; i<start+groups; ++i) for(int j=0; j<m; ++j) tot[i][j]=0;
        for(int i: ids){
            cnt[gr[i]]++;
            for(int j=0; j<m-1; ++j) tot[gr[i]][j]+=a[i].second[j];
        }
        for(int i=start; i<start+groups; ++i) for(int j=0; j<m; ++j) tot[i][j]/=cnt[i];
        int change=0;
        for(int i=start; i<start+groups; ++i) cnt[i]=0;
        for(int i: ids){
            int id=-1;
            double bst=1e18;
            for(int j=start; j<start+groups; ++j){
                double de=0;
                for(int r=0; r<m-1; ++r) de+=pow(abs(a[i].second[r]-tot[j][r]),2);
                de=sqrt(de);
                if(id==-1||de<bst){
                    bst=de;
                    id=j;
                }
            }
            change+=(gr[i]!=id);
            gr[i]=id;
            cnt[gr[i]]++;
        }
        cerr << it << ' ' << change << "\n";
        if(change==0) break;
    }
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
    vector<int> vec1,vec2,vec3;
    for(int i=0; i<n; ++i){
        vec1.pb(i);
    }
    k=4*(m-1)-1;
    k_means_cluster(vec1,0,15);
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
