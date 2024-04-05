/**
 * @date: 2024.01.23
 * @problem: P4649, BZOJ1808
 * @tags: 图论, 动态规划, 树形动态规划, 状态压缩动态规划
 */

#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<pair<pair<int,int>,int>> edge;
vector<int> E[1001];
vector<int> toHandle[1001];

int dep[1001],fa[1001][11];
void dfs(int id,int father){
    dep[id]=dep[father]+1;
    fa[id][0]=father;
    for(int k=1;k<=10;k++)
        fa[id][k]=fa[fa[id][k-1]][k-1];
    for(int v :E[id]){
        if(v==father)continue;
        dfs(v,id);
    }
}

inline int getlca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    for(int i=10;i>=0;i--)
        if(dep[u]-dep[v]>=(1<<i))
            u=fa[u][i];
    if(u==v)return u;
    for(int i=10;i>=0;i--)
        if(fa[u][i]!=fa[v][i])
            u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}

int f[1001][1<<10],idx[1001];
void dp(int id,int father){
    int cntSon=0;
    for(int v :E[id]){
        if(v==father)continue;
        dp(v,id);
        idx[v]=cntSon++;
    }
    for(int status=0;status<(1<<cntSon);status++)
        for(int v :E[id]){
            if(v==father)continue;
            if(!(status&(1<<idx[v])))f[id][status]+=f[v][0];
        }
    for(int e :toHandle[id]){
        int u=edge[e].first.first;
        int v=edge[e].first.second;
        int w=edge[e].second;
        if(u!=id){
            w+=f[u][0];
            while(fa[u][0]!=id){
                w+=f[fa[u][0]][1<<idx[u]];
                u=fa[u][0];
            }
        }
        if(v!=id){
            w+=f[v][0];
            while(fa[v][0]!=id){
                w+=f[fa[v][0]][1<<idx[v]];
                v=fa[v][0];
            }
        }
        for(int status=0;status<(1<<cntSon);status++){
            int tar=status;
            if(u!=id){
                if(status&(1<<idx[u]))continue;
                tar|=1<<idx[u];
            }
            if(v!=id){
                if(status&(1<<idx[v]))continue;
                tar|=1<<idx[v];
            }
            f[id][status]=max(f[id][status],f[id][tar]+w);
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    int sum=0;
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        if(w==0){
            E[u].push_back(v);
            E[v].push_back(u);
        }
        else edge.push_back({{u,v},w}),sum+=w;
    }
    dfs(1,0);
    for(int i=0;i<edge.size();i++){
        int u=edge[i].first.first,v=edge[i].first.second;
        int lca=getlca(u,v);
        if(!((dep[u]+dep[v])&1))toHandle[lca].push_back(i);
    }
    dp(1,0);
    printf("%d\n",sum-f[1][0]);
    return 0;
}
