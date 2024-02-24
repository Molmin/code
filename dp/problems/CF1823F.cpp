/**
 * @date: 2024.02.23
 * @problem: CF1823F
 * @tags: 动态规划, 图论, 数学, 概率期望
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;

int n,s,t,deg[200001];

struct Edge{
    int to,nxt;
}edge[400001];
int cntEdge,head[200001];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

bool onChain[200001];
void init(int id,int father){
    if(id==s){
        onChain[id]=true;
        return;
    }
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father)continue;
        init(v,id);
        if(onChain[v])onChain[id]=true;
    }
}

long long f[200001];
void dfs(int id,int father){
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father)continue;
        if(onChain[v])f[v]=f[id]+1;
        else f[v]=f[id];
        dfs(v,id);
    }
}

int main(){
    scanf("%d%d%d",&n,&s,&t);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
        deg[u]++,deg[v]++;
    }
    init(t,0);
    dfs(t,0);
    deg[t]=f[t]=1;
    for(int i=1;i<=n;i++)
        printf("%lld%c",1ll*f[i]*deg[i]%mod," \n"[i==n]);
    return 0;
}
