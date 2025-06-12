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

void sort_all(){
    sort(a,a+n,[&](point x, point y){
        return x.second<y.second;
    });
    cout << n << ' ' << m << "\n";
    for(int i=0; i<n; ++i){
        cout << a[i].first << ' ';
        for(int j=0; j<m-1; ++j) cout << a[i].second[j] << ' ';
        cout << '\n';
    }
}
/*
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
*/

vector<double> tot[K];
int cnt[K];

void k_means_cluster(vector<int> ids, int start, int groups){
    for(int i: ids) gr[i]=rng()%groups+start;
    for(int i=0; i<k; ++i) tot[i].resize(m);
    for(int it=0; it<100; ++it){
        //memset(cnt,0,sizeof cnt);
        for(int i=start; i<start+groups; ++i) cnt[i]=0;
        for(int i=start; i<start+groups; ++i) for(int j=0; j<m; ++j) tot[i][j]=0;
        for(int i: ids){
            cnt[gr[i]]++;
            for(int j=0; j<m-1; ++j) tot[gr[i]][j]+=a[i].second[j];
        }
        for(int i=start; i<start+groups; ++i) for(int j=0; j<m; ++j) tot[i][j]/=cnt[i];
        int change=0;
        //memset(cnt,0,sizeof cnt);
        for(int i=start; i<start+groups; ++i) cnt[i]=0;
        //vector<int> ord(n);
        //iota(all(ord),0);
        //shuffle(all(ord),rng);
        for(int i: ids){
            int id=-1;
            double bst=1e18;
            for(int j=start; j<start+groups; ++j){
                double de=0;
                for(int r=0; r<m-1; ++r) de+=pow(abs(a[i].second[r]-tot[j][r]),2);
                de=sqrt(de);
                // de+=cnt[j]/200000.0;
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
    /*
    for(int i=0; i<k; ++i){
        cerr << "group " << i << ' ' << cnt[i] << ' ';
        for(int j=1; j<m; ++j) cerr << tot[i][j] << ' ';
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
    */
}

//double mu[K],sigma[K];

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
        /*
        if(a[i].second[0]<0.01) vec1.pb(i);
        else if(a[i].second[3]<0.01) vec2.pb(i);
        else vec3.pb(i);
        */
        vec1.pb(i);
    }
    cerr << sz(vec1) << ' ' << sz(vec2) << ' ' << sz(vec3) << "\n";
    k=4*(m-1)-1;
    //k_means_cluster(vec1,0,5);
    //k_means_cluster(vec2,5,5);
    //k_means_cluster(vec3,10,5);
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
    /*
    for(int j=0; j<m-1; ++j){
        for(int i=0; i<n; ++i){
            mu[j]+=a[i].second[j];
        }
        mu[j]/=n;
    }
    for(int j=0; j<m-1; ++j){
        for(int i=0; i<n; ++i){
            sigma[j]+=pow(a[i].second[j]-mu[j],2);
        }
        sigma[j]/=n;
        sigma[j]=sqrt(sigma[j]);
    }
    for(int j=0; j<m-1; ++j){
        for(int j2=0; j2<m-1; ++j2){
            double cov=0;
            for(int i=0; i<n; ++i) cov+=1ll*a[i].second[j]*a[i].second[j2];
            cov/=n;
            cov-=mu[j]*mu[j2];
            cout << cov/(sigma[j]*sigma[j2]) << ' ';
        }
        cout << "\n";
    }
    */
    /*
    const int M=100;
    int cnt[4][M+1]{};
    for(int i=0; i<n; ++i){
        int id=max_element(a[i].second.begin()+1,a[i].second.end())-a[i].second.begin();
        if(a[i].second[0]<0.01){
            cnt[id][int(a[i].second[id]*M)]++;
        }
    }
    for(int i=0; i<M; ++i) if(max({cnt[1][i],cnt[2][i],cnt[3][i]})>0){
        cout << i << ' ';
        for(int x=1; x<4; ++x) cout << cnt[x][i] << ' ';
        cout << '\n';
    }
    
    const int M=30;
    int cnt[M+1][M+1]{};
    int tot=0;
    for(int i=0; i<n; ++i){
        if(a[i].second[0]<0.01){
            if(a[i].second[1]<0.25&&a[i].second[3]<0.25) tot++;
            if(a[i].second[3]>max(a[i].second[1],a[i].second[2])){
                cnt[int(a[i].second[1]*M)][int(a[i].second[2]*M)]++,tot++;
            }
        }
    }
    cout << tot << "\n";
    */
    /*
    cout << tot << "\n";
    for(int i=0; i<M; ++i){
        for(int j=0; j<M; ++j) cout << setw(4) << cnt[i][j] << ' ';
        cout << '\n';
    }
    */
    /*
    k=4*(m-1)-1;
    for(int i=0; i<n; ++i){
        b[i].resize(m);
        b[i][0]=a[i][0];
        
        double tot=0;
        for(int j=1; j<m; ++j){
            tot+=a[i][j]*a[i][j];
        }
        tot=sqrt(tot);
        for(int j=1; j<m; ++j){
            b[i][j]=a[i][j]/tot;
        }
        
        for(int j=1; j<m; ++j){
            b[i][j]=f(a[i][j]);
        }
    }
    */
    // k_means_cluster();

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
