#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#define ll int
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
ofstream out;
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

map<ll,ll> mp;
vector<vector<ll> >vec;
vector<vector<ll> >adj;
vector<ll> v;
vector<ll> sub;
vector<ll> cnt;
vector<bool> over;  
ll ans;
ll n;

void dfs1(ll u,ll p){
     sub[u]=1;
     for(auto x:adj[u]){
          if(x!=p){
               dfs1(x,u);
               sub[u]+=sub[x];
          }
     }
     return;
}

void dfs2(ll u,ll p,bool keep){
     ll maxi=-1;
     ll maxv=0;
     for(auto x:adj[u]){
          if(x!=p){
               if(sub[x]>maxv){
                    maxv=sub[x];
                    maxi=x;
               }
          }
     }
     for(auto x:adj[u]){
          if(x!=p && x!=maxi){
               dfs2(x,u,0);
          }
     }
     if(maxi!=-1){
          dfs2(maxi,u,1);
          swap(vec[u],vec[maxi]);
     }
     if(!over[v[u]]){
        vec[u].push_back(u);
        mp[v[u]]++;
        if(mp[v[u]]==cnt[v[u]]){
            over[v[u]]=1;
            mp.erase(v[u]);
        }
     }
     for(auto x:adj[u]){
          if(x!=p && x!=maxi){
               for(auto y:vec[x]){
                   if(!over[v[y]]){
                        vec[u].push_back(y);
                        mp[v[y]]++;
                        if(mp[v[y]]==cnt[v[y]]){
                            over[v[y]]=1;
                            mp.erase(v[y]);
                        }
                   }
               }
          }
     }
     /*out<<u<<endl;
     for(auto x:mp)
     out<<x.first<<" "<<x.second<<endl;*/
     if(mp.empty() && u!=1)
     ans++;
     if(!keep){
          for(auto x:vec[u]){
              if(!over[v[x]]){
                  mp[v[x]]--;
                  if(mp[v[x]]==0)
                  mp.erase(v[x]);
              }
          }
     }
     return;
}

void solve(ll t){
    
     ans=0;
     in>>n;
     v.resize(n+1);
     adj.resize(n+1);
     for(ll i=0;i<n-1;i++){
          ll u1,u2;
          in>>u1>>u2;
          adj[u1].push_back(u2);
          adj[u2].push_back(u1);
     }
     for(ll i=1;i<=n;i++)
     in>>v[i];
     cnt.resize(n+1,0);
     over.resize(n+1,0);
     for(ll i=1;i<=n;i++){
         cnt[i]=0;
         over[i]=0;
     }
     for(ll i=1;i<=n;i++){
         cnt[v[i]]++;
     }
     vec.resize(n+1);
     sub.resize(n+1);
     dfs1(1,1);
     dfs2(1,1,0);
     out<<"Case #"<<t<<": "<<ans<<endl;
     over.clear();
     sub.clear();
     cnt.clear();
     mp.clear();
     adj.clear();
     vec.clear();
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

    out.open("output.txt");
    in.open("input.txt");

    ll t;
    in>>t;
    ll y=t;
    while(t--) solve(y-t);
    out.close();
    in.close();
} 
 
 



