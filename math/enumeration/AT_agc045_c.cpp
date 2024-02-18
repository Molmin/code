/**
 * @date: 2024.02.18
 * @problem: AT_agc045_c
 * @tags: 数学, 组合数学, 组合计数, 思维, 动态规划
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int n,a,b;
long long f[5001],g[5001][5001],h[5001][5001];
long long sg[5001],sumg[5001][5001],sumh[5001];

int main(){
    scanf("%d%d%d",&n,&a,&b);
    if(a>b)swap(a,b);
    f[0]=g[0][0]=h[0][0]=1;
    if(n<=1000){
        // O(N^3)
        for(int i=1;i<=n;i++){
            if(i<a)f[i]++;
            for(int j=max(0,i-a+1);j<i;j++)
                for(int k=1;k<=j;k++)
                    f[i]+=g[j][k],f[i]%=mod;
            for(int j=1;j<=i&&j<b;j++){
                for(int k=1;k<j;k++)
                    g[i][j]+=h[i-k][j-k];
                g[i][j]+=f[i-j],g[i][j]%=mod;
            }
            if(a<=i&&i<b)h[i][i]++;
            for(int j=1;j<=i&&j<b;j++){
                for(int k=a;k<j;k++)
                    h[i][j]+=g[i-k][j-k];
                h[i][j]%=mod;
            }
        }
    }
    else{
        // O(N^2)
        for(int i=1;i<=n;i++){
            for(int j=1;j<i;j++)
                sg[i-1]+=g[i-1][j];
            sg[i-1]%=mod;

            if(i<a)f[i]++;
            for(int j=max(0,i-a+1);j<i;j++)f[i]+=sg[j];
            f[i]%=mod;
            for(int j=1;j<=i&&j<b;j++){
                g[i][j]=(sumh[i-j]+f[i-j])%mod;
                sumg[i][j]=(sumg[i-1][j-1]+g[i][j])%mod;
            }
            if(a<=i&&i<b)h[i][i]++;
            for(int j=1;j<=i&&j<b;j++){
                if(i>=a&&j>=a)h[i][j]+=sumg[i-a][j-a],h[i][j]%=mod;
                sumh[i-j]+=h[i][j],sumh[i-j]%=mod;
            }
        }
    }
    long long answer=1;
    for(int i=1;i<=n;i++)answer=answer*2%mod;
    answer-=f[n];
    for(int i=1;i<=n;i++)
        answer-=g[n][i]+h[n][i];
    printf("%lld\n",(answer%mod+mod)%mod);
    return 0;
}
