#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf INT_MAX
#define minf INT_MIN
#define mod 1000000007
using namespace std;
ll max(ll a,ll b){
    if(a>b)
    return a;
    return b;
}
struct node{
    ll pre=0;
    ll suf=0;
    ll sum=0;
    ll sub=0;
};

ll n,m;
vector<ll> v;
vector<node> seg;
node merge(node n1,node n2){
    node ans;
    ans.sum=n1.sum+n2.sum;
    ans.pre=max(n1.pre,n1.sum+n2.pre);
    ans.suf=max(n2.suf,n2.sum+n1.suf);
    ans.sub=max(max(max(n1.sub,n2.sub),n1.suf+n2.pre),0);
    return ans;
}
void build(ll i,ll tl,ll tr){
    if(tl==tr){
        seg[i].sum=seg[i].pre=seg[i].suf=v[tl];
        seg[i].sub=max(0,v[tl]);
        return;
    }
    ll c=i<<1;
    ll tm=(tl+tr)>>1;
    build(c+1,tl,tm);
    build(c+2,tm+1,tr);
    seg[i]=merge(seg[c+1],seg[c+2]);
    return;
}

void update(ll i,ll tl,ll tr,ll j,ll u){
    if(tl==tr){
        seg[i].pre=seg[i].suf=seg[i].sum=u;
        seg[i].sub=max(0,u);
        return;
    }
    ll tm=(tl+tr)>>1;
    ll c=i<<1;
    if(j<=tm){
        update(c+1,tl,tm,j,u);
        seg[i]=merge(seg[c+1],seg[c+2]);
        return;
    }
    update(c+2,tm+1,tr,j,u);
    seg[i]=merge(seg[c+1],seg[c+2]);
    return;
}

node query(ll i,ll tl,ll tr,ll rl,ll rr){
    if(rl>rr||tl>rr||tr<rl){
        node nod;
        nod.pre=nod.suf=nod.sum=nod.sub=0;
        return nod;
    }
    ll c=i<<1;
    ll tm=(tl+tr)>>1;
    if(tl>=rl && tr<=rr){
        return seg[i];
    }
    return merge(query(c+1,tl,tm,rl,min(rr,tm)),query(c+2,tm+1,tr,max(tm+1,rl),rr));
}

void solve(){
    v.clear();
    seg.clear();
    cin>>n>>m;
    v.resize(n);
    seg.resize(4*n);
    for(ll i=0;i<n;i++){
        cin>>v[i];
    }
    build(0,0,n-1);
    for(ll i=0;i<m;i++){
        ll k,x;
        cin>>k>>x;
        update(0,0,n-1,k-1,x);
        cout<<seg[0].sub<<endl;
    }

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    t=1;
    while(t--) solve();
} 


