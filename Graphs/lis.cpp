#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#define ll long long
#define inf 9223372036854775807
#define minf -9223372036854775808
#define mod 1000000007
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
void LIS(vector<ll> &v,vector<ll> &seq){
    ll n=v.size();
    vector<ll> lis(n+1,-1);
    vector<ll> par(n,-1);
    lis[1]=0;
    for(ll i=1;i<n;i++){
        ll l=1;
        ll r=n;
        while(l<r){
            ll m=(l+r)/2+1;
            if(lis[m]==-1 || v[lis[m]]>=v[i])
            r=m-1;
            else
            l=m;
        }
        if(lis[l]==-1 || v[lis[l]]>=v[i]){
            lis[1]=i;
        }
        else{
            lis[l+1]=i;
            par[i]=lis[l];
        }
    }
    ll temp=0;
    for(ll i=1;i<=n;i++)
    if(lis[i]!=-1)
    temp=lis[i];
    while(temp!=-1){
        seq.push_back(v[temp]);
        temp=par[temp];
    }
    reverse(seq.begin(),seq.end());
    return;
}
void solve(){
    ll n;
    cin>>n;
    vector<ll> v(n);
    for(ll i=0;i<n;i++)
    cin>>v[i];
    vector<ll> seq;
    LIS(v,seq);
    cout<<seq.size()<<endl;
    for(auto x:seq)
    cout<<x<<" ";
    cout<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    while(t--) solve();
} 