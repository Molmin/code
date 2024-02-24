/**
 * @date: 2024.02.21
 * @problem: QOJ6555
 * @tags: 数学, 组合计数, 数论
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;

long long power(long long x,long long y){
    if(y==0)return 1;
    long long tmp=power(x,y>>1);
    tmp=tmp*tmp%mod;
    if(y&1)tmp=tmp*x%mod;
    return tmp;
}

int n,m;
bitset<1001> a[1001];
long long f[2][2],g[2][2];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        a[u].flip(v);
    }	
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
            if(a[i][j])a[j].flip(i),a[i][j]=false;
        int x=0;
        for(int j=i+1;j<=n;j++)
            if(a[j][i])x=j;
        if(!x)continue;
        swap(a[x],a[i+1]);
        for(int j=i+1;j<=n;j++){
            bool tmp=a[j][x]; a[j][x]=a[j][i+1]; a[j][i+1]=tmp;
        }
        bitset<1001> tmp; tmp.reset();
        for(int j=i+2;j<=n;j++)
            if(a[j][i])a[j]^=a[i+1],tmp[j]=true;
        for(int j=i+1;j<=n;j++)
            if(a[j][i+1])a[j]^=tmp;
    }
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        g[0][0]=g[0][1]=g[1][0]=g[1][1]=0;
        for(int u=0;u<2;u++)
            for(int v=0;v<2;v++){
                g[0][v]+=f[u][v];
                g[1][v]+=f[u][v^a[i][i]^(u==0?0:a[i][i-1])];
            }
        for(int u=0;u<2;u++)
            for(int v=0;v<2;v++)f[u][v]=g[u][v]%mod;
    }
    printf("%lld\n",(f[0][0]+f[1][0])%mod);
    return 0;
}
