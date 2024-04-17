/**
 * @date: 2024.04.05
 * @problem: P1357
 * @tags: 动态规划, 矩阵, 矩阵乘法, 矩阵快速幂, 状态压缩动态规划
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

long long n; int m,k;

struct Matrix{
    int n,m;
    vector<vector<int> > data;
    inline void init(int _n,int _m){
        n=_n,m=_m;
        data.clear();
        vector<int> vec;
        for(int i=0;i<m;i++)
            vec.push_back(0);
        for(int i=0;i<n;i++)
            data.push_back(vec);
    }
    inline int val(int i,int j){
        return data[i][j];
    }
    inline int set(int i,int j,int val){
        return data[i][j]=val;
    }
    inline int add(int i,int j,int val){
        return data[i][j]=(data[i][j]+val)%mod;
    }
    inline Matrix operator*(Matrix S)const{
        if(m!=S.n)return{0,0,{}};
        Matrix res;
        res.n=n,res.m=S.m;
        for(int i=0;i<res.n;i++){
            vector<int> tmp;
            for(int j=0;j<res.m;j++){
                long long sum=0;
                for(int k=0;k<m;k++)
                    sum+=1ll*data[i][k]*S.val(k,j)%mod;
                tmp.push_back(sum%mod);
            }
            res.data.push_back(tmp);
        }
        return res;
    }
};

Matrix power(Matrix x,long long y){
    if(y==1)return x;
    Matrix tmp=power(x,y>>1);
    tmp=tmp*tmp;
    if(y&1)tmp=tmp*x;
    return tmp;
}

int main(){
    scanf("%lld%d%d",&n,&m,&k);
    Matrix A,B,C;
    A.init(1,1<<m);
    B.init(1<<m,1<<m);
    for(int i=0;i<(1<<m);i++){
        for(int j=0;j<2;j++){
            int s=(i>>1)|(j<<m-1);
            if(__builtin_popcount(i)<=k&&__builtin_popcount(s)<=k)
                B.add(s,i,1);
        }
    }
    C=power(B,n);
    long long answer=0;
    for(int i=0;i<(1<<m);i++)
        answer+=C.val(i,i);
    printf("%lld\n",answer%mod);
    return 0;
}
