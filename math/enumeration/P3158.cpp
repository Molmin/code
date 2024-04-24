/**
 * @date: 2024.04.24
 * @problem: P3158, BZOJ3294
 * @tags: 数学, 组合数学, 组合计数, 动态规划
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+9;

int C[901][901];
void init(int n=900){
    for(int i=0;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
}

int n,m,c;
int f[11][31][31],g[31][31];

int main(){
    init();
    scanf("%d%d%d",&n,&m,&c);
    f[0][0][0]=1;
    for(int i=1;i<=c;i++){
        int x; scanf("%d",&x);
        memset(g,0,sizeof g);
        for(int r=1;r<=n;r++)
            for(int c=1;c<=m;c++){
                long long ret=C[r*c][x];
                for(int p=1;p<=r;p++)
                    for(int q=1;q<=c;q++)
                        if(p<n||q<c)ret-=1ll*C[r][p]*C[c][q]%mod*g[p][q]%mod;
                g[r][c]=(ret%mod+mod)%mod;
            }
        for(int r=1;r<=n;r++)
            for(int c=1;c<=m;c++){
                long long ret=0;
                for(int p=1;p<=r;p++)
                    for(int q=1;q<=c;q++)
                        ret+=1ll*C[n-r+p][p]*C[m-c+q][q]%mod
                            *f[i-1][r-p][c-q]%mod*g[p][q]%mod;
                f[i][r][c]=ret%mod;
            }
    }
    long long answer=0;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            answer+=f[c][i][j];
    printf("%lld\n",answer%mod);
    return 0;
}
