#include "stdc++.h"

// multiply 2*2 matrices
void multiply(vector<int> v1,vector<int> v2,vector<int> &v3){
    v3[0]=v1[0]*v2[0]+v1[1]*v2[2];
    v3[1]=v1[0]*v2[1]+v1[1]*v2[3];
    v3[2]=v1[2]*v2[0]+v1[3]*v2[2];
    v3[3]=v1[2]*v2[1]+v1[3]*v2[3];
    return;
}
// matrix exponentiation (O(logn) approach)
void mat_exp(vector<int> base,int p, vector<int> &mat){
    
    if(p==0){
        mat[0]=1;
        mat[1]=0;
        mat[2]=0;
        mat[3]=1;
        return;
    }
    if(p==1){
        mat[0]=base[0];
        mat[1]=base[1];
        mat[2]=base[2];
        mat[3]=base[3];
        return;
    }
    vector<int> temp(4);
    mat_exp(base,p>>1,temp);
    if(p&1){
        multiply(temp,temp,mat);
        multiply(mat,base,mat);
        return;
    }
    else{
        multiply(temp,temp,mat);
        return;
    }
}
// find nth fibonacci number. (O(nlogn) approach using matrix exponentiation)
int fib(int n){
    if(n==0)
    return 0;
    vector<int> mat(4);
    vector<int> base(4);
    base[0]=1;
    base[1]=1;
    base[2]=1;
    base[3]=0;
    mat_exp(base,n-1,mat);
    return mat[0];
    // an=a(n-1)+a(n-2)
    //a(n-1)=a(n-1)+0*a(n-2)
    //a(n)=   |1 1|a(n-1)
    //a(n-1)  |1 0|a(n-2)

}
void solve(){
    int n;
    cin>>n;
    cout<<n<<"th fibonacci number= "<<fib(n)<<endl;
}

int main(){
    int t;
    cin>>t;
    while(t--)solve();
}