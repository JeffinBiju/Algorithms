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
 
ll max(ll a,ll b){
    if(a>b)
    return a;
    return b;
}
 
ll min(ll a,ll b){
    if(a<b)
    return a;
    return b;
}
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
ll dfs1(ll u,ll p,ll d,vector<vector<ll> >&adj,vector<ll> &par,vector<ll> &depth,vector<ll> &heavy){
    par[u]=p;
    depth[u]=d;
    heavy[u]=-1;
    ll sub=0;
    ll size=1;
    for(auto x:adj[u]){
        if(x!=p){
            ll temp=dfs1(x,u,d+1,adj,par,depth,heavy);
            size+=temp;
            if(temp>sub){
                sub=temp;
                heavy[u]=x;
            }
        }
    }
    return size;
}
void dfs2(ll u,ll  p,ll h,ll &cur,vector<vector<ll> >&adj,vector<ll> &heavy,vector<ll> &pos,vector<ll> &head){
    head[u]=h;
    pos[u]=cur;
    cur++;
    if(heavy[u]==-1)
    return;
    dfs2(heavy[u],u,h,cur,adj,heavy,pos,head);
    for(auto x:adj[u]){
        if(x!=p && x!=heavy[u]){
            dfs2(x,u,x,cur,adj,heavy,pos,head);
        }
    }
}
ll hld(ll a,ll b,vector<ll> &depth,vector<ll> &par,vector<ll> &pos,vector<ll> &head){
    ll ans=0;
    ll n=depth.size()-1;
    while(head[a]!=head[b]){
        if(depth[head[a]]>=depth[head[b]]){
            ans+=query(0,0,n-1,pos[head[a]],pos[a]);
            a=par[head[a]];
        }
        else{
            ans+=query(0,0,n-1,pos[head[b]],pos[b]);
            b=par[head[b]];
        }
    }
    if(depth[a]<=depth[b]){
        ans+=query(0,0,n-1,pos[a],pos[b]);
    }
    else{
        ans+=query(0,0,n-1,pos[b],pos[a]);
    }
    return ans;
}
void solve(){
    ll n,q;
    cin>>n>>q;
    vector<ll> val(n+1);
    for(ll i=1;i<=n;i++)
    cin>>val[i];
    vector<vector<ll> > adj(n+1);
    for(ll i=1;i<=n-1;i++){
        ll a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<ll> par(n+1);
    vector<ll> depth(n+1);
    vector<ll> heavy(n+1);
    dfs1(1,1,0,adj,par,depth,heavy);
    vector<ll> pos(n+1);
    vector<ll> head(n+1);
    ll cur=0;
    dfs2(1,1,1,cur,adj,heavy,pos,head);
    v.resize(n);
    seg.resize(4*n);
    for(ll i=1;i<=n;i++){
        v[pos[i]]=val[i];
    }
    build(0,0,n-1);
    for(ll i=0;i<q;i++){
        ll temp;
        cin>>temp;
        if(temp==1){
            ll s,x;
            cin>>s>>x;
            update(0,0,n-1,pos[s],x);
        }
        else{
            ll a;
            cin>>a;
            cout<<hld(1,a,depth,par,pos,head)<<" ";
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
 