/**
 * @date: 2024.01.22
 * @problem: BZOJ2226, SPLCMSUM
 * @tags: 数学, 数论, 线性筛
 */

#include<bits/stdc++.h>
using namespace std;

bool vis[1000001];
int cntPrime,prime[1000001];
long long f[1000001];

void precalc(int n=1000000){
    f[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i])prime[++cntPrime]=i,f[i]=1+i*(i-1ll);
        for(int j=1;j<=cntPrime&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                f[i*prime[j]]=f[i]+(f[i]-f[i/prime[j]])*prime[j]*prime[j];
                break;
            }
            f[i*prime[j]]=f[i]*f[prime[j]];
        }
    }
}

int main(){
    precalc();
    int T; scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        printf("%lld\n",(f[n]+1)*n/2);
    }
    return 0;
}
