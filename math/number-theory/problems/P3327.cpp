/**
 * @date: 2024.02.07
 * @problem: P3327, LOJ2185, BZOJ3994
 * @tags: 数学, 数论, 莫比乌斯函数, 莫比乌斯反演, 整除分块
 */

#include<bits/stdc++.h>
using namespace std;

bool vis[50001];
int cnt[50001],cntPrime,prime[50001];
long long mu[50001],d[50001];

void calcMu(int n=50000){
    mu[1]=1,d[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cntPrime]=i;
            mu[i]=-1,d[i]=2,cnt[i]=1;
        }
        for(int j=1;j<=cntPrime&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                cnt[i*prime[j]]=cnt[i]+1;
                d[i*prime[j]]=d[i]/(cnt[i]+1)*(cnt[i]+2);
                break;
            }
            mu[i*prime[j]]=-mu[i];
            cnt[i*prime[j]]=1;
            d[i*prime[j]]=d[i]*2;
        }
    }
    for(int i=1;i<=n;i++)mu[i]+=mu[i-1],d[i]+=d[i-1];
}

int n,m;

int main(){
    calcMu();
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        long long answer=0;
        for(int l=1,r;l<=min(n,m);l=r+1){
            r=min(min(n,m),min(n/(n/l),m/(m/l)));
            answer+=(mu[r]-mu[l-1])*d[n/l]*d[m/l];
        }
        printf("%lld\n",answer);
    }
    return 0;
}
