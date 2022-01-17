#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf INT_MAX
#define minf INT_MIN
#define mod 1000000007
//#include "stdc++.h"
using namespace std;

vector<ll> v;
vector<ll> seg;

void build(ll i,ll tl,ll tr){
    if(tl==tr){
        seg[i]=v[tl];
        return;
    }
    ll c=i<<1;
    ll tm=(tl+tr)>>1;
    build(c+1,tl,tm);
    build(c+2,tm+1,tr);
    seg[i]=seg[c+1]+seg[c+2];
    return;
}

void update(ll i,ll tl,ll tr,ll j,ll x){
    if(tl==tr){
        seg[i]=x;
        return;
    }
    ll tm=(tl+tr)>>1;
    ll c=i<<1;
    if(j<=tm)
    update(c+1,tl,tm,j,x);
    else    
    update(c+2,tm+1,tr,j,x);
    seg[i]=seg[c+1]+seg[c+2];
    return;
}

ll query(ll i,ll tl,ll tr,ll rl,ll rr){
    if(rl>rr||tl>rr||tr<rl){
        return 0;
    }
    ll c=i<<1;
    ll tm=(tl+tr)>>1;
    if(tl>=rl && tr<=rr){
        return seg[i];
    }
    return query(c+1,tl,tm,rl,min(rr,tm))+query(c+2,tm+1,tr,max(tm+1,rl),rr);
}

void dfs(ll u,ll p,vector<vector<ll> > &adj,vector<ll> &tin,vector<ll> &tout,ll &tim){
    tin[u]=tim;
    tim++;
    for(auto x:adj[u]){
        if(x!=p){
            dfs(x,u,adj,tin,tout,tim);
        }
    }
    tout[u]=tim-1;
    return;
}

void solve(){
    ll n,q;
    cin>>n>>q;
    vector<ll> val(n+1);
    for(ll i=1;i<=n;i++)
    cin>>val[i];
    vector<vector<ll> >adj(n+1);
    for(ll i=0;i<n-1;i++){
        ll a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<ll> tin(n+1);
    vector<ll> tout(n+1);
    ll tim=0;
    dfs(1,1,adj,tin,tout,tim);
    v.resize(n);
    seg.resize(4*n);
    for(ll i=1;i<=n;i++)
    v[tin[i]]=val[i];
    build(0,0,n-1);
    for(ll i=0;i<q;i++){
        ll y;
        cin>>y;
        if(y==1){
            ll s,x;
            cin>>s>>x;
            update(0,0,n-1,tin[s],x);
        }
        else{
            ll s;
            cin>>s;
            cout<<query(0,0,n-1,tin[s],tout[s])<<endl;
        }
    }

}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    t=1;
    while(t--) solve();
} 
 
 

