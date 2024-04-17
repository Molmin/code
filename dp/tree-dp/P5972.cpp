/**
 * @date: 2024.03.27
 * @problem: P5972, AT_agc009_d
 * @tags: 动态规划, 图论, 树形动态规划
 */

#include<bits/stdc++.h>
using namespace std;

int n,f[100001];

struct Edge{
    int to,nxt;
}edge[200001];
int head[100001],cntEdge;
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

void dfs(int id,int father){
    int cnt[20]={};
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father)continue;
        dfs(v,id);
        for(int k=0;k<20;k++)
            if((f[v]>>k)&1)cnt[k]++;
    }
    int i=19; while(i&&cnt[i]<2)i--;
    while(cnt[i])i++;
    f[id]|=1<<i;
    for(i++;i<20;i++)
        if(cnt[i])f[id]|=1<<i;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,0);
    for(int i=19;i>=0;i--)
        if((f[1]>>i)&1)return printf("%d\n",i),0;
    printf("0\n");
    return 0;
}
