#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf 9223372036854775807
#define minf INT_MIN
#define mod 1000000007
using namespace std;

ll min(ll a,ll b){
    if(a<b)
    return a;
    return b;
}
struct node{
    ll d;
    ll from;
    ll to;
    node(){
        this->d=0;
        this->from=0;
        this->to=0;
    }
    node(ll d,ll from,ll to){
        this->d=d;
        this->from=from;
        this->to=to;
    }
    bool operator<(const node&obj)const{
        return this->d<obj.d;
    }
};
void dijkstra(ll u,vector<vector<pair<ll,ll> > >&adj,vector<ll> &dist,vector<ll> &par){

    ll n=adj.size()-1;
    vector<bool> b(n+1,0);
    multiset<node>s;
    for(ll i=1;i<=n;i++){
        if(i==u)
        s.insert(node(0,-1,u));
        else
        s.insert(node(inf,-1,i));
    }
    while(!s.empty()){
        node temp=*(s.begin());
        s.erase(s.begin());
        ll d1=temp.d;
        ll p1=temp.from;
        ll v1=temp.to;
        if(d1==inf)
        break;
        if(b[v1])
        continue;
        dist[v1]=d1;
        par[v1]=p1;
        b[v1]=1;
        for(auto x:adj[v1]){
            ll v2=x.first;
            ll e=x.second;
            s.insert(node(d1+e,v1,v2));
        }
    }
}
  
void solve(){
    ll n,m;
    cin>>n>>m;
    vector<vector<pair<ll,ll> > > adj(n+1);
    for(ll i=0;i<m;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back(make_pair(b,c));
    }
    vector<ll> dist(n+1,inf);
    vector<ll> par(n+1);
    dijkstra(1,adj,dist,par);
    for(ll i=1;i<=n;i++){
        cout<<dist[i]<<" ";
    }
    cout<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
} 