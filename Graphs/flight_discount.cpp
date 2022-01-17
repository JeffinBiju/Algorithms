#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf 9223372036854775807
#define minf 
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
void dijkstra(ll u,vector<map<ll,ll> >&adj,vector<ll> &dist,vector<ll> &par){
    ll n=adj.size()-1;
    vector<bool> b(n+1,0);
    fill(dist.begin(),dist.end(),inf);
    dist[u]=0;
    fill(par.begin(),par.end(),0);
    set<node> s;
    for(ll i=1;i<=n;i++){
        if(i!=u){
            s.insert(node(inf,i,0));
        }
        else{
            s.insert(node(0,u,0));
        }
    }
    while(!s.empty()){
        node temp=*(s.begin());
        if(temp.d==inf){
            break;
        }
        s.erase(s.begin());
        ll v1=temp.to;
        ll d1=temp.d;
        b[v1]=1;
        for(auto x:adj[v1]){
            ll v2=x.first;
            ll e=x.second;
            if(!b[v2]){
                s.erase(s.find(node(dist[v2],v2,par[v2])));
                if(dist[v2]>dist[v1]+e){
                    dist[v2]=dist[v1]+e;
                    par[v2]=v1;
                }
                s.insert(node(dist[v2],v2,par[v2]));
            }
        }
    }
    return;
}
  
void solve(){
    ll n,m;
    cin>>n>>m;
    vector<map<ll,ll> > adj(n+1);
    vector<map<ll,ll> >radj(n+1);
    for(ll i=0;i<m;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        if(adj[a].find(b)!=adj[a].end())
        adj[a][b]=min(adj[a][b],c);
        else
        adj[a][b]=c;
        if(radj[b].find(a)!=radj[b].end())
        radj[b][a]=min(radj[b][a],c);
        else
        radj[b][a]=c;
    }
    vector<ll> dist(n+1);
    vector<ll> rdist(n+1);
    vector<ll> par(n+1);
    vector<ll> rpar(n+1);
    dijkstra(1,adj,dist,par);
    dijkstra(n,radj,rdist,rpar);
    ll ans=inf;
    for(ll i=1;i<=n;i++){
        for(auto x:adj[i]){
            ll u2=x.first;
            ll e=x.second;
            if(dist[i]!=inf && rdist[u2]!=inf)
            ans=min(ans,dist[i]+e/2+rdist[u2]);
        }
    }
    cout<<ans<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
} 