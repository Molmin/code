/**
 * @date: 2024.02.18
 * @problem: AT_arc118_e
 * @tags: 动态规划, 数学, 组合数学, 组合计数
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;

int n,a[201];
long long fac[201],dp[202][202][201][2][2];
bool vis[201];

inline void add(long long &x,long long y){x=x+y;}
inline bool canuse(int x,int y){
    return 1<=x&&x<=n&&1<=y&&y<=n&&(a[x]==y||(a[x]==-1&&!vis[y]));
}

int main(){
    scanf("%d",&n);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    int total=0;
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        if(a[i]!=-1)vis[a[i]]=true,total++;
    }
    dp[0][0][total][0][0]=1;
    for(int x=0;x<=n+1;x++)for(int y=0;y<=n+1;y++)
        for(int i=0;i<=n;i++)
            for(int p=0;p<=1;p++)for(int q=0;q<=1;q++){
                dp[x][y][i][p][q]%=mod;
                long long it=dp[x][y][i][p][q];
                if(x!=n+1){
                    add(dp[x+1][y][i][0][q],it);
                    if(!q&&canuse(x+1,y))
                        add(dp[x+1][y][i+(a[x+1]==-1)][1][1],-it);
                }
                if(y!=n+1){
                    add(dp[x][y+1][i][p][0],it);
                    if(!p&&canuse(x,y+1))
                        add(dp[x][y+1][i+(a[x]==-1)][1][1],-it);
                }
            }
    long long answer=0;
    for(int i=0;i<=n;i++)
        answer+=fac[n-i]*dp[n+1][n+1][i][0][0]%mod;
    printf("%lld\n",(answer%mod+mod)%mod);
    return 0;
}
