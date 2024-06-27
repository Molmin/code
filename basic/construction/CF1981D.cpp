/**
 * @date: 2024.06.11
 * @problem: CF1981D
 * @tags: 构造, 数论, 素数, 图论, 欧拉回路
 */

#include<bits/stdc++.h>
using namespace std;

int primes[5000],cntprime;
bool notprime[20000];

int k,now[5000];
bool vis[5000][5000];

void dfs(int u,int &target){
    for(int *i=&now[u];*i<=k;(*i)++){
        if(vis[u][*i])continue;
        vis[u][*i]=vis[*i][u]=true;
        dfs(*i,target);
    }
    if(target){
        target--;
        printf("%d%c",primes[u]," \n"[!target]);
    }
}

int main(){
    for(int i=2;i<20000;i++){
        if(!notprime[i])primes[++cntprime]=i;
        for(int j=1;primes[j]*i<20000&&j<=cntprime;j++){
            notprime[primes[j]*i]=true;
            if(i%primes[j]==0)break;
        }
    }
    int T; scanf("%d",&T);
    while(T--){
        int n; scanf("%d",&n);
        k=0;
        while(true){
            k++;
            if(k%2==0&&k*(k+1)/2+1-(k/2-1)>=n)break;
            if(k%2==1&&k*(k+1)/2+1>=n)break;
        }
        if(k%2==0){
            for(int i=3;i<=k;i+=2)
                vis[i][i+1]=vis[i+1][i]=true;
        }
        for(int i=1;i<=k;i++)now[i]=1;
        int cnt=n; dfs(1,cnt);
        for(int i=1;i<=k;i++)
            for(int j=1;j<=k;j++)
                vis[i][j]=false;
    }
    return 0;
}
