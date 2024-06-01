/**
 * @date: 2024.05.31
 * @problem: CF870E
 * @tags: 组合数学, 组合计数, 图论
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int power(int x,int y){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)tmp=1ll*tmp*x%mod;
    return tmp;
}

int n;
vector<int> E[200001];
int cntL=0,cntR=1e5;
map<int,int> newL,newR;
int answer=1,cntEdge,cntPoint;
bool vis[200001];

void dfs(int u,bool flag=false){
    if(flag)cntEdge=cntPoint=0;
    if(vis[u])return;
    vis[u]=true,cntPoint++;
    for(int v :E[u]){
        cntEdge++;
        if(vis[v])continue;
        dfs(v);
    }
    if(flag)answer=1ll*answer*(power(2,cntPoint)-(cntEdge/2==cntPoint-1)+mod)%mod;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        if(newL[x])x=newL[x];
        else x=newL[x]=++cntL;
        if(newR[y])y=newR[y];
        else y=newR[y]=++cntR;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    for(int i=1;i<=cntL;i++)dfs(i,true);
    for(int i=1e5+1;i<=cntR;i++)dfs(i,true);
    printf("%d\n",answer);
    return 0;
}
