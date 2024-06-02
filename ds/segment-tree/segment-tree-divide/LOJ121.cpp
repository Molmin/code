/**
 * @date: 2024.06.02
 * @problem: LOJ121
 * @tags: 数据结构, 线段树, 线段树分治, 并查集, 可撤销并查集, 图论, 二分图
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,u[500001],v[500001];
map<pair<int,int>,int> mp;
vector<pair<int,int>> edges[2000001];

void addEdge(int id,int l,int r,int u,int v,int tl,int tr){
    if(tl<=l&&r<=tr){
        edges[id].emplace_back(u,v);
        return;
    }
    int mid=l+r>>1;
    if(tl<=mid)addEdge(id<<1,l,mid,u,v,tl,tr);
    if(mid<tr)addEdge(id<<1|1,mid+1,r,u,v,tl,tr);
}

int fa[5001],d[5001];
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
    int now=revertSteps.size();
    for(pair<int,int> edge :edges[id]){
        int u=edge.first,v=edge.second;
        int fu=find(u),fv=find(v);
        if(fu==fv)continue;
        merge(fu,fv);
    }
    if(l==r&&u[l]){
        int fu=find(u[l]),fv=find(v[l]);
        if(fu==fv)puts("Y");
        else puts("N");
    }
    else if(l<r){
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
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(x>y)swap(x,y);
        if(op==0)mp[{x,y}]=i;
        if(op==1){
            addEdge(1,1,m,x,y,mp[{x,y}],i);
            mp.erase({x,y});
        }
        if(op==2)u[i]=x,v[i]=y;
    }
    for(pair<pair<int,int>,int> i :mp)
        addEdge(1,1,m,i.first.first,i.first.second,i.second,m);
    for(int i=1;i<=n;i++)fa[i]=i;
    solve(1,1,m);
    return 0;
}
