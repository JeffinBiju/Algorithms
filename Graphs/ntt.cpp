// Change mod and G. Remember to init() in main.

#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf 9223372036854775807
#define minf -9223372036854775808
#define mod 998244353

#define G  3
//#define root_1 28448323
//#define root_pw  (1 << 18)

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

vector<ll> gpow(30);
vector<ll> invgpow(30);

void init(){
    ll where = (mod - 1) / 2, invg = power(G, mod - 2);
    ll idx = 0;
    while (where % 2 == 0) {
        idx++;
        gpow[idx] = power(G, where);
        invgpow[idx] = power(invg, where);
        where /= 2;
    }
}

void ntt(vector<ll> &a, ll n, ll sign) {
    for (ll i = n >> 1, j = 1; j < n; j++) {
        if (i < j) swap(a[i], a[j]);
        ll k = n >> 1;
        while (k & i) {
            i ^= k;
            k >>= 1;
        }
        i ^= k;
    }
    for (ll l = 2, idx = 1; l <= n; l <<= 1, idx++) {
        ll omega = (sign == 1) ? gpow[idx] : invgpow[idx];
        for (ll i = 0; i < n; i += l) {
            ll value = 1;
            for (ll j = i; j < i + (l>>1); j++) {
                ll u = a[j], v = a[j + (l>>1)] * value % mod;
                a[j] = (u + v); a[j] = (a[j] >= mod) ? a[j] - mod : a[j];
                a[j + (l>>1)] = (u - v); a[j + (l>>1)] = (a[j + (l>>1)] < 0) ? a[j + (l>>1)] + mod : a[j + (l>>1)];
                value = value * omega % mod;
            }
        }
    }
    if (sign == -1) {
        const ll x = power(n, mod - 2);
        for (ll i = 0; i < n; i++) {
            a[i] = a[i] * x % mod;
        }
    }
}
 
vector<ll> multiply(vector<ll> &a1, vector<ll> &b1) {
    vector<ll> a=a1;
    vector<ll> b=b1;
    ll na=a.size();
    ll nb=b.size();
    ll n = 1; while (n < na + nb - 1) n <<= 1;
    a.resize(n);
    b.resize(n);
    for (ll i = na; i < n; i++) {
        a[i] = 0;
    }
    for (ll i = nb; i < n; i++) {
        b[i] = 0;
    }
 
    ntt(a, n, +1); ntt(b, n, +1);
    for (ll i = 0; i < n; i++) {
        a[i] = a[i] * b[i] % mod;
    }
    ntt(a, n, -1);
    for (ll i = na + nb - 1; i < n; i++) {
        a[i] = 0;
    }
    return a;
}

void solve(){
    vector<ll> v1;
    vector<ll> v2;
    v1.push_back(1);
    v1.push_back(1);
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(1);
    vector<ll> ans=multiply(v1,v2);
    for(auto x:ans)
    cout<<x<<" ";
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    //cin>>t;
    t=1;
    init();
    while(t--) solve();
} 
 
 


