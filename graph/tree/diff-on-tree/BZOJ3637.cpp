/**
 * @date: 2024.02.23
 * @problem: BZOJ3637, SP_QTREE6
 * @tags: 图论, 树上差分, 树链剖分, 数据结构, 树状数组
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,col[100001];

struct Edge{
    int to,nxt;
}edge[200001];
int cntEdge,head[100001];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int fa[100001],siz[100001],heavy[100001];
void init(int id,int father){
    fa[id]=father,siz[id]=1;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father)continue;
        init(v,id);
        siz[id]+=siz[v];
        if(siz[v]>siz[heavy[id]])
            heavy[id]=v;
    }
}

int cntdfn,dfn[100001],rnk[100001],endAt[100001];

struct BIT{
    int v[100001];
    inline int lowbit(int x){
        return x&-x;
    }
    inline void add(int x,int val){
        if(!x)return;
        for(;x<=n;x+=lowbit(x))v[x]+=val;
    }
    inline int query(int x){
        int ret=0;
        for(;x;x-=lowbit(x))ret+=v[x];
        return ret;
    }
    inline int sum(int x){
        return query(endAt[x])-query(dfn[x]-1);
    }
}T[2];

int top[100001];
int maxid[100001][2];
set<int> ids[100001][2];
void decomposition(int id,int col){
    dfn[id]=++cntdfn,rnk[cntdfn]=id,top[id]=col;
    ids[top[id]][0].insert(dfn[id]);
    maxid[top[id]][0]=id;
    if(heavy[id])decomposition(heavy[id],col);
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa[id]||v==heavy[id])continue;
        decomposition(v,v);
    }
    endAt[id]=cntdfn;
    T[0].add(dfn[id],1);
    T[1].add(dfn[fa[id]],-1),T[1].add(dfn[id],1);
}

inline int getFirst(int id,int col){
    int x=id; id=fa[id];
    while(id){
        if(maxid[top[id]][col]){
            auto it=ids[top[id]][col].upper_bound(dfn[id]);
            if(it!=ids[top[id]][col].begin()){
                int tmp=rnk[*--it];
                if(tmp==id)return x;
                else return heavy[tmp];
            }
        }
        x=top[id],id=fa[x];
    }
    return 1;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    init(1,0);
    decomposition(1,1);
    scanf("%d",&m);
    while(m--){
        int op,u;
        scanf("%d%d",&op,&u);
        if(op){
            ids[top[u]][col[u]].erase(dfn[u]);
            ids[top[u]][!col[u]].insert(dfn[u]);
            maxid[top[u]][0]=ids[top[u]][0].empty()?0:rnk[*ids[top[u]][0].begin()];
            maxid[top[u]][1]=ids[top[u]][1].empty()?0:rnk[*ids[top[u]][1].begin()];

            int target=getFirst(u,!col[u]);
            if(fa[target])target=fa[target];
            int val=T[col[u]].sum(u);
            T[col[u]].add(dfn[fa[u]],-val);
            T[col[u]].add(dfn[fa[target]],val);

            col[u]^=1;
            target=getFirst(u,!col[u]);
            if(fa[target])target=fa[target];
            val=T[col[u]].sum(u);
            T[col[u]].add(dfn[fa[u]],val);
            T[col[u]].add(dfn[fa[target]],-val);
        }
        else printf("%d\n",T[col[u]].sum(getFirst(u,!col[u])));
    }
    return 0;
}