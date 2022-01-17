#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf INT_MAX
#define minf INT_MIN
#define mod 1000000007
using namespace std;

struct node{
    bool b1=0;
    bool b2=0;
    ll l1;
    ll l2;
    ll val;

};

ll n,q;
vector<ll> v;
vector<node> seg;

void build(ll i,ll tl,ll tr){
    if(tl>tr)
    return;
    if(tl==tr){
        seg[i].val=v[tl];
        return;
    }
    ll c=i<<1;
    ll m=(tl+tr)>>1;
    build(c+1,tl,m);
    build(c+2,m+1,tr);
    seg[i].val=seg[c+1].val+seg[c+2].val;
    return;
}

void push1(ll i,ll c){
    if(seg[i].b1){
        if(seg[c].b1){
            seg[c].l1+=seg[i].l1;
        }
        else if(seg[c].b2){
            seg[c].l2+=seg[i].l1;
        }
        else{
            seg[c].b1=1;
            seg[c].l1=seg[i].l1;
        }
    }
    if(seg[i].b2){
        seg[c].b1=0;
        seg[c].b2=1;
        seg[c].l2=seg[i].l2;
    }
}

void push(ll i,ll tl,ll tr){
    
    if(seg[i].b1){
        seg[i].val+=(tr-tl+1)*seg[i].l1;
        if(tl!=tr){
            ll c=i<<1;
            push1(i,c+1);
            push1(i,c+2);
        }
        seg[i].b1=0;
    }
    if(seg[i].b2){
        seg[i].val=(tr-tl+1)*(seg[i].l2);
        if(tl!=tr){
            ll c=i<<1;
            push1(i,c+1);
            push1(i,c+2);
        }
        seg[i].b2=0;
    }
    
}

void update(ll i,ll tl,ll tr,ll rl,ll rr,ll u,bool b){
    push(i,tl,tr);
    if(rl>rr||tl>rr||tr<rl){
        return;
    }
    ll c=i<<1;
    ll m=(tl+tr)>>1;
    if(tl>=rl && tr<=rr){
        if(b){
            seg[i].b1=1;
            seg[i].l1=u;
            push(i,tl,tr);
        }
        else{
            seg[i].b2=1;
            seg[i].l2=u;
            push(i,tl,tr);
        }
        return;
    }
    update(c+1,tl,m,rl,min(rr,m),u,b);
    update(c+2,m+1,tr,max(m+1,rl),rr,u,b);
    seg[i].val=seg[c+1].val+seg[c+2].val;
    return;
}

ll query(ll i,ll tl,ll tr,ll rl,ll rr){
    push(i,tl,tr);
    if(rl>rr||tl>rr||tr<rl){
        return 0;
    }
    ll c=i<<1;
    ll m=(tl+tr)>>1;
    if(tl>=rl && tr<=rr){
        return seg[i].val;
    }
    return query(c+1,tl,m,rl,min(rr,m))+query(c+2,m+1,tr,max(m+1,rl),rr);
}

void solve(){
    v.clear();
    seg.clear();
    cin>>n>>q;
    v.resize(n);
    seg.resize(4*n);
    for(ll i=0;i<n;i++){
        cin>>v[i];
    }
    build(0,0,n-1);
    for(ll i=0;i<q;i++){
        ll t;
        cin>>t;
        if(t==1){
            ll a,b,x;
            cin>>a>>b>>x;
            update(0,0,n-1,a-1,b-1,x,1);
        }
        if(t==2){
            ll a,b,x;
            cin>>a>>b>>x;
            update(0,0,n-1,a-1,b-1,x,0);
        }
        if(t==3){
            ll a,b;
            cin>>a>>b;
            cout<<query(0,0,n-1,a-1,b-1)<<endl;
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


