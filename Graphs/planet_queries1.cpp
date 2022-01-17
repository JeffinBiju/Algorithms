#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf 9223372036854775807
#define minf INT_MIN
#define mod 1000000007
using namespace std;
ll bj(vector<vector<ll> >&dp,ll x,ll k){
    ll i=dp[0].size();
    for(ll j=i-1;j>=0;j--){
        if(k&(1<<j)){
            x=dp[x][j];
        }
    }
    return x;
}
void solve(){
    ll n,q;
    scanf("%lld %lld",&n,&q);
    ll m=30;
    vector<vector<ll> >dp(n+1,vector<ll>(m+1));
    for(ll i=1;i<=n;i++)
    scanf("%lld",&dp[i][0]);
    for(ll i=1;i<=m;i++)
    for(ll j=1;j<=n;j++)
    dp[j][i]=dp[dp[j][i-1]][i-1];
    for(ll i=0;i<q;i++){
        ll x,k;
        scanf("%lld %lld",&x,&k);
        printf("%lld\n",bj(dp,x,k));
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
} 