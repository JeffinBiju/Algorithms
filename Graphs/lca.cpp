#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <math.h>
#define ll long long
#define inf INT_MAX
#define minf INT_MIN
#define mod 1000000007
//#include "stdc++.h"
using namespace std;

void dfs(ll u,ll p,vector<vector<ll> >&adj,vector<ll> &par,ll &tim,vector<ll> &tin,vector<ll> &tout,ll d,vector<ll> &dist){
    par[u]=p;
    tin[u]=tim;
    tim++;
    dist[u]=d;
    for(auto x:adj[u]){
        if(x!=p)
        dfs(x,u,adj,par,tim,tin,tout,d+1,dist);
    }
    tout[u]=tim;
    tim++;
    return;
}

bool is_anc(ll a,ll b,vector<ll> &tin,vector<ll> &tout){
    if(tin[a]<=tin[b] && tout[a]>=tout[b])
    return 1;
    return 0;
}

ll lca(ll a,ll b,vector<ll>&tin,vector<ll>&tout,vector<vector<ll> >&dp){
    if(is_anc(a,b,tin,tout))
    return a;
    if(is_anc(b,a,tin,tout))
    return b;
    ll k=dp[1].size()-1;
    for(ll i=k;i>=0;i--){
        if(!is_anc(dp[a][i],b,tin,tout))
        a=dp[a][i];
    }
    return dp[a][0];
}

void solve(){
    ll n,q;
    cin>>n>>q;
    vector<vector<ll> >adj(n+1);
    for(ll i=1;i<n;i++){
        ll a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ll k=ceil(log2(n));
    vector<vector<ll> > dp(n+1,vector<ll>(k+1));
    vector<ll> par(n+1);
    ll tim=1;
    vector<ll> tin(n+1);
    vector<ll> tout(n+1);
    vector<ll> dist(n+1);
    dfs(1,1,adj,par,tim,tin,tout,0,dist);
    for(ll i=1;i<=n;i++)
    dp[i][0]=par[i];
    for(ll i=1;i<=k;i++)
    for(ll j=1;j<=n;j++)
    dp[j][i]=dp[dp[j][i-1]][i-1];
    for(ll i=0;i<q;i++){
        ll a,b;
        cin>>a>>b;
        ll c=lca(a,b,tin,tout,dp);
        cout<<(dist[a]+dist[b]-2*dist[c])<<endl;
    }
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    t=1;
    while(t--) solve();
} 
