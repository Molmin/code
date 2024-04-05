/**
 * @date: 2022.08.02
 * @problem: AGC019F
 * @tags: 数学, 概率期望, 组合数学, 组合计数
 */

#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;

long long power(long long m,long long n=mod-2){
    if(n==0)return 1;
    long long tmp=power(m,n>>1);
    tmp=tmp*tmp%mod;
    if(n&1)tmp=tmp*m%mod;
    return tmp;
}

long long fac[2000001],invfac[2000001];
void init(int N=2000000){
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=fac[i-1]*i%mod;
    invfac[N]=power(fac[N]);
    for(int i=N-1;i>=0;i--)
        invfac[i]=invfac[i+1]*(i+1)%mod;
}
inline long long C(int n,int m){
    return fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}
inline long long invC(int n,int m){
    return invfac[n]*fac[m]%mod*fac[n-m]%mod;
}

int main(){
    init();
    int n,m;
    scanf("%d%d",&n,&m);
    if(n>m)swap(n,m);
    long long answer=0,inv2=power(2);
    for(int i=1;i<=n;i++)
        answer+=C(i<<1,i)*C(n+m-(i<<1),n-i)%mod,answer%=mod;
    printf("%lld\n",answer*inv2%mod*invC(n+m,n)%mod+m);
    return 0;
}
