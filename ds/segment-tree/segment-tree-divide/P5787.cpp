/**
 * @date: 2024.05.24
 * @problem: P5787, BZOJ4025
 * @tags: 数据结构, 线段树, 线段树分治, 并查集, 可撤销并查集, 图论, 二分图
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,t;
vector<pair<int,int>> edges[400001];

void addEdge(int id,int l,int r,int u,int v,int tl,int tr){
    if(tl<=l&&r<=tr){
        edges[id].emplace_back(u,v);
        return;
    }
    int mid=l+r>>1;
    if(tl<=mid)addEdge(id<<1,l,mid,u,v,tl,tr);
    if(mid<tr)addEdge(id<<1|1,mid+1,r,u,v,tl,tr);
}

int fa[200001],d[200001];
vector<pair<int,bool>> revertSteps;

int find(int id){
    if(fa[id]==id)return id;
    else return find(fa[id]);
}
void merge(int u,int v){
    if(d[u]>d[v])swap(u,v);
    fa[u]=v,revertSteps.emplace_back(u,d[u]==d[v]);
    if(d[u]==d[v])d[v]++;
}

void solve(int id,int l,int r){
    int now=revertSteps.size(); bool flag=true;
    for(pair<int,int> edge :edges[id]){
        int u=edge.first,v=edge.second;
        int fu=find(u),fv=find(v);
        if(fu==fv){
            flag=false;
            break;
        }
        merge(fu,find(v+n)),merge(find(u+n),fv);
    }
    if(!flag)for(int i=l;i<=r;i++)puts("No");
    else if(l==r)puts("Yes");
    else{
        int mid=l+r>>1;
        solve(id<<1,l,mid);
        solve(id<<1|1,mid+1,r);
    }
    while(now<revertSteps.size()){
        pair<int,bool> step=revertSteps.back();
        revertSteps.pop_back();
        int u=step.first;
        if(step.second)d[fa[u]]--;
        fa[u]=u;
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=m;i++){
        int u,v,l,r;
        scanf("%d%d%d%d",&u,&v,&l,&r);
        addEdge(1,1,t,u,v,l+1,r);
    }
    for(int i=1;i<=n*2;i++)fa[i]=i;
    solve(1,1,t);
    return 0;
}
