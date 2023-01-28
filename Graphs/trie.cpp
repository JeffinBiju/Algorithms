#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#define ll long long
#define mod (998244353)
#define inf 9223372036854775807
//#define minf -9223372036854775808
#define minf -1e17
//#define endl "\n"
#define pb push_back
#define mk make_pair
using namespace std;

ll cur=1;
vector<vector<ll> > adj; //trie
vector<ll> v;   //value at each node in trie. Used for deleting strings etc.

void add(string &s, ll i, ll p){
    v[p]++;
    if(i>=s.size())
    return;
    if(adj[p][s[i]-'a']!=-1){
        add(s,i+1,adj[p][s[i]-'a']);
    }
    else{
        adj[p][s[i]-'a']=cur;
        cur++;
        add(s,i+1,adj[p][s[i]-'a']);
    }
}

ll search(string &s, ll i, ll p){
    if(i>=s.size())
    return i;
    if(adj[p][s[i]-'a']!=-1 && v[adj[p][s[i]-'a']]>1){
        return search(s,i+1,adj[p][s[i]-'a']);
    }
    else{
        return i;
    }
    return i;
}

void solve(){
    ll n;
    cin>>n;
    vector<string> temp(n);
    ll sum=0;
    for(ll i=0;i<n;i++){
        cin>>temp[i];
        sum+=temp[i].size();
    }
    adj.resize(sum+5,vector<ll>(26,-1));
    v.resize(sum+5,0);
    for(ll i=0;i<n;i++){
        add(temp[i],0,0);
    }
    for(ll i=0;i<n;i++){
        ll x=search(temp[i],0,0);
        cout<<x<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    t=1;
    while(t--) solve();
} 
 
 




