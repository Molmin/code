/**
 * @date: 2024.06.02
 * @problem: P5214, BZOJ3562, LOJ2189
 * @tags: 数据结构, 线段树, 线段树分治, 并查集, 可撤销并查集, 图论
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,q,isQuery[10001];
map<pair<int,int>,int> mp;
vector<pair<int,int>> edges[40005];

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

void solve(int id,int l,int r,int answer){
    int now=revertSteps.size();
    for(pair<int,int> edge :edges[id]){
        int u=edge.first,v=edge.second;
        int fu=find(u),fv=find(v);
        if(fu!=fv){
            merge(fu,fv);
            answer--;
        }
    }
    if(l==r&&isQuery[l])
        printf("%d\n",answer);
    else if(l<r){
        int mid=l+r>>1;
        solve(id<<1,l,mid,answer);
        solve(id<<1|1,mid+1,r,answer);
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
        int u,v;
        scanf("%d%d",&u,&v);
        if(u>v)swap(u,v);
        mp[{u,v}]=0;
    }
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        char op;
        scanf(" %c",&op);
        if(op=='Q'){
            isQuery[i]=true;
            continue;
        }
        int u,v;
        scanf("%d%d",&u,&v);
        if(u>v)swap(u,v);
        if(op=='A')mp[{u,v}]=i;
        if(op=='D'){
            addEdge(1,0,q,u,v,mp[{u,v}],i);
            mp.erase({u,v});
        }
    }
    for(pair<pair<int,int>,int> i :mp)
        addEdge(1,0,q,i.first.first,i.first.second,i.second,q);
    for(int i=1;i<=n;i++)fa[i]=i;
    solve(1,0,q,n);
    return 0;
}
