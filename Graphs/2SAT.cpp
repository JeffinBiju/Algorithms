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

vector<set<ll> >tadj;
vector<vector<ll> >adj;
vector<vector<ll> >radj;
vector<ll> order;
vector<bool> vis;
vector<ll> cmp;

ll nott(ll u,ll n){
    if(u<=n)
    return u+n;
    else
    return u-n;
}

void dfs1(ll u){
    vis[u]=1;
    for(auto x:radj[u])
    if(!vis[x])
    dfs1(x);
    order.push_back(u);
}

void dfs2(ll u,ll cur){
    cmp[u]=cur;
    for(auto x:adj[u])
    if(cmp[x]==-1)
    dfs2(x,cur);
}

void solve(){
    ll n,m;
    cin>>m>>n;
    tadj.clear();
    adj.clear();
    radj.clear();
    order.clear();
    vis.clear();
    cmp.clear();
    tadj.resize(2*n+1);
    adj.resize(2*n+1);
    radj.resize(2*n+1);
    vis.resize(2*n+1,0);
    cmp.resize(2*n+1,-1);
    for(ll i=0;i<m;i++){
        char c1,c2;
        ll u1,u2;
        cin>>c1>>u1>>c2>>u2;
        if(c1=='-')
        u1=nott(u1,n);
        if(c2=='-')
        u2=nott(u2,n);
        if(tadj[nott(u1,n)].find(u2)==tadj[nott(u1,n)].end() && abs(u1-u2)!=n){
            adj[nott(u1,n)].push_back(u2);
            tadj[nott(u1,n)].insert(u2);
            radj[u2].push_back(nott(u1,n));
            if(u1!=u2){
                adj[nott(u2,n)].push_back(u1);
                tadj[nott(u2,n)].insert(u1);
                radj[u1].push_back(nott(u2,n));
            }
        } 
    }
    
    for(ll i=1;i<=2*n;i++){
        if(!vis[i]){
            dfs1(i);
        }
    }
    reverse(order.begin(),order.end());

    ll cur=0;
    for(auto x:order){
        if(cmp[x]==-1){
            dfs2(x,cur);
            cur++;
        }
    }

    vector<bool> ans(n+1,0); 
    for(ll i=1;i<=n;i++){
        if(cmp[i]==cmp[i+n]){
            cout<<"IMPOSSIBLE"<<endl;
            return;
        }
        ans[i]=(cmp[i]>cmp[i+n])?0:1;
    }
    for(ll i=1;i<=n;i++)
    if(ans[i])
    cout<<"+ ";
    else
    cout<<"- ";
    cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    //cin>>t;
    t=1;
    while(t--) solve();
} 
 
 



