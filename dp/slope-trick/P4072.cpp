/**
 * @date: 2024.04.06
 * @problem: P4072, BZOJ4518, LOJ2035
 * @tags: 动态规划, 斜率优化, WQS 二分
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,a[3001],g[3001];
long long x[3001],y[3001],f[3001];
int q[3001],head,tail;

inline double slope(int u,int v){
    return (y[v]-y[u])*1.0/(x[v]-x[u]);
}

void solve(long long mid){
    head=tail=0;
    for(int i=1;i<=n;i++){
        while(head<tail&&slope(q[head],q[head+1])<2*a[i])head++;
        g[i]=g[q[head]]+1;
        f[i]=f[q[head]]+mid+1ll*(a[i]-a[q[head]])*(a[i]-a[q[head]]);
        x[i]=a[i],y[i]=f[i]+1ll*a[i]*a[i];
        while(head<tail&&slope(q[tail],i)<slope(q[tail-1],q[tail]))tail--;
        q[++tail]=i;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),a[i]+=a[i-1];
    long long l=0,r=1ll*a[n]*a[n];
    while(l<r){
        long long mid=l+r>>1;
        solve(mid);
        if(g[n]<=m)r=mid;
        else l=mid+1;
    }
    solve(l);
    printf("%lld\n",(f[n]-m*l)*m-1ll*a[n]*a[n]);
    return 0;
}
