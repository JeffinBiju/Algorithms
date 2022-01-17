#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf ((1LL<<31)-1)
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
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int add) {
    if (l > r)
        return;
    if (l == tl && r == tr) {
        t[v] += add;
    } else {
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), add);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
    }
}

int get(int v, int tl, int tr, int pos) {
    if (tl == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return t[v] + get(v*2, tl, tm, pos);
    else
        return t[v] + get(v*2+1, tm+1, tr, pos);
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
void hld1(ll a,ll b,vector<ll> &depth,vector<ll> &par,vector<ll> &pos,vector<ll> &head){
    ll n=depth.size()-1;
    while(head[a]!=head[b]){
        if(depth[head[a]]>=depth[head[b]]){
            update(0,0,n-1,pos[head[a]],pos[a]);
            a=par[head[a]];
        }
        else{
            update(0,0,n-1,pos[head[b]],pos[b]);
            b=par[head[b]];
        }
    }
    if(depth[a]<=depth[b]){
        update(0,0,n-1,pos[a],pos[b]);
    }
    else{
        update(0,0,n-1,pos[b],pos[a]);
    }
}

ll hld2(ll a,ll b,vector<ll> &depth,vector<ll> &par,vector<ll> &pos,vector<ll> &head){
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
    vector<vector<ll> > adj(n+1);
    for(ll i=1;i<=n-1;i++){
        ll a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<ll> val(n+1);
    for(ll i=1;i<=n;i++)
    cin>>val[i];
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
        ll a,u,v;
        cin>>a>>u>>v;
        if(a==1){
            hld1(u,v,depth,par,pos,head);
        }
        else{
            cout<<hld2(u,v,depth,par,pos,head)<<endl;
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
 