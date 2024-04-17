/**
 * @date: 2024.03.29
 * @problem: P5465, LOJ6435
 * @tags: 组合数学, 概率期望, 倍增
 */

#include<bits/stdc++.h>
using namespace std;

int n,q,l[300001],f[300001][20];
long long g[300001][20];

inline long long calc(int x,int y){
    if(l[y]<=x)return y-x;
    long long sum=y-l[y];
    int now=1;
    y=l[y];
    for(int k=19;k>=0;k--){
        if(f[y][k]<x)continue;
        sum+=g[y][k]+1ll*now*(y-f[y][k]);
        now+=1<<k,y=f[y][k];
    }
    if(x<y)sum+=(now+1ll)*(y-x);
    return sum;
}

int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++)
        scanf("%d",l+i),f[i][0]=l[i],g[i][0]=i-l[i];
    for(int i=n-1;i>=2;i--){
        f[i][0]=min(f[i+1][0],f[i][0]);
        g[i][0]=i-f[i][0];
    }
    for(int k=1;k<20;k++)
        for(int i=1<<k;i<=n;i++){
            f[i][k]=f[f[i][k-1]][k-1];
            g[i][k]=g[i][k-1]+g[f[i][k-1]][k-1]+(f[i][k-1]-f[i][k])*(1ll<<k-1);
        }
    scanf("%d",&q);
    while(q--){
        int l,r,x;
        scanf("%d%d%d",&l,&r,&x);
        long long a=calc(l,x)-calc(r+1,x),b=r-l+1;
        printf("%lld/%lld\n",a/__gcd(a,b),b/__gcd(a,b));
    }
    return 0;
}
