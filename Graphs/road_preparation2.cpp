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

struct edge{
    ll w;
    ll u1;
    ll u2;
    edge(){
        this->w=0;
        this->u1=0;
        this->u2=0;
    }
    bool operator<(const edge& obj)const{
        return this->w<obj.w;
    }
};

vector<ll> parent;
vector<ll> ranks;


ll find(ll u){
    if(u==parent[u])
    return u;
    parent[u]=find(parent[u]);
    return parent[u];
}

void uni(ll u1,ll u2){
    ll p1=find(u1);
    ll p2=find(u2);
    if(p1==p2)
    return;
    if(ranks[p1]==ranks[p2]){
        parent[p2]=p1;
        ranks[p1]++;
        return;
    }
    if(ranks[p1]>ranks[p2])
    parent[p2]=p1;
    else
    parent[p1]=p2;
}

ll kruskal(vector<edge> &v,vector<vector<pair<ll,ll> > >&mst){
    ll m=v.size();
    ll n=mst.size()-1;
    parent.resize(n+1);
    ranks.resize(n+1,1);
    for(ll i=1;i<=n;i++)
    parent[i]=i;
    vector<bool>b(n+1,0);
    ll cost=0;
    sort(v.begin(),v.end());
    for(ll i=0;i<m;i++){
        ll u1=v[i].u1;
        ll u2=v[i].u2;
        ll w=v[i].w;
        if(find(u1)!=find(u2)){
            uni(u1,u2);
            cost+=w;
            b[u1]=b[u2]=1;
            mst[u1].push_back(make_pair(u2,w));
            mst[u2].push_back(make_pair(u1,w));
        }
    }
    ll root=find(1);
    for(ll i=2;i<=n;i++){
        if(find(i)!=root){
            return inf;
        }
    }
    return cost;
}

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<edge> v(m);
    for(ll i=0;i<m;i++){
        edge e;
        cin>>e.u1>>e.u2>>e.w;
        v.push_back(e);
    }
    vector<vector<pair<ll,ll> > >mst(n+1);
    ll cost=kruskal(v,mst);
    if(cost==inf)
    cout<<"IMPOSSIBLE"<<endl;
    else
    cout<<cost<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    t=1;
    while(t--) solve();
} 


