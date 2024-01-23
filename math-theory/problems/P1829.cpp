/**
 * @date: 2024.01.22
 * @problem: P1829, BZOJ2154
 * @tags: 数学, 数论, 莫比乌斯反演, 整除分块
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=20101009;

int n,m;

bool vis[10000001];
int mu[10000001],cntPrime,prime[1000001];
int sum[10000001];

void precalc(int n=10000000){
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
    for(int i=1;i<=n;i++)
        sum[i]=(1ll*i*i%mod*mu[i]+sum[i-1]+mod)%mod;
}

inline int calcsum(int n,int m){
    return ((n+1ll)*n/2%mod)*((m+1ll)*m/2%mod)%mod;
}

int f(int n,int m){
    long long answer=0;
    for(int l=1,r;l<=n;l=r+1){
        r=min(n,min(n/(n/l),m/(m/l)));
        answer+=1ll*(sum[r]-sum[l-1])*calcsum(n/l,m/l)%mod;
    }
    return answer;
}

int main(){
    precalc();
    scanf("%d%d",&n,&m);
    if(n>m)swap(n,m);
    long long answer=0;
    for(int l=1,r;l<=n;l=r+1){
        r=min(n,min(n/(n/l),m/(m/l)));
        answer+=f(n/l,m/l)*((l+r)*(r-l+1ll)/2%mod)%mod;
    }
    printf("%lld\n",(answer%mod+mod)%mod);
    return 0;
}
