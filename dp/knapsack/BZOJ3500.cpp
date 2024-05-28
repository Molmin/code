/**
 * @date: 2024.05.27
 * @problem: BZOJ3500
 * @tags: 组合数学, 组合计数, 动态规划, 背包
 */

#include<bits/stdc++.h>
using namespace std;
int mod=999999599;

int power(int x,int y){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)return 1ll*tmp*x%mod;
    else return tmp;
}

int n,m,S;
int f[200001],g[200001];

int main(){
    scanf("%d%d",&n,&m),S=sqrt(n);
    f[0]=g[0]=1;
    for(int i=1;i<=S;i++)
        for(int j=i;j<=n;j++)
            f[j]=(f[j]+f[j-i])%(mod-1);
    long long answer=f[n];
    for(int i=1;i<=S;i++)
        for(int j=0;j<=n;j++){
            g[j]=(g[j]+(j-i>=0?g[j-i]:0))%(mod-1);
            int require=n-j-i*(S+1);
            if(require>=0)answer+=1ll*g[j]*f[require]%(mod-1);
        }
    printf("%d\n",power(m,answer%(mod-1)));
    return 0;
}
