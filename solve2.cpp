#include<bits/stdc++.h>
using namespace std;

#define all(a) a.begin(),a.end()
#define pb push_back
#define sz(a) ((int)a.size())

using ll=long long;

using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int N=300000,K=50;
int n,m,k,gr[N],n2;
vector<int> a[N],a2[N];
vector<double> b[N];
mt19937 rng(777771449);

void sort_all(){
    sort(a,a+n,[&](vector<int> vec1, vector<int> vec2){
        vector<int> tmp1(vec1.begin()+1,vec1.end());
        vector<int> tmp2(vec2.begin()+1,vec2.end());
        return tmp1<tmp2;
    });
    cout << n << ' ' << m << "\n";
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j) cout << a[i][j] << ' ';
        cout << '\n';
    }
}

double f(int x){
    return log(x+4);
}

double f_inv(double x){
    return exp(x)-4;
}

double dis(int x, int y){
    double res=0;
    for(int i=1; i<m; ++i){
        double u=f(a[x][i]),v=f(a[y][i]);
        res+=pow(abs(u-v),2);
    }
    return sqrt(res);
}

vector<double> tot[K];
int cnt[K];

void k_means_cluster(){
    for(int i=0; i<n; ++i) gr[i]=rng()%k;
    for(int i=0; i<k; ++i) tot[i].resize(m);
    for(int it=0; it<100; ++it){
        memset(cnt,0,sizeof cnt);
        for(int i=0; i<k; ++i) for(int j=0; j<m; ++j) tot[i][j]=0;
        for(int i=0; i<n; ++i){
            cnt[gr[i]]++;
            for(int j=1; j<m; ++j) tot[gr[i]][j]+=b[i][j];
        }
        for(int i=0; i<k; ++i) for(int j=0; j<m; ++j) tot[i][j]/=cnt[i];
        int change=0;
        memset(cnt,0,sizeof cnt);
        vector<int> ord(n);
        iota(all(ord),0);
        shuffle(all(ord),rng);
        for(int i: ord){
            int id=-1;
            double bst=1e18;
            for(int j=0; j<k; ++j){
                double de=0;
                for(int r=1; r<m; ++r) de+=pow(abs(b[i][r]-tot[j][r]),2);
                de=sqrt(de);
                de+=cnt[j]/10000.0;
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
    for(int i=0; i<k; ++i){
        cerr << "group " << i << ' ' << cnt[i] << ' ';
        for(int j=1; j<m; ++j) cerr << f_inv(tot[i][j]) << ' ';
        cerr << '\n';
    }
    cout << n << ' ' << m-1 << "\n";
    for(int j=0; j<k; ++j){
        for(int i=0; i<n; ++i) if(gr[i]==j){
            cout << a[i][0] << ' ' << gr[i] << ' ';
            for(int r=1; r<m; ++r) cout << a[i][r] << ' ';
            cout << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    //cout << fixed << setprecision(10);
    cin >> n >> m;
    int cur=0;
    for(int i=0; i<n; ++i){
        a[i].resize(m);
        for(int j=0; j<m; ++j) cin >> a[i][j];
        if(a[i][1]==0){
            a2[cur]=a[i];
            cur++;
        }
    }
    n=cur;
    for(int i=0; i<n; ++i){
        a[i]=a2[i];
    }
    k=5;
    for(int i=0; i<n; ++i){
        b[i].resize(m);
        b[i][0]=a[i][0];
        /*
        double tot=0;
        for(int j=1; j<m; ++j){
            tot+=a[i][j]*a[i][j];
        }
        tot=sqrt(tot);
        for(int j=1; j<m; ++j){
            b[i][j]=a[i][j]/tot;
        }
        */
        for(int j=1; j<m; ++j){
            b[i][j]=f(a[i][j]);
        }
    }
    k_means_cluster();
    /*
    map<vector<int>,int> mp;
    for(int i=0; i<n; ++i){
        vector<int> ord(m-1);
        iota(all(ord),0);
        sort(all(ord),[&](int x, int y){return a[i][x+1]<a[i][y+1];});
        mp[ord]++;
    }
    for(auto &[v,y]: mp){
        for(int i=0; i<sz(v); ++i) cout << v[i] << ' ';
        cout << y << "\n";
    }
    */
}
