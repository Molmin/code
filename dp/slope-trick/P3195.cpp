/**
 * @date: 2024.04.06
 * @problem: P3195, BZOJ1010
 * @tags: 动态规划, 斜率优化
 */

#include<bits/stdc++.h>
using namespace std;

int n,l;
long long c[50001],x[50001],y[50001],dp[50001];
int q[50001],head,tail;

inline double slope(int u,int v){
    return (y[v]-y[u])*1.0/(x[v]-x[u]);
}

int main(){
    scanf("%d%d",&n,&l);
    for(int i=1;i<=n;i++)
        scanf("%lld",c+i),c[i]+=c[i-1];
    x[0]=0,y[0]=(l+1ll)*(l+1);
    for(int i=1;i<=n;i++){
        x[i]=c[i]+i;
        while(head<tail&&slope(q[head],q[head+1])<=2*x[i])head++;
        dp[i]=dp[q[head]]+(x[i]-x[q[head]]-l-1)*(x[i]-x[q[head]]-l-1);
        y[i]=(x[i]+l+1)*(x[i]+l+1)+dp[i];
        while(head<tail&&slope(q[tail],i)<slope(q[tail-1],q[tail]))tail--;
        q[++tail]=i;
    }
    printf("%lld\n",dp[n]);
    return 0;
}
