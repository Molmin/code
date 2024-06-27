/**
 * @date: 2024.06.08
 * @problem: BZOJ3518
 * @tags: 数学, 数论, 莫比乌斯函数, 莫比乌斯反演, 整除分块
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int n,m;
bool vis[50001];
int cntPrime,prime[50001],phi[50001];

void precalc(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i])prime[++cntPrime]=i,phi[i]=i-1;
        for(int j=1;j<=cntPrime&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    precalc(min(n,m));
    long long answer=0;
    for(int d=1;d<=min(n,m);d++)
        answer+=phi[d]
            *(1ll*(n-d+n-n/d*d)*(n/d)/2%mod)%mod
            *(1ll*(m-d+m-m/d*d)*(m/d)/2%mod)%mod;
    answer-=(1ll*n*(n-1)/2%mod)*(1ll*m*(m-1)/2%mod)%mod;
    answer*=2;
    answer+=n*(1ll*m*(m-1)*(m-2)/6%mod);
    answer+=m*(1ll*n*(n-1)*(n-2)/6%mod);
    printf("%lld\n",(answer%mod+mod)%mod);
    return 0;
}
