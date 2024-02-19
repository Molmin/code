/**
 * @date: 2024.02.18
 * @problem: LOJ3646, QOJ4909
 * @tags: 图论, 树链剖分, 倍增, 位运算, 贪心
 */

#include<bits/stdc++.h>
using namespace std;

int read(){
    int x=0; char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
    return x;
}
long long readll(){
    long long x=0; char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
    return x;
}

int n; long long w[1000001];

struct Edge{
    int to,nxt;
}edge[2000001];
int cntEdge,head[1000001];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int fa[1000001],dep[1000001];
int siz[1000001],heavy[1000001];
void init(int id,int father){
    dep[id]=dep[father]+1;
    siz[id]=1,fa[id]=father;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father)continue;
        init(v,id);
        siz[id]+=siz[v];
        if(siz[v]>siz[heavy[id]])heavy[id]=v;
    }
}

int top[1000001],dfn[1000001],cntdfn;
void decomposition(int id,int t){
    top[id]=t,dfn[id]=++cntdfn;
    if(heavy[id])decomposition(heavy[id],t);
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa[id]||v==heavy[id])continue;
        decomposition(v,v);
    }
}

long long dfsw[1000001],st[1000001][21];
int pos[1000001][21];

struct Node{
    long long maxn;
    int l,r,maxpos;
    bool shouldSplit;
    inline bool operator<(Node x)const{
        return maxn<x.maxn;
    }
};

priority_queue<Node> Q;

inline long long queryMax(int l,int r){
    int k=__lg(r-l+1);
    return max(st[l][k],st[r-(1<<k)+1][k]);
}
inline int getMaxPosition(int l,int r,long long maxn=-1){
    int k=__lg(r-l+1);
    long long lval=st[l][k],rval=st[r-(1<<k)+1][k];
    return lval>rval?pos[l][k]:pos[r-(1<<k)+1][k];
}

inline void pushToQueue(int l,int r){
    long long maxn=queryMax(l,r);
    Q.push({maxn,l,r,getMaxPosition(l,r,maxn),true});
}

inline void addChain(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        pushToQueue(dfn[top[u]],dfn[u]);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v])swap(u,v);
    pushToQueue(dfn[u],dfn[v]);
}

int main(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++)w[i]=readll();
    init(1,0);
    decomposition(1,1);
    for(int i=1;i<=n;i++)dfsw[dfn[i]]=w[i];
    for(int i=1;i<=n;i++)st[i][0]=dfsw[i],pos[i][0]=i;
    for(int k=1;k<=20;k++)
        for(int i=1;i+(1<<k)-1<=n;i++){
            st[i][k]=max(st[i][k-1],st[i+(1<<k-1)][k-1]);
            pos[i][k]=st[i][k]==st[i][k-1]?pos[i][k-1]:pos[i+(1<<k-1)][k-1];
        }
    int q=read();
    long long lastAnswer=0;
    while(q--){
        int x=(readll()^lastAnswer)%n+1;
        int y=(readll()^lastAnswer)%n+1;
        int m=read(),target=m*62;
        while(!Q.empty())Q.pop();
        addChain(x,y);
        long long answer=0;
        while(!Q.empty()&&Q.top().maxn>answer){
            vector<long long> vals;
            int k=__lg(Q.top().maxn^answer);
            do{
                Node it=Q.top(); Q.pop();
                vals.push_back(it.maxn);
                if(!it.shouldSplit)continue;
                if(it.l!=it.maxpos)pushToQueue(it.l,it.maxpos-1);
                if(it.maxpos!=it.r)pushToQueue(it.maxpos+1,it.r);
            }
            while(
                vals.size()<m&&!Q.empty()&&Q.top().maxn>answer
                &&__lg(Q.top().maxn^answer)==k
            );
            if(vals.size()==m){
                answer|=1ll<<k;
                for(long long v :vals)Q.push({v,0,0,0,false});
            }
            else for(long long v :vals)
                Q.push({v^(1ll<<k),0,0,0,false});
        }
        printf("%lld\n",answer);
        lastAnswer=answer;
    }
    return 0;
}
