/**
 * @date: 2024.02.18
 * @problem: AT_agc030_d, CF258D
 * @tags: 数学, 逆序对, 概率期望, 动态规划
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

long long power(long long x,long long y=mod-2){
    if(y==0)return 1;
    long long tmp=power(x,y>>1);
    tmp=tmp*tmp%mod;
    if(y&1)tmp=tmp*x%mod;
    return tmp;
}

int n,q,a[3001];
long long f[3001][3001],g[3001][3001],inv2=power(2);

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=a[i]>a[j];
    for(int k=1;k<=q;k++){
        int x,y;
        scanf("%d%d",&x,&y);
        for(int i=1;i<=n;i++){
            if(i==x||i==y)continue;
            g[i][x]=g[i][y]=(f[i][x]+f[i][y])*inv2%mod;
            g[x][i]=g[y][i]=(f[x][i]+f[y][i])*inv2%mod;
        }
        g[x][y]=g[y][x]=(f[x][y]+f[y][x])*inv2%mod;
        for(int i=1;i<=n;i++){
            f[i][x]=g[i][x],f[i][y]=g[i][y];
            f[x][i]=g[x][i],f[y][i]=g[y][i];
        }
    }
    long long answer=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            answer+=f[i][j];
    printf("%lld\n",answer%mod*power(2,q)%mod);
    return 0;
}
