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
//#include "stdc++.h"
using namespace std;
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
 
void factorial(ll n,vector<ll> &fact){
    fact[0]=1;
    fact[1]=1;
    for(ll i=2;i<=n;i++)
    fact[i]=(fact[i-1]*(i%mod))%mod;
    return;
}
 
ll inv(ll n){
    return power(n,mod-2);
}
 
ll ncr(ll n,ll r,vector<ll> &fact,vector<ll> &invfact){
    if(r>n || r<0 || n<0)
    return 0;
    return ((((fact[n]*invfact[n-r])%mod)*invfact[r])%mod);
}
 
void find_primes(ll n,vector<ll> &primes){
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
 
void find_fact1(ll n,vector<ll> &primes,vector<unordered_map<ll,ll> > &primfact){
    vector<ll> cur(n+1);
    for(ll i=0;i<=n;i++){
        cur[i]=i;
    }
    for(auto x:primes){
        for(ll i=x;i<=n;i+=x){
            ll cnt=0;
            while(cur[i]%x==0){
                cur[i]/=x;
                cnt++;
            }
            primfact[i][x]=cnt;
        }
    }
    return;
}
void find_fact2(ll n,vector<ll> &primes,vector<ll> &sp){
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

void bfs(ll u,vector<vector<ll> >&adj,vector<ll> &dist){
    ll n=adj.size()-1;
    vector<bool> vis(n+1,0);
    vis[u]=1;
    dist[u]=0;
    queue<ll> q;
    q.push(u);
    ll level=1;
    while(!q.empty()){
        ll k=q.size();
        for(ll i=0;i<k;i++){
            ll x=q.front();
            q.pop();
            for(auto y:adj[x]){
                if(!vis[y]){
                    vis[y]=1;
                    dist[y]=level;
                    q.push(y);
                }
            }
        }
        level++;
    }
    return;
}
void dfs(ll u,ll p,vector<vector<ll> >&adj,vector<bool> &vis,set<pair<ll,ll> >&s,vector<ll> &tim,vector<ll>&low,ll &cur){
    vis[u]=1;
    tim[u]=cur;
    cur++;
    ll cnt=0;
    low[u]=tim[u];
    for(auto x:adj[u]){
        if(vis[x]){
            if(x!=p)
            low[u]=min(low[u],tim[x]);
        }
        else{
            cnt++;
            dfs(x,u,adj,vis,s,tim,low,cur);
            low[u]=min(low[u],low[x]);
        }
    }
    if(u!=p){
        if(low[u]>tim[p]){
            s.insert(make_pair(min(u,p),max(u,p)));
        }
    }
    return;
}

void solve(ll t){
     ll n,m;
     cin>>n>>m;
     vector<vector<ll> >adj(n+1);
     for(ll i=0;i<m;i++){
         ll u1,u2;
         cin>>u1>>u2;
         adj[u1].push_back(u2);
         adj[u2].push_back(u1);
     }
     vector<bool> vis(n+1,0);
     vector<ll> tim(n+1,0);
     vector<ll> low(n+1,n);
     set<pair<ll,ll> >s;
     ll cur=0;
     for(ll i=1;i<=n;i++){
         if(!vis[i]){
             dfs(i,i,adj,vis,s,tim,low,cur);
         }
     }
     cout<<"Caso #"<<t<<endl;
     if(s.empty()){
         cout<<"Sin bloqueos"<<endl;
         return;
     }
     cout<<s.size()<<endl;
     for(auto x:s){
         cout<<x.first<<" "<<x.second<<endl;
     }
}

 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    /*ll n1=10000;
    vector<ll> fact(n1+1);
    factorial(n1,fact);

    vector<ll> invfact(n1+1);
    invfact[n1]=inv(fact[n1]);
    for(ll i=n1-1;i>=0;i--)
    invfact[i]=(invfact[i+1]*((i+1)%mod))%mod;*/
    
    /*vector<ll> primes;
    ll n2=1000;
    find_primes(n2,primes);*/
 
    /*ll n3=100000;
    vector<unordered_map<ll,ll> >primfact(n3+1);
    find_fact1(n3,primes,primfact);*/
 
    
    /*ll n3=100000;
    vector<ll>sp(n3+1);
    find_fact2(n3,primes,sp);*/
    
    
    ll t;
    //t=1;
    cin>>t;
    ll y=t;
    while(t--) solve(y-t);
} 
 
 



