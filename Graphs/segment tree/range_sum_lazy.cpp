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
//#include "stdc++.h"
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

vector<ll> v;
vector<ll> seg;
vector<ll> lazy;

void build(ll i,ll tl,ll tr){
    if(tl==tr){
        seg[i]=v[tl];
        return;
    }
    ll c=i<<1;
    ll tm=(tl+tr)>>1;
    build(c+1,tl,tm);
    build(c+2,tm+1,tr);
    seg[i]=seg[c+1]+seg[c+2];
}

void push(ll i,ll tl,ll tr){
    seg[i]+=(tr-tl+1)*lazy[i];
    if(tl!=tr){
        ll c=i<<1;
        lazy[c+1]+=lazy[i];
        lazy[c+2]+=lazy[i];
    }
    lazy[i]=0;
}

void update(ll i,ll tl,ll tr,ll rl,ll rr,ll x){
    push(i,tl,tr);
    if(tl>tr || rl>rr || rl>tr || rr<tl)
    return;
    if(tl>=rl && tr<=rr){
        lazy[i]=x;
        push(i,tl,tr);
        return;
    }
    ll c=i<<1;
    ll tm=(tl+tr)>>1;
    update(c+1,tl,tm,rl,min(rr,tm),x);
    update(c+2,tm+1,tr,max(rl,tm+1),rr,x);
    seg[i]=seg[c+1]+seg[c+2];
}
ll query(ll i,ll tl,ll tr,ll rl,ll rr){
    push(i,tl,tr);
    if(tl>tr || rl>rr || rl>tr || rr<tl)
    return 0;
    if(tl>=rl && tr<=rr){
        return seg[i];
    }
    ll c=i<<1;
    ll tm=(tl+tr)>>1;
    return query(c+1,tl,tm,rl,min(rr,tm))+query(c+2,tm+1,tr,max(rl,tm+1),rr);
}


void solve(){
     ll n;
     cin>>n;
     v.resize(n,0);
     for(ll i=0;i<n;i++)
     v[i]=0;
     seg.resize(4*n,0);
     for(ll i=0;i<4*n;i++)
     seg[i]=0;
     lazy.resize(4*n,0);
     for(ll i=0;i<4*n;i++)
     lazy[i]=0;
     /*for(ll i=0;i<n;i++)
     cin>>v[i];
     build(0,0,n-1);*/
     ll q;
     cin>>q;
     
     for(ll i=0;i<q;i++){
         ll temp;
         cin>>temp;
         if(temp==0){
             ll rl,rr,x;
             cin>>rl>>rr>>x;
             rl-=1;
             rr-=1;
             update(0,0,n-1,rl,rr,x);
         }
         else{
             ll rl,rr;
             cin>>rl>>rr;
             rl-=1;
             rr-=1;
             cout<<query(0,0,n-1,rl,rr)<<endl;
    
         }
     }

}

 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    //t=1;
    cin>>t;
    //ll y=t;
    while(t--) solve();
} 
 
 



