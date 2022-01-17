#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#define ll long long
#define inf 9223372036854775807
#define minf -9223372036854775808
#define mod (1000*1000*1000+7)
#define endl "\n"
#define pb push_back
#define mk make_pair
using namespace std;


vector<ll> fact;
vector<ll> invfact;
vector<ll> primes;
vector<ll> sp;


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
void solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    ll n1=5e5;
    fact.resize(n1+1);
    factorial(n1);

    invfact.resize(n1+1);
    invfact[n1]=inv(fact[n1]);
    for(ll i=n1-1;i>=0;i--)
    invfact[i]=(invfact[i+1]*((i+1)%mod))%mod;

    /*ll n2=1000;
    find_primes(n2);
    
    ll n3=100000;
    sp.resize(n3+1);
    find_fact(n3);*/

    ll t;
    cin>>t;
    while(t--) solve();
    
} 
 
 



