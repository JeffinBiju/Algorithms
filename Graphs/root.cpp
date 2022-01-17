// Change mod in #define mod 

#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf 9223372036854775807
#define minf -9223372036854775808
#define mod 330301441
using namespace std;

ll power(ll x,ll y){
    x=x%mod;
    if(x==1)
    return 1;
    if(y==0)
    return 1;
    if(y==1)
    return x;
    ll temp=power(x,y>>1);
    if(y&1){
        return ((((temp*temp)%mod)*x)%mod);
    }
    else
    return ((temp*temp)%mod);
}

ll inv(ll n){
    return power(n,mod-2);
}

ll generator (ll p) {
    vector<ll> fact;
    ll phi = p-1,  n = phi;
    for (ll i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (ll res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= power (res, phi / fact[i]) != 1;
        if (ok)  return res;
    }
    return -1;
}

void solve(){
    cout<<generator(mod)<<endl;
    cout<<inv(generator(mod))<<endl;
}
 
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    //cin>>t;
    t=1;
    while(t--) solve();
} 