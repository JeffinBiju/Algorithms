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
    ll to;
    ll from;
    node(ll d,ll to,ll from){
        this->from=from;
        this->to=to;
        this->d=d;
    }
    bool operator<(const node&obj)const{
        if(this->d!=obj.d)
        return this->d<obj.d;
        return this->to<obj.to;
    }
};
void dijkstra(ll u,ll k,vector<vector<pair<ll,ll> > >&adj,vector<vector<ll> > &dist){

    ll n=adj.size()-1;
    vector<bool> b(n+1,0);
    multiset<pair<ll,ll> >s;
    for(ll i=1;i<=n;i++){
        if(i==u)
        s.insert(make_pair(0,i));
        else
        s.insert(make_pair(inf,i));
    }
    while(!s.empty()){
        pair<ll,ll> p=*(s.begin());
        s.erase(s.begin());
        ll v1=p.second;
        ll d1=p.first;
        if(d1==inf)
        break;
        if(dist[v1].size()==k)
        continue;
        dist[v1].push_back(d1);
        for(auto x:adj[v1]){
            ll v2=x.first;
            ll e=x.second;
            s.insert(make_pair(e+d1,v2));
        }
    }
}
  
void solve(){
    ll n,m,k;
    cin>>n>>m>>k;
    vector<vector<pair<ll,ll> > > adj(n+1);
    for(ll i=0;i<m;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back(make_pair(b,c));
    }
    vector<vector<ll> > dist(n+1);
    dijkstra(1,k,adj,dist);
    for(ll i=0;i<k;i++){
        cout<<dist[n][i]<<" ";
    }
    cout<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
} 