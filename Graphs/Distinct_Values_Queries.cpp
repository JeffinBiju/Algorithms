#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf INT_MAX
#define minf INT_MIN
#define mod 1000000007
using namespace std;


vector<ll> v;
vector<ll> seg;

void update(ll i,ll tl,ll tr,ll j,ll val){
    if(tl==tr){
        seg[i]=val;
        return;
    }
    ll tm=(tl+tr)>>1;
    ll c=i<<1;
    if(j<=tm)
    update(c+1,tl,tm,j,val);
    else
    update(c+2,tm+1,tr,j,val);
    seg[i]=seg[c+1]+seg[c+2];
    return;
}

ll query(ll i,ll tl,ll tr,ll rl,ll rr){
    if(rl>rr||tl>rr||tr<rl){
        return 0;
    }
    ll c=i<<1;
    ll tm=(tl+tr)>>1;
    if(tl>=rl && tr<=rr){
        return seg[i];
    }
    return query(c+1,tl,tm,rl,min(rr,tm))+query(c+2,tm+1,tr,max(tm+1,rl),rr);
}
struct qry{
    ll l;
    ll r;
    ll id;
    bool operator<(const qry& obj)const{
        return this->r<obj.r;
    }
};
void solve(){
    v.clear();
    seg.clear();
    ll n,q;
    cin>>n>>q;
    v.resize(n);
    seg.resize(4*n,0);
    for(ll i=0;i<n;i++){
        cin>>v[i];
    }
    vector<qry> v1(q);
    for(ll i=0;i<q;i++){
        qry q1;
        cin>>q1.l>>q1.r;
        q1.id=i;
        q1.l-=1;
        q1.r-=1;
        v1[i]=q1;
    }
    sort(v1.begin(),v1.end());
    ll right=-1;
    map<ll,ll> mp;
    vector<ll> ans(q);
    for(ll i=0;i<q;i++){
        while(right<v1[i].r){
            right++;
            if(mp.find(v[right])!=mp.end()){
                update(0,0,n-1,mp[v[right]],0);
                update(0,0,n-1,right,1);
                mp[v[right]]=right;
            }
            else{
                mp[v[right]]=right;
                update(0,0,n-1,right,1);
            }
        }
        ans[v1[i].id]=query(0,0,n-1,v1[i].l,v1[i].r);
    }
    for(ll i=0;i<q;i++){
        cout<<ans[i]<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    t=1;
    while(t--) solve();
} 


