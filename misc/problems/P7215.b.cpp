/**
 * @date: 2024.01.18
 * @problem: P7215
 * @tags: 图论, 缩点
 * @note: 没写完
 */

#include<bits/stdc++.h>
using namespace std;

int n,k,col[200001],answer;
vector<int> ids[200001];
bool vis[200001];

struct Tree{
    struct Edge{
        int to,nxt;
    }edge[400001];
    int cntEdge,head[200001];
    inline void addEdge(int u,int v){
        edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
    }
}T;

struct Graph{
    struct Edge{
        int to,nxt;
    }edge[400001];
    int cntEdge,head[200001];
    inline void addEdge(int u,int v){
        edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
        // fprintf(stderr,"%d -> %d\n",u,v);
    }
}G;

int dep[200001],fa[200001][19];
void init(int id,int father){
    dep[id]=dep[father]+1;
    fa[id][0]=father;
    for(int k=1;k<=18;k++)
        fa[id][k]=fa[fa[id][k-1]][k-1];
    for(int i=T.head[id];i;i=T.edge[i].nxt){
        int v=T.edge[i].to;
        if(v==father)continue;
        init(v,id);
    }
}

inline int getlca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    for(int k=18;k>=0;k--)
        if(dep[u]-dep[v]>=(1<<k))
            u=fa[u][k];
    if(u==v)return u;
    for(int k=18;k>=0;k--)
        if(fa[u][k]!=fa[v][k])
            u=fa[u][k],v=fa[v][k];
    return fa[u][0];
}

stack<int> S;
int cntdfn,dfn[200001],low[200001];
bool inStack[200001];
void tarjan(int id,int father){
    low[id]=dfn[id]=++cntdfn;
    S.push(id),inStack[id]=true;
    for(int i=G.head[id];i;i=G.edge[i].nxt){
        int v=G.edge[i].to;
        if(v==father)continue;
        tarjan(v,id);
    }
    if(dfn[id]==low[id]){
        while(s.top().)
    }

}

int main(){
    scanf("%d%d",&n,&k),answer=k-1;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        T.addEdge(u,v);
        T.addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",col+i);
        ids[col[i]].push_back(i);
    }
    init(1,0);
    for(int c=1;c<=k;c++){
        if(ids[c].empty())continue;
        int lca=ids[c][0];
        for(int i :ids[c])lca=getlca(lca,i);
        set<int> S;
        for(int i :ids[c])if(i!=lca)
            S.insert(col[fa[i][0]]);
        for(int it :S)if(it!=c)
            G.addEdge(c,it);
    }
    printf("%d\n",answer);
    return 0;
}
