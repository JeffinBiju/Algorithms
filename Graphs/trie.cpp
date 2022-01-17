#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#define ll long long
#define inf 9223372036854775807
#define minf -9223372036854775808
#define mod 1000000007
//#define endl "\n"
//#include "stdc++.h"
using namespace std;

struct node{
    node* c[26];
    bool end;
    node(){
        for(ll i=0;i<26;i++)
        c[i]=NULL;
        end=0;
    }
};

void insert(node* root,string &s){
    for(ll i=0;i<s.size();i++){
        ll id=s[i]-'a';
        if(!root->c[id])
        root->c[id]=new node;
        root=root->c[id];
    }
    root->end=1;
}

bool search(node* root,string &s){
    for(ll i=0;i<s.size();i++){
        ll id=s[i]-'a';
        if(!root->c[id])
        return 0;
        root=root->c[id];
    }
    if(root->end)
    return 1;
    return 0;
}

void solve(){
    node* root=new node;
    ll q;
    cin>>q;
    for(ll i=0;i<q;i++){
        ll temp;
        string s;
        cin>>temp>>s;
        if(temp==0){
            insert(root,s);
        }
        else{
            if(search(root,s))
            cout<<"YES"<<endl;
            else
            cout<<"NO"<<endl;
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
 
 


