/**
 * @date: 2024.02.22
 * @problem: CF1260F
 * @tags: 数学, 组合数学, 组合计数, 图论, 树链剖分, 数据结构, 树状数组
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

struct Edge{
    int to,nxt;
}edge[200001];
int cntEdge,head[100001];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int n,l[100001],r[100001];
long long inv[100001];
vector<int> insertpos[100001],removepos[100002];

struct BIT{
    long long v1[100001],v2[100001];
    inline int lowbit(int x){
        return x&-x;
    }
    inline void add(int x,int val){
        for(int t=x-1;x<=n;x+=lowbit(x)){
            v1[x]+=val,v1[x]%=mod;
            v2[x]+=1ll*val*t,v2[x]%=mod;
        }
    }
    inline void add(int l,int r,int val){
        add(l,val); add(r+1,-val);
    }
    inline long long query(int x){
        long long ret=0;
        for(int t=x;x;x-=lowbit(x))
            ret+=v1[x]*t-v2[x],ret%=mod;
        return ret%mod;
    }
    inline long long query(int l,int r){
        return query(r)-query(l-1);
    }
}_;

int fa[100001],dep[100001];
int siz[100001],heavy[100001];
void init(int id,int father){
    fa[id]=father,siz[id]=1;
    dep[id]=dep[father]+1;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father)continue;
        init(v,id);
        siz[id]+=siz[v];
        if(siz[v]>siz[heavy[id]])
            heavy[id]=v;
    }
}

int top[100001],cntdfn,dfn[100001];
void decomposition(int id,int col){
    top[id]=col,dfn[id]=++cntdfn;
    if(heavy[id])decomposition(heavy[id],col);
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa[id]||v==heavy[id])continue;
        decomposition(v,v);
    }
}

inline void updateChain(int x,long long val){
    while(x){
        _.add(dfn[top[x]],dfn[x],val);
        x=fa[top[x]];
    }
}
inline long long queryChain(int x){
    long long ret=0;
    while(x){
        ret+=_.query(dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    return ret;
}

long long A,B,C,D;
inline void insertPoint(int id){
    A+=dep[id]*inv[r[id]-l[id]+1],A%=mod;
    B+=inv[r[id]-l[id]+1],B%=mod;
    C+=dep[id]*inv[r[id]-l[id]+1]%mod*inv[r[id]-l[id]+1],C%=mod;
    D+=queryChain(id)*inv[r[id]-l[id]+1],D%=mod;
    updateChain(id,inv[r[id]-l[id]+1]);
}
inline void removePoint(int id){
    A-=dep[id]*inv[r[id]-l[id]+1],A%=mod;
    B-=inv[r[id]-l[id]+1],B%=mod;
    C-=dep[id]*inv[r[id]-l[id]+1]%mod*inv[r[id]-l[id]+1],C%=mod;
    updateChain(id,-inv[r[id]-l[id]+1]);
    D-=queryChain(id)*inv[r[id]-l[id]+1],D%=mod;
}

int main(){
    inv[1]=1;
    for(int i=2;i<=100000;i++)
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",l+i,r+i);
        insertpos[l[i]].push_back(i);
        removepos[r[i]+1].push_back(i);
    }
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    init(1,0);
    decomposition(1,1);
    long long answer=0;
    for(int i=1;i<=100000;i++){
        for(int v :insertpos[i])insertPoint(v);
        for(int v :removepos[i])removePoint(v);
        answer+=A*B%mod-C-D*2;
    }
    answer=(answer%mod+mod)%mod;
    for(int i=1;i<=n;i++)
        answer=answer*(r[i]-l[i]+1)%mod;
    printf("%lld\n",answer);
    return 0;
}
