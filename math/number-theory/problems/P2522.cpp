/**
 * @date: 2024.01.20
 * @problem: P2522, BZOJ2301
 * @tags: 数学, 数论, 莫比乌斯函数, 莫比乌斯反演, 整除分块
 */

#include<bits/stdc++.h>
using namespace std;

bool vis[50001];
int mu[50001],cntPrime,prime[50001];

void calcMu(int n=50000){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i])prime[++cntPrime]=i,mu[i]=-1;
        for(int j=1;j<=cntPrime&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
    }
    for(int i=2;i<=n;i++)mu[i]+=mu[i-1];
}

int solve(int n,int m,int k){
    int sum=0;
    for(int l=1,r;n/(l*k)&&m/(l*k);l=r+1){
        r=min(n/k/(n/(l*k)),m/k/(m/(l*k)));
        sum+=(mu[r]-mu[l-1])*(n/(l*k))*(m/(l*k));
    }
    return sum;
}

int main(){
    calcMu();
    int T; scanf("%d",&T);
    while(T--){
        int a,b,c,d,k;
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        printf("%d\n",solve(b,d,k)-solve(a-1,d,k)-solve(b,c-1,k)+solve(a-1,c-1,k));
    }
    return 0;
}
