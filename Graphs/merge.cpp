#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf 9223372036854775807
#define minf -9223372036854775808
#define mod 1000000007
//#include "stdc++.h"
using namespace std;

ll merge(vector<ll>&v,ll s,ll e){
    if(s==e){
        return 0;
    }
    ll m=(s+e)>>1;
    ll ans=0;
    ans+=merge(v,s,m);
    ans+=merge(v,m+1,e);
    vector<ll> temp(e-s+1);
    ll p1=s;
    ll p2=m+1;
    ll cur=0;
    while(cur<e-s+1){
        if(p1>m || (p2<=e && v[p1]>v[p2])){
           temp[cur]=v[p2];
           p2++;
           ans+=(m-p1+1);
        }
        else{
            temp[cur]=v[p1];
            p1++;
        }
        cur++;
    }
    for(ll i=0;i<e-s+1;i++){
        v[s+i]=temp[i];
    }
    return ans;
}
void solve(){
    ll n;
    cin>>n;
    vector<ll> v(n);
    for(ll i=0;i<n;i++){
        cin>>v[i];
    }
    cout<<merge(v,0,n-1)<<endl;
}
 
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    /*ll n1=300000;
    vector<ll> fact(n1+1);
    factorial(n1,fact);*/
    
    
    /*vector<ll> primes;
    ll n2=10000;
    find_primes(n2,primes);*/
 
    /*ll n3=100000;
    vector<unordered_map<ll,ll> >primfact(n3+1);
    find_fact1(n3,primes,primfact);*/
 
    
    /*ll n3=100000;
    vector<ll>sp(n3+1);
    find_fact2(n3,primes,sp);*/
    
    
 
    ll t;
    t=1;
    while(t--) solve();
} 
 
 




