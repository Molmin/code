/**
 * @date: 2024.02.19
 * @problem: QOJ7754, GYM104813I
 * @tags: 数学, 组合数学, 概率期望, 动态规划
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;

int n,m,a[13],b[13];
long long dp[1<<12][1001];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",a+i);
    for(int i=1;i<=m;i++)
        scanf("%d",b+i);
    dp[(1<<m)-1][0]=1;
    for(int status=(1<<m)-1;status>=1;status--){
        for(int i=0;i<=n;i++){
            int total=-n,totalFail=0;
            for(int j=1;j<=m;j++)
                if(status&(1<<j-1))total+=a[j];
                else total+=a[j]-b[j],totalFail+=a[j]-b[j];
            // dp[status][i]*totalFail*inv[total]
            dp[status][i+1]+=;
            for(int j=1;j<=m;j++)
                if(status&(1<<j-1))
                    dp[status][i]
        }
    }
    return 0;
}
