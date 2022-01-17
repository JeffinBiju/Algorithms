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

void solve(){
    ll n,m,k;
    cin>>n>>m>>k;
    adj.clear();
    elist.clear();
    adj.resize(n+m+3);
    ll cnt=0;
    for(ll i=0;i<k;i++){
        ll a,b;
        cin>>a>>b;
        b+=n;
        edge e;
        e.u1=a;
        e.u2=b;
        e.cap=1;
        e.flow=0;
        elist.push_back(e);
        e.cap=0;
        swap(e.u1,e.u2);
        elist.push_back(e);
        adj[a].push_back(cnt);
        adj[b].push_back(cnt+1);
        cnt+=2;
    }
    ll src=n+m+1;
    ll sink=n+m+2;
    for(ll i=1;i<=n;i++){
        edge e;
        e.u1=src;
        e.u2=i;
        e.cap=1;
        e.flow=0;
        elist.push_back(e);
        e.cap=0;
        swap(e.u1,e.u2);
        elist.push_back(e);
        adj[src].push_back(cnt);
        adj[i].push_back(cnt+1);
        cnt+=2;
    }
    for(ll i=1;i<=m;i++){
        edge e;
        e.u1=i+n;
        e.u2=sink;
        e.cap=1;
        e.flow=0;
        elist.push_back(e);
        e.cap=0;
        swap(e.u1,e.u2);
        elist.push_back(e);
        adj[i+n].push_back(cnt);
        adj[sink].push_back(cnt+1);
        cnt+=2;
    }
    ll ans=dinc(src,sink);
    cout<<ans<<endl;
    for(auto e:elist){
        if(e.flow==1 && e.u1!=src && e.u2!=sink){
            cout<<e.u1<<" "<<e.u2-n<<endl;
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
 
 



