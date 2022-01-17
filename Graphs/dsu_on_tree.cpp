#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#define ll long long
#define inf 9223372036854775807
#define minf -9223372036854775808
#define mod 1000000007
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

vector<ll> c;
vector<ll> sum;
vector<vector<ll> >vec;
vector<vector<ll> >adj;
vector<ll> v;
vector<ll> ans;
vector<ll> sub;
ll n,maxf;

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
     vec[u].push_back(u);
     c[v[u]]++;
     sum[c[v[u]]]+=v[u];
     sum[c[v[u]]-1]-=v[u];
     maxf=max(maxf,c[v[u]]);
     for(auto x:adj[u]){
          if(x!=p && x!=maxi){
               for(auto y:vec[x]){
                    vec[u].push_back(y);
                    c[v[y]]++;
                    sum[c[v[y]]]+=v[y];
                    sum[c[v[y]]-1]-=v[y];
                    maxf=max(maxf,c[v[y]]);
               }
          }
     }
     ans[u]=sum[maxf];
     if(!keep){
          for(auto x:vec[u]){
               sum[c[v[x]]]-=v[x];
               c[v[x]]--;
               sum[c[v[x]]]+=v[x];
          }
          maxf=0;
     }
     return;
}

void solve(){
     cin>>n;
     v.resize(n+1);
     for(ll i=1;i<=n;i++)
     cin>>v[i];
     adj.resize(n+1);
     for(ll i=0;i<n-1;i++){
          ll u1,u2;
          cin>>u1>>u2;
          adj[u1].push_back(u2);
          adj[u2].push_back(u1);
     }
     c.resize(n+1,0);
     sum.resize(n+1,0);
     vec.resize(n+1);
     ans.resize(n+1);
     sub.resize(n+1);
     maxf=0;
     dfs1(1,1);
     dfs2(1,1,0);
     for(ll i=1;i<=n;i++)
     cout<<ans[i]<<" ";
     cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    t=1;
    //cin>>t;
    //ll y=t;
    while(t--) solve();
} 
 
 



