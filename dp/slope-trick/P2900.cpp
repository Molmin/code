/**
 * @date: 2024.04.06
 * @problem: P2900, SPACQUIRE
 * @tags: 动态规划, 斜率优化
 */

#include<bits/stdc++.h>
using namespace std;

int n,w[50001],l[50001];
pair<int,int> rec[50001];
long long x[50001],y[50001],dp[50001];
int q[50001],head,tail;

inline double slope(int u,int v){
    return (y[v]-y[u])*1.0/(x[v]-x[u]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&rec[i].first,&rec[i].second);
    {
        sort(rec+1,rec+1+n,[&](pair<int,int> x,pair<int,int> y){return x>y;});
        int m=0;
        for(int i=1;i<=n;i++)
            if(rec[i].second>l[m])w[++m]=rec[i].first,l[m]=rec[i].second;
        n=m;
        reverse(w+1,w+1+n);
        reverse(l+1,l+1+n);
    }
    x[0]=-l[1];
    for(int i=1;i<=n;i++){
        while(head<tail&&slope(q[head],q[head+1])<=w[i])head++;
        dp[i]=dp[q[head]]+1ll*w[i]*l[q[head]+1];
        x[i]=-l[i+1],y[i]=dp[i];
        while(head<tail&&slope(q[tail],i)<slope(q[tail-1],q[tail]))tail--;
        q[++tail]=i;
    }
    printf("%lld\n",dp[n]);
    return 0;
}
