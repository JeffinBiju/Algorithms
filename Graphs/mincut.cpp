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

ll min(ll a,ll b){
    if(a<b)
    return a;
    return b;
}

ll max(ll a,ll b){
    if(a>b)
    return a;
    return b;
}

struct edge{
    ll u1;
    ll u2;
    ll cap;
    ll flow;
};

vector<vector<ll> >adj;
vector<edge> elist;
vector<ll> dist;
vector<bool> reachable;

bool bfs(ll src,ll sink){
    ll n=adj.size()-1;
    vector<bool> vis(n+1,0);
    vis[src]=1;
    dist[src]=0;
    queue<ll> q;
    q.push(src);
    ll level=1;
    while(!q.empty()){
        ll k=q.size();
        for(ll i=0;i<k;i++){
            ll x=q.front();
            q.pop();
            for(auto e:adj[x]){
                ll y=elist[e].u2;
                if(!vis[y] && elist[e].flow<elist[e].cap){
                    vis[y]=1;
                    dist[y]=level;
                    q.push(y);
                }
            }
        }
        level++;
    }
    if(dist[sink]==-1)
    return 0;
    return 1;
}

ll block(ll src,ll sink,vector<ll> &start,ll pushed){
    if(pushed==0)
    return 0;
    if(src==sink)
    return pushed;
    for(;start[src]<adj[src].size();start[src]++){
        edge e=elist[adj[src][start[src]]];
        if(e.flow<e.cap && dist[e.u2]==dist[e.u1]+1){
            ll temp=block(e.u2,sink,start,min(pushed,e.cap-e.flow));
            if(temp>0){
                elist[adj[src][start[src]]].flow+=temp;
                elist[adj[src][start[src]]^1].flow-=temp;
                return temp;
            }
        }
    }
    return 0;
}

ll dinc(ll src,ll sink){
    ll ans=0;
    ll n=adj.size()-1;
    dist.resize(n+1,-1);
    while(bfs(src,sink)){
        vector<ll> start(n+1,0);
        ll temp;
        while((temp=block(src,sink,start,inf))>0){
            ans+=temp;
        } 
        for(ll i=1;i<=n;i++)
        dist[i]=-1;
    }
    return ans;
}
void dfs(ll u){
    reachable[u]=1;
    for(auto e:adj[u]){
        if(elist[e].flow<elist[e].cap && !reachable[elist[e].u2])
        dfs(elist[e].u2);
    }
}

void solve(){
    ll n,m;
    cin>>n>>m;
    adj.clear();
    elist.clear();
    adj.resize(n+1);
    vector<vector<ll> >mat(n+1,vector<ll>(n+1,-1));
    ll cnt=0;
    for(ll i=0;i<m;i++){
        ll a,b,c;
        cin>>a>>b;
        //capacity
        c=1;
        if(mat[a][b]==-1){
            mat[a][b]=cnt;
            mat[b][a]=cnt+1;
            adj[a].push_back(cnt);
            adj[b].push_back(cnt+1);
            edge e;
            e.u1=a;
            e.u2=b;
            //undirected
            e.cap=c;
            e.flow=0;
            elist.push_back(e);
            swap(e.u1,e.u2);
            elist.push_back(e);
            cnt+=2;
        }
        else{
            //undirected
            elist[mat[a][b]].cap+=c;
            elist[mat[b][a]].cap+=c;
        }
    }
    ll src=1;
    ll sink=n;
    ll ans=dinc(src,sink);
    reachable.resize(n+1,0);
    dfs(src);
    cout<<ans<<endl;
    for(ll i=0;i<elist.size();i+=2){
        if(reachable[elist[i].u1]!=reachable[elist[i].u2])
        cout<<elist[i].u1<<" "<<elist[i].u2<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    t=1;
    while(t--) solve();
    
} 
 
 



