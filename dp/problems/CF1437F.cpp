/**
 * @date: 2024.02.17
 * @problem: CF1437F
 * @tags: 动态规划, 数学, 组合数学, 组合计数
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;

long long power(long long x,long long y=mod-2){
    if(y==0)return 1;
    long long tmp=power(x,y>>1);
    tmp=tmp*tmp%mod;
    if(y&1)tmp=tmp*x%mod;
    return tmp;
}

long long fac[5001],invfac[5001];
void init(int n=5000){
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    invfac[n]=power(fac[n]);
    for(int i=n;i>=1;i--)invfac[i-1]=invfac[i]*i%mod;
}
inline long long A(int x,int y){
    return fac[x]*invfac[x-y]%mod;
}

int n,a[5001],lim[5001];
long long dp[5001];

int main(){
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    sort(a+1,a+1+n);
    lim[0]=-1,dp[0]=1;
    for(int i=1;i<=n;i++){
        lim[i]=lim[i-1];
        while(a[lim[i]+1]<=a[i]/2)lim[i]++;
    }
    if(lim[n]<n-1)return printf("0\n"),0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=lim[i];j++)
            dp[i]+=dp[j]*A(n-2-lim[j],lim[i]-lim[j]-1)%mod;
        dp[i]%=mod;
    }
    printf("%lld\n",dp[n]);
    return 0;
}
