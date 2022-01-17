#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#define ll long long
#define inf 9223372036854775807
#define minf -9223372036854775808
#define mod 998244353
#define endl "\n"
using namespace std;
using std::ofstream;

vector<ll> fact;
vector<ll> invfact;
vector<ll> primes;
vector<ll> sp;
ifstream in;

ll min(ll a,ll b){
    if(a<b)
    return a;
    return b;
}

ll max(ll a,ll b){
    if(a>b)
    return a;
    return b;
}

ll gcd(ll a,ll b){
    
    if(a==0)
    return b;
    if(b==0)
    return a;
    return gcd(b,a%b);
}

ll power(ll x,ll y){
    x=x%mod;
    if(x==1)
    return 1;
    if(y==0)
    return 1;
    if(y==1)
    return x;
    ll temp=power(x,y>>1);
    if(y&1){
        return ((((temp*temp)%mod)*x)%mod);
    }
    else
    return ((temp*temp)%mod);
}
 
void factorial(ll n){
    fact[0]=1;
    fact[1]=1;
    for(ll i=2;i<=n;i++)
    fact[i]=(fact[i-1]*(i%mod))%mod;
    return;
}
 
ll inv(ll n){
    return power(n,mod-2);
}
 
ll ncr(ll n,ll r){
    if(r>n || r<0 || n<0)
    return 0;
    return ((((fact[n]*invfact[n-r])%mod)*invfact[r])%mod);
}

ll npr(ll n,ll r){
    if(r>n || r<0 || n<0)
    return 0;
    return ((fact[n]*invfact[n-r])%mod);
}
 
void find_primes(ll n){
    bool isprime[n+1];
    for(ll i=0;i<=n;i++)
    isprime[i]=1;
    isprime[0]=0;
    isprime[1]=0;
    for(ll i=2;i<=n;i++){
        if(isprime[i]){
            for(ll j=i*i;j<=n;j+=i){
                isprime[j]=0;
            }
        }
    }
    for(ll i=0;i<=n;i++){
        if(isprime[i]){
            primes.push_back(i);
        }
    }
    return;
}
 
void find_fact(ll n){
    for(ll i=0;i<=n;i++){
        sp[i]=i;
    }
    for(auto x:primes){
        for(ll i=x*2;i<=n;i+=x){
            sp[i]=min(sp[i],x);
        }
    }
    return;
}

void kmp(string s,vector<ll> &pi) {
    ll n = s.size();
    pi[0]=0;
    for (ll i = 1; i < n; i++) {
        ll j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return;
}


struct edge{
    ll u1;
    ll u2;
    ll cap;
    ll flow;
};

vector<vector<ll> >adj;
vector<edge> elist;
vector<ll> dist;

bool bfs(ll src,ll sink){
    ll n=adj.size()-1;
    vector<bool> vis(n+1,0);
    vis[src]=1;
    dist[src]=0;
    queue<ll> q;
    q.push(src);
    ll level=1;
    while(!q.empty()){
        ll k=q.size();
        for(ll i=0;i<k;i++){
            ll x=q.front();
            q.pop();
            for(auto e:adj[x]){
                ll y=elist[e].u2;
                if(!vis[y] && elist[e].flow<elist[e].cap){
                    vis[y]=1;
                    dist[y]=level;
                    q.push(y);
                }
            }
        }
        level++;
    }
    if(dist[sink]==-1)
    return 0;
    return 1;
}

ll block(ll src,ll sink,vector<ll> &start,ll pushed){
    if(pushed==0)
    return 0;
    if(src==sink)
    return pushed;
    for(;start[src]<adj[src].size();start[src]++){
        edge e=elist[adj[src][start[src]]];
        if(e.flow<e.cap && dist[e.u2]==dist[e.u1]+1){
            ll temp=block(e.u2,sink,start,min(pushed,e.cap-e.flow));
            if(temp>0){
                elist[adj[src][start[src]]].flow+=temp;
                elist[adj[src][start[src]]^1].flow-=temp;
                return temp;
            }
        }
    }
    return 0;
}

ll dinc(ll src,ll sink){
    ll ans=0;
    ll n=adj.size()-1;
    dist.resize(n+1,-1);
    while(bfs(src,sink)){
        vector<ll> start(n+1,0);
        ll temp;
        while((temp=block(src,sink,start,inf))>0){
            ans+=temp;
        } 
        for(ll i=1;i<=n;i++)
        dist[i]=-1;
    }
    return ans;
}

void solve(){
    ll n,m;
    cin>>n>>m;
    adj.clear();
    elist.clear();
    adj.resize(n+1);
    vector<vector<ll> >mat(n+1,vector<ll>(n+1,-1));
    ll cnt=0;
    for(ll i=0;i<m;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        if(mat[a][b]==-1){
            mat[a][b]=cnt;
            mat[b][a]=cnt+1;
            adj[a].push_back(cnt);
            adj[b].push_back(cnt+1);
            edge e;
            e.u1=a;
            e.u2=b;
            e.cap=c;
            e.flow=0;
            elist.push_back(e);
            swap(e.u1,e.u2);
            e.cap=0;
            elist.push_back(e);
            cnt+=2;
        }
        else{
            elist[mat[a][b]].cap+=c;
        }
    }
    ll ans=dinc(1,n);
    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    /*ll n1=6000;
    fact.resize(n1+1);
    factorial(n1);

    invfact.resize(n1+1);
    invfact[n1]=inv(fact[n1]);
    for(ll i=n1-1;i>=0;i--)
    invfact[i]=(invfact[i+1]*((i+1)%mod))%mod;*/

    

    /*ll n2=1000;
    find_primes(n2);
    
    ll n3=100000;
    sp.resize(n3+1);
    find_fact(n3);*/
    ll t;
    //cin>>t;
    t=1;
    while(t--) solve();
    
} 
 
 



