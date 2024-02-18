/**
 * @date: 2024.02.18
 * @problem: CF1801E
 * @tags: 图论, 并查集, 倍增
 */

#include<bits/stdc++.h>
using namespace std;

int n,l[200001],r[200001];
vector<int> son[200001];

int dep[200001],fa[200001][19];
void init(int id,int father){
    dep[id]=dep[father]+1;
    fa[id][0]=father;
    for(int k=1;k<=18;k++)
        fa[id][k]=fa[fa[id][k-1]][k-1];
    for(int v :son[id])init(v,id);
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

int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        int f; scanf("%d",&f);
        son[f].push_back(i);
    }
    init(1,0);
    for(int i=1;i<=n;i++)
        scanf("%d%d",l+i,r+i);
    int m; scanf("%d",&m);
    while(m--){
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
    }
    return 0;
}
