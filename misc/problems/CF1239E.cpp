/**
 * @date: 2024.01.29
 * @problem: CF1239E
 * @tags: 思维
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[51],ans[2][26];
bitset<2500001> dp[51][26];
bool vis[51];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n*2;i++)
        scanf("%d",a+i);
    sort(a+1,a+1+2*n,[&](int x,int y){return x>y;});
    n=2*n-2;
    dp[0][0][0]=true;
    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=a[i];
        dp[i][0]=dp[i-1][0];
        for(int j=min(i,n/2);j>=1;j--)
            dp[i][j]=(dp[i-1][j-1]<<a[i])|dp[i-1][j];
    }
    int minn=0x7fffffff;
    for(int i=0;i<=sum;i++)
        if(dp[n][n/2][i])minn=min(minn,max(i,sum-i));
    for(int i=n,total=n/2;i>=1;i--){
        if(dp[i-1][total][minn]);
        else vis[i]=true,minn-=a[i],total--;
    }
    n=n/2+1;
    ans[0][1]=a[2*n-1],ans[1][n]=a[2*n];
    ans[0][0]=1;
    for(int i=1;i<=2*n-2;i++)
        if(vis[i])ans[0][++ans[0][0]]=a[i];
        else ans[1][++ans[1][0]]=a[i];
    sort(ans[0]+2,ans[0]+1+n);
    sort(ans[1]+1,ans[1]+n,[&](int x,int y){return x>y;});
    for(int i=0;i<2;i++)
        for(int j=1;j<=n;j++)
            printf("%d%c",ans[i][j]," \n"[j==n]);
    return 0;
}
