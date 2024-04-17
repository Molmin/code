/**
 * @date: 2024.03.28
 * @problem: BZOJ4128
 * @tags: 数论, BSGS, 矩阵, 矩阵乘法
 */

#include<bits/stdc++.h>
using namespace std;

int n,p;

struct Matrix{
    vector<vector<int> > v;

    inline void read(int n){
        v.clear();
        for(int i=0;i<n;i++){
            vector<int> vec(n);
            for(int j=0;j<n;j++)
                scanf("%d",&vec[j]);
            v.push_back(vec);
        }
    }

    inline friend Matrix operator*(Matrix &a,Matrix &b){
        int n=a.v.size();
        Matrix ret;
        for(int i=0;i<n;i++){
            vector<int> vec(n);
            for(int j=0;j<n;j++){
                vec[j]=0;
                for(int k=0;k<n;k++)
                    vec[j]+=1ll*a.v[i][k]*b.v[k][j]%p,vec[j]%=p;
            }
            ret.v.push_back(vec);
        }
        return ret;
    }

    inline unsigned long long getHash(){
        int n=v.size();
        unsigned long long ret=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                ret=ret*998244353+v[i][j];
        return ret;
    }
}A,B;

Matrix power(Matrix A,int x){
    if(x==1)return A;
    Matrix B=power(A,x>>1);
    B=B*B;
    if(x&1)B=B*A;
    return B;
}

int main(){
    scanf("%d%d",&n,&p);
    A.read(n),B.read(n);
    int m=ceil(sqrt(p));
    unordered_map<unsigned long long,int> mp;
    for(int i=1;i<=m;i++)
        B=B*A,mp[B.getHash()]=i;
    A=power(A,m);
    Matrix now=A;
    for(int i=1;i<=m;i++){
        int ret=mp[now.getHash()];
        if(ret)return printf("%d\n",i*m-ret),0;
        now=now*A;
    }
    return 0;
}
