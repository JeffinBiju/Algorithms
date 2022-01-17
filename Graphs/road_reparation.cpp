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
ll find_mst(vector<vector<pair<ll,ll> > >&adj,vector<vector<pair<ll,ll> > >&mst){

    ll n=adj.size()-1;
    vector<bool> b(n+1,0);
    multiset<node>s;
    for(ll i=1;i<=n;i++){
        if(i==1)
        s.insert(node(0,-1,1));
        else
        s.insert(node(inf,-1,i));
    }
    ll cost=0;
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
        if(v1!=1){
            cost+=d1;
            mst[p1].push_back(make_pair(v1,d1));
            mst[v1].push_back(make_pair(p1,d1));
        }
        b[v1]=1;
        for(auto x:adj[v1]){
            ll v2=x.first;
            ll e=x.second;
            s.insert(node(e,v1,v2));
        }
    }
    for(ll i=1;i<=n;i++){
        if(!b[i])
        return inf;
    }
    return cost;
}
  
void solve(){
    ll n,m;
    cin>>n>>m;
    vector<vector<pair<ll,ll> > > adj(n+1);
    for(ll i=0;i<m;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back(make_pair(b,c));
        adj[b].push_back(make_pair(a,c));
    }
    vector<vector<pair<ll,ll> > >mst(n+1);
    ll cost=find_mst(adj,mst);
    if(cost==inf)
    cout<<"IMPOSSIBLE"<<endl;
    else
    cout<<cost<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
} 